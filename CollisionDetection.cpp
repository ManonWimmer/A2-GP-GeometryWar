#include "CollisionDetection.h"


bool CollisionDetection::CircleIsInSquare(sf::CircleShape circle, sf::RectangleShape rect)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	float rxTL = rect.getPosition().x - (rw / 2);
	float ryTR = rect.getPosition().y + (rh / 2);


	float cx = circle.getPosition().x;
	float cy = circle.getPosition().y;

	float cr = circle.getRadius();

	if ((cx - cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr <= ryTR && cy + cr >= ryTR - rh))
	{
		return true;
	}
	return false;
}

void CollisionDetection::ClampCircleOutsideRectangles(sf::CircleShape& circle, std::list<sf::RectangleShape> listRect)
{
	listRect = CollisionDetection::rectList;

	std::list<sf::RectangleShape>::iterator it = listRect.begin();

	while (it != listRect.end())
	{
		bool isInSquare = CollisionDetection::CircleIsInSquare(circle, *it);
		if (isInSquare)
		{
			std::cout << "One is in square" << std::endl;

			// Bloquer le circle
			/* circle.setPosition(circle.getPosition()); */
		}
	}
}