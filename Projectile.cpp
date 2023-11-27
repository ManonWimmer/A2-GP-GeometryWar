#include "projectile.h"
#include <SFML/Graphics.hpp>

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f direction, float currentTime, int speed)
{
	this->_origin = origin;
	this->_direction = direction;
	this->_currentTime = currentTime;
	this->_speed = speed;
}