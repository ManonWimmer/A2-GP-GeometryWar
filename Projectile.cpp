#include "projectile.h"
#include <SFML/Graphics.hpp>

Projectile::Projectile(sf::Vector2f origin, sf::Vector2f direction, float currentTime, int speed, sf::CircleShape projectileShape)
{
	this->_origin = origin;
	this->_direction = direction;
	this->CurrentTime = currentTime;
	this->_speed = speed;
	this->ProjectileShape = projectileShape;
}

void Projectile::MoveProjectile(float deltaTime) 
{
	//std::cout << "move projectile" << std::endl;
	sf::Vector2f movement = _direction * static_cast<float>(_speed) * deltaTime;
	ProjectileShape.move(movement);
	//std::cout << "new pos proj" << ProjectileShape.getPosition().x << " " << ProjectileShape.getPosition().y << std::endl;
}