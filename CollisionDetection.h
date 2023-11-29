#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "Projectile.h"

class CollisionDetection
{
public :

	CollisionDetection(std::list<sf::RectangleShape> rectListTemp)
	{
		rectList = rectListTemp;
	}

	/*bool PointInsideSquare(float, float, sf::RectangleShape)*/;

	bool CircleIsPartiallyInCircle(sf::CircleShape, sf::CircleShape, sf::Vector2f);

	bool CircleIsInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	bool CirclePartialyInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	sf::Vector2f ClampCircleOutsideRectangles(sf::CircleShape&, std::list<sf::RectangleShape>, sf::Vector2f, sf::Vector2f);

	sf::Vector2f ClampCircleInsideRectangle(sf::CircleShape&, sf::RectangleShape, sf::Vector2f, sf::Vector2f);


	bool BulletTouchWall(Projectile&);

	void BulletsCollideWall(std::list<Projectile*>&);


	std::list<sf::RectangleShape> rectList;

};

