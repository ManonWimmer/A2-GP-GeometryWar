#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "CollisionDetection.h"
#include "Entity.h"

class ManagerEntity;

class Player: public Entity
{
public :

	Player(ManagerEntity& managerEntity, CollisionDetection& collisionDetection);

	sf::Vector2f MovePlayer(sf::RenderWindow& window, CollisionDetection, float, float);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

	
	void CheckInvincibility(float);

	sf::CircleShape circleShape;

	int pv;

	float invincibilityCooldown;

	float invincibilityTime;

	bool isInvincible;
};



#endif