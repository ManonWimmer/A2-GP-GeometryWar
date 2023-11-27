#include "projectile.h"
#include <SFML/Graphics.hpp>

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f direction, float currentTime, int speed, sf::CircleShape projectileShape)
{
	this->_origin = origin;
	this->_direction = direction;
	this->CurrentTime = currentTime;
	this->_speed = speed;
	this->_projectileShape = projectileShape;
}

void Projectile::MoveProjectile(float deltaTime) 
{
	sf::Vector2f movement = _direction * static_cast<float>(_speed) * deltaTime;
	_projectileShape.move(movement);
}