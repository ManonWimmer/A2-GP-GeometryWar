#include "CollisionDetection.h"

//bool CollisionDetection::PointInsideSquare(float x, float y, sf::RectangleShape rect)
//{
//
//}

bool CollisionDetection::CircleIsInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	//float rxTL = rect.getPosition().x - (rw / 2);
	float rxTL = rect.getPosition().x;
	//float ryTR = rect.getPosition().y + (rh / 2);
	float ryTR = rect.getPosition().y;


	float cr = circle.getRadius();

	//float cx = nextPosition.x;
	float cx = nextPosition.x + cr;
	//float cy = nextPosition.y;
	float cy = nextPosition.y + cr;



	if ((cx - cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr >= ryTR && cy + cr <= ryTR + rh))		// Si coordonnées dans rectangle
	//if ((cx - cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr <= ryTR && cy + cr >= ryTR - rh))	// a utiliser si réferentiel pas retourné
	{
		return true;
	}
	return false;
}


bool CollisionDetection::CirclePartialyInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	//float rxTL = rect.getPosition().x - (rw / 2);
	float rxTL = rect.getPosition().x;
	//float ryTR = rect.getPosition().y + (rh / 2);
	float ryTR = rect.getPosition().y;


	float cr = circle.getRadius();

	//float cx = nextPosition.x;
	float cx = nextPosition.x + cr;
	//float cy = nextPosition.y;
	float cy = nextPosition.y + cr;



	if ((cx - cr >= rxTL && cx - cr <= rxTL + rw) && (cy - cr >= ryTR && cy - cr <= ryTR + rh))	// Si point gauche haut cercle dans rectangle
	{
		return true;
	}
	else if ((cx + cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr >= ryTR && cy - cr <= ryTR + rh))	// Si point droit haut cercle dans rectangle
	{
		return true;
	}
	else if ((cx - cr >= rxTL && cx - cr <= rxTL + rw) && (cy + cr >= ryTR && cy + cr <= ryTR + rh))	// Si point bas gauche cercle dans rectangle
	{
		return true;
	}
	else if ((cx + cr >= rxTL && cx + cr <= rxTL + rw) && (cy + cr >= ryTR && cy + cr <= ryTR + rh))	// Si point bas droit cercle dans rectangle
	{
		return true;
	}
	return false;
}

sf::Vector2f CollisionDetection::ClampCircleOutsideRectangles(sf::CircleShape& circle, std::list<sf::RectangleShape> listRect, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	listRect = CollisionDetection::rectList;

	std::list<sf::RectangleShape>::iterator it = listRect.begin();

	while (it != listRect.end())	// Parcours Liste
	{
		if (CollisionDetection::CirclePartialyInSquare(circle, *it, nextPosition))	// Si nextPosition dans rectangle
		{
			return currentPosition;
		}
		it++;
	}
	return nextPosition;
}

sf::Vector2f CollisionDetection::ClampCircleInsideRectangle(sf::CircleShape& circle, sf::RectangleShape rect, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	if (CollisionDetection::CircleIsInSquare(circle, rect, nextPosition))	// Si nextPosition dans rectangle
	{
		return nextPosition;
	}
	return currentPosition;
}