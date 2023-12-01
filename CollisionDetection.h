#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Projectile.h"

class Player;
class AI_Agent;

class CollisionDetection
{
public :

	CollisionDetection() {

	}

	CollisionDetection(std::list<sf::RectangleShape> rectListTemp)
	{
		rectList = rectListTemp;
	}

	//bool PointInsideSquare(float, float, sf::RectangleShape);


	sf::Vector2f ClampCircleOutsideRectangles(sf::CircleShape&, std::list<sf::RectangleShape>, sf::Vector2f, sf::Vector2f);

	sf::Vector2f ClampCircleInsideRectangle(sf::CircleShape&, sf::RectangleShape, sf::Vector2f, sf::Vector2f);


	void BulletsCollideWall(std::list<Projectile*>&);


	void BulletsTouchPlayerCheck(Player&, std::list<Projectile*>&);

	void BulletsTouchEnemyCheck(AI_Agent&, std::list<Projectile*>&);


	std::list<sf::RectangleShape> rectList;

private:
	bool CircleIsPartiallyInCircle(sf::CircleShape, sf::CircleShape, sf::Vector2f);

	bool CircleIsInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	bool CirclePartialyInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	bool BulletTouchWall(Projectile&);
};

