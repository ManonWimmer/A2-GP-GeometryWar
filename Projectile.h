#include <SFML/Graphics.hpp>
#pragma once

class Projectile
{
public:
	Projectile(sf::Vector2f, sf::Vector2f, float, int);

private:
	sf::Vector2f _origin;
	sf::Vector2f _direction;
	float _currentTime;
	int _speed;
};
