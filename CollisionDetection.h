#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

class CollisionDetection
{
public :
	bool CircleIsInSquare(sf::CircleShape, sf::RectangleShape);

	void ClampCircleOutsideRectangles(sf::CircleShape&, std::list<sf::RectangleShape>);

	std::list<sf::RectangleShape> rectList;
};

