#include "Particle.h"

#include <cstdlib>
#include <ctime>


Particle::Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color, sf::Vector2f target, float angle)
{
	this->lifeTime = InitializeLifeTime(lifeTime);

	this->currenLifeTime = 0;
	this->circleShape = InitializeCircleShape(position, size, color);

	this->speed = InitializeRandomSpeed(speed);

	this->dir = InitializeRandomDir(position, target, angle);
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

sf::CircleShape Particle::InitializeCircleShape(sf::Vector2f position, float size, sf::Color color)
{
	sf::CircleShape circle;
	circle.setFillColor(color);
	circle.setRadius(size);
	circle.setPosition(position);

	return circle;
}
float Particle::InitializeRandomSpeed(float speed)
{
	float randomSpeed = (speed + 10) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((speed + 10) - (speed / 2))));
	return randomSpeed;
}
sf::Vector2f Particle::InitializeRandomDir(sf::Vector2f position, sf::Vector2f target, float angle)
{
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

	return rotatedDirection;
}
float Particle::InitializeLifeTime(float lifeTime)
{
	float randomLifeTime = (lifeTime + lifeTime / 2) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((lifeTime + lifeTime / 4) - (lifeTime / 2))));
	return randomLifeTime;
}