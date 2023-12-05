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
Particle::Particle(sf::Vector2f position, float speed, float lifeTime, float size, sf::Color color, sf::Vector2i target)
{
	this->lifeTime = lifeTime;

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
	//std::srand(std::time(nullptr));

	//float randomValue1 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));
	//float randomValue2 = 1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1 - (-1))));

	sf::Vector2i targetPosition;
	sf::Vector2f bulletOrigin;
	targetPosition = target;
	bulletOrigin = position;
	float gap = 50;

	
	/*int length = sqrt(targetPosition.x * targetPosition.x + targetPosition.y * targetPosition.y);
	if (length != 0)
	{
		targetPosition /= length;
	}*/

	float randomValue1 = 1;
	float randomValue2 = 1;

	if (gap != targetPosition.x && gap != targetPosition.y)
	{
		randomValue1 = (targetPosition.x + gap) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((targetPosition.x + gap) - (targetPosition.x - gap))));
		randomValue2 = (targetPosition.y + gap) + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / ((targetPosition.y + gap) - (targetPosition.y - gap))));
	}
	float randomAngle = 70 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (70 - 0)));;
	int randomBin = 1 + static_cast <int> (rand()) / (static_cast <int> (RAND_MAX / (1 - 0)));
	
	if (randomBin == 1) {
		randomAngle = -randomAngle;
	}

	float angleRadians = randomAngle * (3.14159265359 / 180.0f);
	sf::Vector2f rotatedVector;
	sf::Vector2f originalVector;
	originalVector.x = targetPosition.x - position.x;
	originalVector.y = targetPosition.y - position.y;

	rotatedVector.x = std::cos(angleRadians) * (originalVector.x - position.x) - std::sin(angleRadians) * (originalVector.y - position.y) + position.x;
	rotatedVector.y = std::sin(angleRadians) * (originalVector.x - position.x) + std::cos(angleRadians) * (originalVector.y - position.y) + position.y;

	float length = rotatedVector.x * rotatedVector.x + rotatedVector.y * rotatedVector.y;
	if (length != 0) {
		rotatedVector /= length;
	}

	this->dir = sf::Vector2f(rotatedVector.x, rotatedVector.y);
	//this->dir.x = target.x - position.x;
	//this->dir.y = target.y - position.y;

	//this->dir = sf::Vector2f(randomValue1, randomValue2);
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