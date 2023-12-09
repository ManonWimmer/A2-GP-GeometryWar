#pragma once
#include <SFML/Graphics.hpp>


class MathLib
{
public:
	static sf::Vector2f NormalizedVector(sf::Vector2f vector);
	static float GetMagnitude(sf::Vector2f vector);

};

