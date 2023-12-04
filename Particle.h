#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
public:
	Particle();
	Particle(int);
	Particle(int, int);
	Particle(int, int, int, sf::Color);

	void Move();

	sf::CircleShape circleShape;

	float lifeTime;
	float currenLifeTime;

	float speed;

	sf::Vector2f dir;
};

