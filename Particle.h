#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Particle
{
public:
	Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color, sf::Vector2f target, float angle);

	void Move(float deltaTime);

	sf::CircleShape circleShape;

	float lifeTime;
	float currenLifeTime;

	float speed;

	sf::Vector2f dir;

private:
	sf::CircleShape InitializeCircleShape(sf::Vector2f position, float size, sf::Color color);
	float InitializeRandomSpeed(float speed);
	sf::Vector2f InitializeRandomDir(sf::Vector2f position, sf::Vector2f target, float angle);
	float InitializeLifeTime(float lifeTime);
};

