#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Particle
{
public:
	Particle();
	Particle(float);
	Particle(float, float);
	Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color);

	void Move(float deltaTime);

	sf::CircleShape circleShape;

	float lifeTime;
	float currenLifeTime;

	float speed;

	sf::Vector2f dir;
};

