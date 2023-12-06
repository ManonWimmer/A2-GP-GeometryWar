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
Particle::Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color, sf::Vector2i target, float angle)
{

	float randomLifeTime = (lifeTime + 0.3) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((lifeTime + 0.3) - (lifeTime / 2))));
	this->lifeTime = randomLifeTime;

	sf::CircleShape circle;
	circle.setFillColor(color);
	circle.setRadius(size);
	circle.setPosition(position);

	this->circleShape = circle;
	this->currenLifeTime = 0;

	//this->speed = speed;
	float randomSpeed = (speed+10) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((speed + 10) - (speed / 2))));
	this->speed = randomSpeed;
	

	//srand((unsigned int)time(NULL));	// !!!! Attention celle déclaration est appelé une seule fois dans le main sinon le rand sera bloqué sur une constante


	sf::Vector2f shootingDirection = sf::Vector2f(target.x, target.y) - position;

	// Ajout de la dispersion
	float angleVariation = angle;  // Angle de dispersion
	float randomAngle = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * angleVariation - angleVariation / 2.0f;

	// Rotation de la direction du tir (par rapport à la position en paramètre)
	float angleRadians = randomAngle * (3.14159265359 / 180.0f);
	sf::Vector2f rotatedDirection;
	rotatedDirection.x = std::cos(angleRadians) * shootingDirection.x - std::sin(angleRadians) * shootingDirection.y;
	rotatedDirection.y = std::sin(angleRadians) * shootingDirection.x + std::cos(angleRadians) * shootingDirection.y;

	// Normalisation
	float length = std::sqrt(rotatedDirection.x * rotatedDirection.x + rotatedDirection.y * rotatedDirection.y);
	if (length != 0)
	{
		rotatedDirection /= length;
	}

	this->dir = rotatedDirection;
}

void Particle::Move(float deltaTime)
{
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
	dir *= speed * deltaTime;

	if (circleShape.getRadius() - deltaTime * 3 > 0)
	{
			circleShape.setRadius(circleShape.getRadius() - deltaTime * 3);
	}

	sf::Vector2f pos = this->circleShape.getPosition();
	pos += this->dir;
	this->circleShape.setPosition(pos);
}