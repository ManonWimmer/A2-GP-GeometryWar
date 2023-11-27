#include "CollisionDetection.h"


bool CollisionDetection::CircleIsInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	float rxTL = rect.getPosition().x - (rw / 2);
	float ryTR = rect.getPosition().y + (rh / 2);


	float cx = nextPosition.x;
	float cy = nextPosition.y;

	float cr = circle.getRadius();

	if ((cx - cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr <= ryTR && cy + cr >= ryTR - rh))
	{
		return true;
	}
	return false;
}

sf::Vector2f CollisionDetection::ClampCircleOutsideRectangles(sf::CircleShape& circle, std::list<sf::RectangleShape> listRect, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	listRect = CollisionDetection::rectList;

	std::list<sf::RectangleShape>::iterator it = listRect.begin();

	while (it != listRect.end())
	{
		bool isInSquare = CollisionDetection::CircleIsInSquare(circle, *it, nextPosition, currentPosition);
		if (isInSquare)
		{
			std::cout << "One is in square" << std::endl;

			return currentPosition;
		}
	}
	return nextPosition;
}

sf::Vector2f CollisionDetection::ClampCircleInsideRectangle(sf::CircleShape& circle, sf::RectangleShape rect, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	if (CollisionDetection::CircleIsInSquare(circle, rect, nextPosition, currentPosition))
	{
		// Bloquer circle dans rect
		return nextPosition;
	}
	return currentPosition;
}