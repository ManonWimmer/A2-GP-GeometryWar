#include "Player.h"
#include "CollisionDetection.h"
#include <list>
#include "ManagerEntity.h"



Player::Player(ManagerEntity& managerEntity, CollisionDetection& collisionDetection) : Entity(managerEntity, collisionDetection)
{
	sf::CircleShape tempShape;

	tempShape.setRadius(20);
	tempShape.setPosition(640, 360);
	tempShape.setFillColor(sf::Color::Red);

	this->circleShape = tempShape;

	this->pv = 4;

	this->invincibilityCooldown = 2;
	this->invincibilityTime = this->invincibilityCooldown;

	this->isInvincible = false;
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

	pos.x = collisionManager.ClampCircleOutsideRectangles(this->circleShape, collisionManager.rectList, sf::Vector2f(pos.x + dir.x, pos.y), pos).x;
	pos.y = collisionManager.ClampCircleOutsideRectangles(this->circleShape, collisionManager.rectList, sf::Vector2f(pos.x, pos.y + dir.y), pos).y;

	sf::RectangleShape screen;
	screen.setSize(sf::Vector2f(window.getSize()));

	pos = collisionDetection.ClampCircleInsideRectangle(this->circleShape, screen, pos, this->circleShape.getPosition());

	return pos;
}

void Player::Update(sf::RenderWindow& window, float deltaTime)
{
	circleShape.setPosition(MovePlayer(window, collisionDetection, deltaTime, 100.0f));
	
	window.draw(circleShape);
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
