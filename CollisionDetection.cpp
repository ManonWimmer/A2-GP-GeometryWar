#include "CollisionDetection.h"
#include "Player.h"		// -> re include dans le cpp car class incomplet
#include "AI_Agent.h"	// -> re include dans le cpp car class incomplet
#include "Projectile.h"
#include "Weapon.h"
#include "ManagerEntity.h"
#include "Entity.h"


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

bool CollisionDetection::CircleIsInCircle(sf::CircleShape circle1, sf::CircleShape circle2)
{
	float distance = sqrt(pow(circle1.getPosition().x - circle2.getPosition().x, 2) + pow(circle1.getPosition().y - circle2.getPosition().y, 2));

	if (distance <= circle1.getRadius() + circle2.getRadius()) {
		return true;
	}
	else {
		return false;
	}
}

void CollisionDetection::KeepCircleOutsideRectangle(sf::CircleShape circle, sf::RectangleShape rectangle)
{
	float dx = circle.getPosition().x - (rectangle.getPosition().x + rectangle.getSize().x / 2);
	float dy = circle.getPosition().y - (rectangle.getPosition().y + rectangle.getSize().y / 2);

	float maxDistance = sqrt(pow(rectangle.getSize().x / 2, 2) + pow(rectangle.getSize().y / 2, 2)) + circle.getRadius();


	if (sqrt(dx * dx + dy * dy) < maxDistance) {
		double angle = atan2(dy, dx);

		sf::Vector2f newPosition;
		newPosition.x = rectangle.getPosition().x + rectangle.getSize().x / 2 + maxDistance * cos(angle);
		newPosition.y = rectangle.getPosition().y + rectangle.getSize().y / 2 + maxDistance * sin(angle);

		circle.setPosition(newPosition);
	}
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

void CollisionDetection::CheckAllEntitiesCollisions(ManagerEntity& managerEntity)
{

	for (auto i = managerEntity.GetEntityDictionary().begin(); i != managerEntity.GetEntityDictionary().end(); ++i) 
	{
		// Check if the current entity should be simulated
		if (i->first->GetEntityCollisionType() == CollisionType::None_CollisionType) continue;

		// Since only the Circle objects are moving I calcuate collision only for circle shape as the base
		if (i->first->GetEntityCollisionType() == CollisionType::Rectangle) continue;


		for (auto x = managerEntity.GetEntityDictionary().begin(); x != managerEntity.GetEntityDictionary().end(); ++x)
		{
			// Check if the current entity is simulating with itself
			if (i->first == x->first) continue;

			// Check if the second entity have collision
			if (x->first->GetEntityCollisionType() == CollisionType::None_CollisionType) continue;


			// Check if entities are from the same faction
			if (i->first->GetEntityFaction() == x->first->GetEntityFaction()) continue;


			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Player_Entity)
			{
				//Applying damage.
			}

			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::AI_Entity)
			{
				if (CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape()))
				{
					std::cout << "Rentre dans le cercle" << std::endl;
					managerEntity.RemoveEntity(i->first);
					break;
				}
			}

			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Wall_Entity)
			{
				if (x->first->GetEntityCollisionType() == CollisionType::Rectangle && CirclePartialyInSquare(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape(), i->first->GetEntityCircleShape().getPosition())) {
					std::cout << "Collision avec mur rectangulaire ou carre" << std::endl;
					break;
				}

				if (x->first->GetEntityCollisionType() == CollisionType::Circle && CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape())) {
					std::cout << "Collision avec mur circulaire" << std::endl;
					break;
				}
			}
			
			
			if (i->first->GetEntityType() != EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Wall_Entity) {

				if (x->first->GetEntityCollisionType() == CollisionType::Rectangle && CirclePartialyInSquare(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape(), i->first->GetEntityCircleShape().getPosition())) {
					std::cout << "Collision avec mur rectangulaire ou carre" << std::endl;
					KeepCircleOutsideRectangle(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape());
					break;
				}


				if (x->first->GetEntityCollisionType() == CollisionType::Circle && CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape())) {
					std::cout << "Collision avec mur circulaire" << std::endl;
					break;
				}
			}

		}

	}


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
	/*std::list<Weapon*>::iterator it = weaponsList.begin();

	while (it != weaponsList.end())
	{
		BulletsCollideWall((*it)->WeaponPtrProjectiles);

		it++;
	}*/
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
	//std::list<Weapon*>::iterator it = enemyWeapons.begin();

	//while (it != enemyWeapons.end())
	//{
	//	if (BulletsTouchPlayerCheck(player, (*it)->WeaponPtrProjectiles))
	//	{
	//		if (!(player.isInvincible))
	//		{
	//			// reduire pv player
	//			player.pv -= 10;
	//		}
	//	}

	//	it++;
	//}
}
// Fin bulletsPlayer !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!



// Gestion BulletsEnnemy !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
bool CollisionDetection::BulletsTouchEnemyCheck(Entity& enemy, Entity& projectile)
{
	//std::cout << "projectiles : " << playerWeapon.WeaponPtrProjectiles.size() << std::endl;

	//std::cout << enemy.GetEntityCircleShape().getPosition().x << " ; " << enemy.GetEntityCircleShape().getPosition().y << std::endl;

	//std::cout << "TEST" << std::endl;

	if (CircleIsInCircle(projectile.GetEntityCircleShape(), enemy.GetEntityCircleShape()))
	{
		std::cout << "Rentre dans le cercle" << std::endl;
		return true;
		//enemy.DecreaseLife(34);
	}

	//for (const Projectile* projectile : playerWeapon.WeaponPtrProjectiles)
	//{

	//	if (CircleIsPartiallyInCircle(projectile->ProjectileShape, enemy.GetCircle(), projectile->ProjectileShape.getPosition()))
	//	{
	//		std::cout << "Rentre dans le cercle" << std::endl;

	//		// reduire pv enemy
	//		enemy.DecreaseLife(34);
	//	}

	//}


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

