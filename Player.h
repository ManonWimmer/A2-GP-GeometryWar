#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "CollisionDetection.h"

class Player
{
public :

	Player();

	sf::Vector2f MovePlayer(CollisionDetection, float, float);

	
	void CheckInvincibility(float);

	sf::CircleShape circleShape;

	int pv;

	float invincibilityCooldown;

	float invincibilityTime;

	bool isInvincible;
};

