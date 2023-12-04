#include "Particle.h"

Particle::Particle()
{
	this->lifeTime = 5;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = 5;

	this->dir = sf::Vector2f(0,1);
}
Particle::Particle(int speed)
{
	this->lifeTime = 5;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	this->dir = sf::Vector2f(0, 1);
}
Particle::Particle(int speed, int lifeTime)
{
	this->lifeTime = lifeTime;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	this->dir = sf::Vector2f(0, 1);
}
Particle::Particle(int speed, int lifeTime, int size, sf::Color color)
{
	this->lifeTime = lifeTime;

	sf::CircleShape circle;
	circle.setFillColor(color);
	circle.setRadius(size);

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	this->dir = sf::Vector2f(0, 1);
}

void Particle::Move()
{
	dir *= speed;
	sf::Vector2f pos = this->circleShape.getPosition();
	pos += this->dir;
	this->circleShape.setPosition(pos);
}