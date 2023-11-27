#include <SFML/Graphics.hpp>
#pragma once

class Projectile
{
public:
	Projectile(sf::Vector2f, sf::Vector2f, float, int, sf::CircleShape); 
	void MoveProjectile(float);
	float CurrentTime;
	
private:
	sf::Vector2f _origin;
	sf::Vector2f _direction;
	int _speed;
	sf::CircleShape _projectileShape;
};
