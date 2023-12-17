#include "Player.h"
#include "CollisionDetection.h"
#include <list>
#include "ManagerEntity.h"
#include "GameManager.h"
#include "Weapon.h"
#include "Light.h"


Player::Player(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f position)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{

	ptrPistol = new Weapon(managerEntity, collisionDetection, EntityType::Weapon_Entity, entityFaction, CollisionType::None_CollisionType, WeaponType::Pistol, circleShape);
	managerEntity.AddEntity(ptrPistol);


	circleShape.setRadius(20);
	circleShape.setPosition(position);
	circleShape.setFillColor(sf::Color(255, 255, 255, 180));

	circleShape.setOutlineThickness(20 / 5);
	circleShape.setOutlineColor(sf::Color::White);

	circleShape.setOrigin(circleShape.getRadius(), circleShape.getRadius());

	
	_light = new Light(managerEntity, collisionDetection, EntityType::Light_Entity, Faction::None_Faction, CollisionType::None_CollisionType, 500.0f);
	managerEntity.AddEntity(_light);


	pv = 4;

	invincibilityCooldown = 2;
	invincibilityTime = invincibilityCooldown;

	isInvincible = false;

	fvCorner1.setRadius(7.0f);
	fvCorner1.setFillColor(sf::Color::Red);
	fvCorner1.setOrigin(fvCorner1.getRadius(), fvCorner1.getRadius());


}

sf::Vector2f Player::MovePlayer(sf::RenderWindow& window, CollisionDetection collManager, float deltaTime, float cubeSpeed)
{
	CollisionDetection collisionManager = collManager;

	sf::Vector2f pos = this->circleShape.getPosition();
	sf::Vector2f tempPos;
	tempPos.x = pos.x;
	tempPos.y = pos.y;

	sf::Vector2f dir;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		dir.x = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		dir.x = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		dir.y = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		dir.y = 1;


	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
	dir *= cubeSpeed * deltaTime;

	pos.x = collisionManager.ClampCircleOutsideRectangles(this->circleShape, sf::Vector2f(pos.x + dir.x, pos.y), pos).x;
	pos.y = collisionManager.ClampCircleOutsideRectangles(this->circleShape, sf::Vector2f(pos.x, pos.y + dir.y), pos).y;

	return pos;
}

void Player::Update(sf::RenderWindow& window, float deltaTime)
{

	circleShape.setPosition(MovePlayer(window, collisionDetection, deltaTime, 500.0f));
	fvCorner1.setPosition(circleShape.getPosition());
	window.draw(circleShape);

	_light->SetPosition(circleShape.getPosition());
}


void Player::CheckInvincibility(float deltaTime)
{
	if (this->isInvincible)
	{
		this->invincibilityCooldown -= deltaTime;
		if (invincibilityCooldown < 0)
		{
			this->isInvincible = false;
		}
	}
	else
	{
		if (this->invincibilityCooldown < 0)
		{
			this->invincibilityCooldown = this->invincibilityTime;
		}
	}
}

void Player::OnDestroy()
{
	if (ptrPistol != nullptr)   ptrPistol->DestroyItSelf();
}

sf::CircleShape& Player::GetEntityCircleShape()
{
	return circleShape;
}