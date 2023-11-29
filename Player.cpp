#include "Player.h"
#include "CollisionDetection.h"
#include <list>


Player::Player()
{
	sf::CircleShape tempShape;

	tempShape.setRadius(20);
	tempShape.setPosition(640, 360);
	tempShape.setFillColor(sf::Color::Red);

	this->circleShape = tempShape;

}

sf::Vector2f Player::MovePlayer(CollisionDetection collManager, float deltaTime, float cubeSpeed)
{
	CollisionDetection collisionManager = collManager;

	sf::Vector2f pos = this->circleShape.getPosition();
	sf::Vector2f tempPos;
	tempPos.x = pos.x;
	tempPos.y = pos.y;

	sf::Vector2f dir;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		dir.x = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		dir.x = 1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		dir.y = -1;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		dir.y = 1;


	float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (length != 0)
	{
		dir /= length;
	}
	dir *= cubeSpeed * deltaTime;

	pos.x = collisionManager.ClampCircleOutsideRectangles(this->circleShape, collisionManager.rectList, sf::Vector2f(pos.x + dir.x, pos.y), pos).x;
	pos.y = collisionManager.ClampCircleOutsideRectangles(this->circleShape, collisionManager.rectList, sf::Vector2f(pos.x, pos.y + dir.y), pos).y;

	return pos;
}