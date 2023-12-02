#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Entity.h"
#include "ManagerEntity.h"
#include "GameManager.h"
#include "EntityEnums.h"

class Projectile : public Entity
{
public:
	Projectile(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f origin, sf::Vector2f direction, float currentTime, int speed, sf::CircleShape projectileShape);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

	//Function coming from Entity
	sf::CircleShape& GetEntityCircleShape() override;


	void MoveProjectile(float);
	float CurrentTime;
	sf::CircleShape ProjectileShape;
	
private:
	sf::Vector2f _origin;
	sf::Vector2f _direction;
	int _speed;
	
};
