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

// gestion bullet walls !!!!!!!!!!!!!!!!!!!!!!
bool CollisionDetection::BulletTouchWall(Projectile& bullet)
{
	std::list<sf::RectangleShape>::iterator it = this->rectList.begin();
	while (it != this->rectList.end())
	{
		if (CirclePartialyInSquare(bullet.ProjectileShape, *it, bullet.ProjectileShape.getPosition()))
		{
			return true;
		}
		else 
		{
			it++;
		}
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
			it = bulletsList.erase(it);
		}

		it++;
	}
}
void CollisionDetection::WeaponBulletsCollideWall(std::list<Weapon*> weaponsList)
{
	std::list<Weapon*>::iterator it = weaponsList.begin();

	while (it != weaponsList.end())
	{
		BulletsCollideWall((*it)->WeaponPtrProjectiles);

		it++;
	}
}
// Fin bulletwalls!!!!!!!!!!!!!!!!!!!!!!!!!!

// Gestion bulletsPlayer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool CollisionDetection::BulletsTouchPlayerCheck(Player& player, std::list<Projectile*>& bulletsList)
{
	std::list<Projectile*>::iterator it = bulletsList.begin();

	while (it != bulletsList.end())
	{
		if (CircleIsPartiallyInCircle((*it)->ProjectileShape, player.circleShape, (*it)->ProjectileShape.getPosition()))
		{
			if (!(player.isInvincible))
			{
				it = bulletsList.erase(it);
				return true;
			}
		}

		it++;
	}
	return false;
}
void CollisionDetection::WeaponBulletsTouchPlayerCheck(Player& player, std::list<Weapon*> enemyWeapons)
{
	std::list<Weapon*>::iterator it = enemyWeapons.begin();

	while (it != enemyWeapons.end())
	{
		if (BulletsTouchPlayerCheck(player, (*it)->WeaponPtrProjectiles))
		{
			if (!(player.isInvincible))
			{
				// reduire pv player
				player.pv -= 10;
			}
		}

		it++;
	}
}
// Fin bulletsPlayer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// Gestion BulletsEnnemy !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void CollisionDetection::BulletsTouchEnemyCheck(AI_Agent& enemy, Weapon& playerWeapon)
{
	//std::cout << "projectiles : " << playerWeapon.WeaponPtrProjectiles.size() << std::endl;


	for (const Projectile* projectile : playerWeapon.WeaponPtrProjectiles)
	{

		if (CircleIsPartiallyInCircle(projectile->ProjectileShape, enemy.GetCircle(), projectile->ProjectileShape.getPosition()))
		{
			std::cout << "Rentre dans le cercle" << std::endl;

			// reduire pv enemy
			enemy.DecreaseLife(34);

		}

	}


	//std::list<Projectile*>::iterator it = playerWeapon.WeaponPtrProjectiles.end();

	//while (it != playerWeapon.WeaponPtrProjectiles.end())
	//{
	//	std::cout << "Pas encore dans le cercle" << std::endl;

	//	if (CircleIsPartiallyInCircle((*it)->ProjectileShape, enemy.GetCircle(), (*it)->ProjectileShape.getPosition()))
	//	{
	//		std::cout << "Rentre dans le cercle" << std::endl;
	//		// reduire pv enemy
	//		enemy.DecreaseLife(34);

	//		it = playerWeapon.WeaponPtrProjectiles.erase(it);
	//	}
	//
	//	it++;
	//}
}
// Fin bulletsEnnemy !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

