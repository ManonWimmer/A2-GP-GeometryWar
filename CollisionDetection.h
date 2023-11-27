#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

class CollisionDetection
{
public :

	bool CircleIsInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f, sf::Vector2f);

	sf::Vector2f ClampCircleOutsideRectangles(sf::CircleShape&, std::list<sf::RectangleShape>, sf::Vector2f, sf::Vector2f);

	sf::Vector2f ClampCircleInsideRectangle(sf::CircleShape&, sf::RectangleShape, sf::Vector2f, sf::Vector2f);

	std::list<sf::RectangleShape> rectList;
};

