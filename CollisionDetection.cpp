#include "CollisionDetection.h"
#include "Player.h"		// -> re include dans le cpp car class incomplet
#include "AI_Agent.h"	// -> re include dans le cpp car class incomplet


//bool CollisionDetection::PointInsideSquare(float x, float y, sf::RectangleShape rect)
//{
//
//}

bool CollisionDetection::CircleIsInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;


	float rxTL = rect.getPosition().x;
	
	float ryTR = rect.getPosition().y;


	float cr = circle.getRadius();

	
	float cx = nextPosition.x + cr;
	
	float cy = nextPosition.y + cr;



	if ((cx - cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr >= ryTR && cy + cr <= ryTR + rh))		// Si coordonnées dans rectangle
	{
		return true;
	}
	return false;
}


bool CollisionDetection::CirclePartialyInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition)
{
	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	
	float rxTL = rect.getPosition().x;
	
	float ryTR = rect.getPosition().y;


	float cr = circle.getRadius();

	
	float cx = nextPosition.x + cr;
	
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

bool CollisionDetection::CircleIsPartiallyInCircle(sf::CircleShape circle, sf::CircleShape circleColl, sf::Vector2f nextPosition)
{
	float clw = circleColl.getRadius() * 2;
	float clh = circleColl.getRadius() * 2;

	
	float clxTL = circleColl.getPosition().x;
	
	float clyTR = circleColl.getPosition().y;


	float cr = circle.getRadius();

	
	float cx = nextPosition.x + cr;
	
	float cy = nextPosition.y + cr;



	if ((cx - cr >= clxTL && cx - cr <= clxTL + clw) && (cy - cr >= clyTR && cy - cr <= clyTR + clh))	// Si point gauche haut cercle dans rectangle
	{
		return true;
	}
	else if ((cx + cr >= clxTL && cx + cr <= clxTL + clw) && (cy - cr >= clyTR && cy - cr <= clyTR + clh))	// Si point droit haut cercle dans rectangle
	{
		return true;
	}
	else if ((cx - cr >= clxTL && cx - cr <= clxTL + clw) && (cy + cr >= clyTR && cy + cr <= clyTR + clh))	// Si point bas gauche cercle dans rectangle
	{
		return true;
	}
	else if ((cx + cr >= clxTL && cx + cr <= clxTL + clw) && (cy + cr >= clyTR && cy + cr <= clyTR + clh))	// Si point bas droit cercle dans rectangle
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


bool CollisionDetection::BulletTouchWall(Projectile& bullet)
{
	std::list<sf::RectangleShape>::iterator it = this->rectList.begin();
	while (it != this->rectList.end())
	{
		/*if (CirclePartialyInSquare(bullet.shape, *it, bullet.shape.getPosition()))
		{
			return true;
		}
		else 
		{
			it++;
		}*/
	}

	return false;
}

void CollisionDetection::BulletsCollideWall(std::list<Projectile*>& bulletsList)
{
	std::list<Projectile*>::iterator it = bulletsList.begin();

	while (it != bulletsList.end())
	{
		if (BulletTouchWall(*(*(it))))
		{
			// Detruire bullet
		}

		it++;
	}
}

void CollisionDetection::BulletsTouchPlayerCheck(Player& player, std::list<Projectile*>& enemyBullets)
{
	std::list<Projectile*>::iterator it = enemyBullets.begin();

	while (it != enemyBullets.end())
	{
		if (CircleIsPartiallyInCircle((*it)->ProjectileShape, player.circleShape, (*it)->ProjectileShape.getPosition()))
		{
		    // Check invincibilité du player
			// Mort du player
		}

		it++;
	}
}

void CollisionDetection::BulletsTouchEnemyCheck(AI_Agent& enemy, std::list<Projectile*>& playerBullets)
{
	std::list<Projectile*>::iterator it = playerBullets.end();
	
	while (it != playerBullets.end())
	{
		if (CircleIsPartiallyInCircle((*it)->ProjectileShape, enemy.GetCircle(), (*it)->ProjectileShape.getPosition()))
		{
			// Appliquer dégat
			// Tuer l'ennemis
		}
	
		it++;
	}
}


