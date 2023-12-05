#include "Particle.h"

#include <cstdlib>
#include <ctime>

Particle::Particle()
{
	this->lifeTime = 5;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = 5;

	this->dir = sf::Vector2f(0,1);
}
Particle::Particle(float speed)
{
	this->lifeTime = 5;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	this->dir = sf::Vector2f(0, 1);
}
Particle::Particle(float speed, float lifeTime)
{
	this->lifeTime = lifeTime;

	sf::CircleShape circle;

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	this->dir = sf::Vector2f(0, 1);
}
Particle::Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color)
{
	this->lifeTime = lifeTime;

	sf::CircleShape circle;
	circle.setFillColor(color);
	circle.setRadius(size);
	circle.setPosition(position);

	this->circleShape = circle;
	this->currenLifeTime = 0;

	this->speed = speed;

	//srand((unsigned int)time(NULL));	// !!!! Attention celle déclaration est appelé une seule fois dans le main sinon le rand sera bloqué sur une constante
	//std::srand(std::time(nullptr));

	float randomValue1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));
	float randomValue2 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));

	this->dir = sf::Vector2f(randomValue1, randomValue2);
}

void Particle::Move(float deltaTime)
{
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
	dir *= speed * deltaTime;

	sf::Vector2f pos = this->circleShape.getPosition();
	pos += this->dir;
	this->circleShape.setPosition(pos);
}