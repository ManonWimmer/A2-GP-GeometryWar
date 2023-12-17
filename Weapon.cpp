#include "Weapon.h"
#include "CollisionDetection.h" 

#include "ParticleSystem.h"

#include <math.h>

#include "SoundManager.h"

Weapon::Weapon(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, WeaponType weaponType, sf::CircleShape& ownerObject)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{
	switch (weaponType)
	{
	case WeaponType::Pistol:
		this->FireRate = 0.25;
		this->_bulletSpeed = 800;
		this->FireTime = 2;
		this->ownerObject = &ownerObject;

		aimRectangle.setFillColor(sf::Color::White);
		aimRectangle.setPosition(640, 360);
		aimRectangle.setSize(sf::Vector2f(20, 50));
		aimRectangle.setOrigin(aimRectangle.getSize().x / 2, 0);

		break;

	default:
		this->FireRate = 0.5;
		this->_bulletSpeed = 0;
		this->FireTime = 0;
		this->ownerObject = &ownerObject;
		break;
	}
}

Weapon::Weapon(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, WeaponType weaponType, sf::CircleShape& ownerObject, sf::CircleShape* target)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _target(target)
{
	switch (weaponType)
	{
	case WeaponType::Pistol:
		this->FireRate = 0.25;
		this->_bulletSpeed = 800;
		this->FireTime = 2;
		this->ownerObject = &ownerObject;

		aimRectangle.setFillColor(sf::Color::White);
		aimRectangle.setPosition(640, 360);
		aimRectangle.setSize(sf::Vector2f(20, 50));
		aimRectangle.setOrigin(aimRectangle.getSize().x / 2, 0);
		break;

	default:
		this->FireRate = 0.5;
		this->_bulletSpeed = 0;
		this->FireTime = 0;
		this->ownerObject = &ownerObject;
		break;
	}
}

void Weapon::Shoot(sf::RenderWindow& window)
{
	std::cout << "shoot" << std::endl;
	//Play Shoot Sound
	managerEntity.GetSoundManager().PlaySound(SoundEnums::ShotPistolSound);


	// Projectile shape
	sf::CircleShape projectileShape;
	projectileShape.setOutlineColor(sf::Color(255, 204, 229, 255));
	projectileShape.setFillColor(sf::Color::White);
	projectileShape.setOutlineThickness(4);
	projectileShape.setRadius(6);

	sf::Vector2f targetPosition;
	sf::Vector2f bulletOrigin;
	sf::Vector2f ownerPos(ownerObject->getPosition());

	if(_target == nullptr) {
		// Get positions
		targetPosition = sf::Vector2f(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));
		bulletOrigin = sf::Vector2f(ownerPos.x  - projectileShape.getRadius(), ownerPos.y - projectileShape.getRadius());
	}
	else {
		// Get positions
		targetPosition = _target->getPosition();
		bulletOrigin = sf::Vector2f(ownerPos.x + ownerObject->getRadius() - projectileShape.getRadius(), ownerPos.y + ownerObject->getRadius() - projectileShape.getRadius());
	}

	// Calcul de la direction du projectile
	sf::Vector2f bulletDirection = targetPosition - bulletOrigin;

	managerEntity.GetParticleSystem().Burst(bulletOrigin, 20, 300, 0.15, 2, sf::Color::Yellow, targetPosition, 20);	  // Burst preset tir canon

	// Normalisation du vecteur pour obtenir une direction unitaire (longueur 1)
	float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (length != 0)
	{
		bulletDirection /= length;
	}


	// Nouveau projectile
	projectileShape.setPosition(bulletOrigin.x, bulletOrigin.y);
	window.draw(projectileShape);
	
	switch (entityFaction)
	{
		case Faction::PlayerFaction:
			managerEntity.AddEntity(new Projectile(managerEntity, collisionDetection, EntityType::Projectile_Entity, Faction::PlayerFaction, CollisionType::Circle, bulletOrigin, bulletDirection, 0, _bulletSpeed, projectileShape));
			break;

		case Faction::EnemiesFaction:
			managerEntity.AddEntity(new Projectile(managerEntity, collisionDetection, EntityType::Projectile_Entity, Faction::EnemiesFaction, CollisionType::Circle, bulletOrigin, bulletDirection, 0, _bulletSpeed, projectileShape));
			break;

		default:
			break;
	}

}


void Weapon::CheckRotationAim(sf::RectangleShape& aimShape, sf::RenderWindow& window)
{
	/*
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f origin = sf::Vector2f(aimShape.getPosition().x + aimShape.getSize().x / 2, aimShape.getPosition().y + aimShape.getSize().y / 2);
	//aimShape.setOrigin(aimShape.getSize().x / 2, aimShape.getSize().y / 2);
	sf::Vector2f down = sf::Vector2f(0, 1);

	sf::Vector2f bulletDirection = static_cast<sf::Vector2f>(mousePosition) - origin;

	// Normaliser le vecteur de direction
	float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (length != 0) {
		bulletDirection /= length;
	}

	//float angle = atan2(down.y, down.x) - atan2(bulletDirection.y, bulletDirection.x);
	float angle = atan2((mousePosition.y - origin.y), (mousePosition.x - origin.x));

	// Conversion de l'angle en degrés
	angle = angle * 180.0 / atan(1) * 4; // (atan(1) * 4 = pi)

	if (angle < 0)
	{
		angle = 360 -(-angle);

	}

	std::cout << "angle : " << angle << std::endl;

	aimShape.setRotation(angle);*/

	sf::Vector2f curPos;
	curPos.x = aimShape.getGlobalBounds().left;
	curPos.y = aimShape.getGlobalBounds().top;

	sf::Vector2i position;

	if (_target == nullptr) {
		position = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));
	}
	else {
		position = sf::Vector2i(_target->getPosition().x, _target->getPosition().y);
	}

	

	const float PI = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;
	float rotation = (atan2(dy, dx)) * 180 / PI;

	aimShape.setRotation(rotation + 90);
}



void Weapon::Update(sf::RenderWindow& window, float deltaTime) {
	
	if (_target == nullptr) {
		aimRectangle.setPosition(ownerObject->getPosition().x, ownerObject->getPosition().y);
	}
	else {
		aimRectangle.setPosition(ownerObject->getPosition().x + (ownerObject->getRadius() * 1.0f), ownerObject->getPosition().y + (ownerObject->getRadius() * 1.0f));
	}



	if (_target == nullptr) {
		// Verif si il peut tirer (en fonction de fire rate)
		if (shootPressed)
		{
			timeSinceLastShoot += deltaTime;
			if (timeSinceLastShoot >= FireRate)
			{
				shootPressed = false;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			if (!shootPressed)
			{
				shootPressed = true;
				timeSinceLastShoot = 0;
				Shoot(window);
			}
		}
	}
	

	CheckRotationAim(aimRectangle, window);
	window.draw(aimRectangle);
}

