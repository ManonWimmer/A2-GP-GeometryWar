#pragma once
#include <iostream>
#include <list>
#include "Projectile.h"

#include "EntityEnums.h"
#include "Entity.h"
#include "ManagerEntity.h"
#include "GameManager.h"
#include "CollisionDetection.h"



enum WeaponType
{
	Pistol,
	Rifle,
	Shotgun
};



class Weapon : public Entity
{
public:

	Weapon(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, WeaponType weaponType, sf::CircleShape& ownerObject);
	Weapon(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, WeaponType weaponType, sf::CircleShape& ownerObject, sf::CircleShape* target);

	void Shoot(sf::RenderWindow& window);
	void CheckRotationAim(sf::RectangleShape&, sf::RenderWindow&);
	int FireTime;
	float FireRate;
	sf::CircleShape* _target = nullptr;
	sf::CircleShape* ownerObject;
	sf::RectangleShape aimRectangle;
	bool shootPressed = false;
	float timeSinceLastShoot = 0;

	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
	int _bulletSpeed;
	
};