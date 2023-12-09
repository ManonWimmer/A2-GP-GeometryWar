#include "CollisionDetection.h"
#include "Player.h"		// -> re include dans le cpp car class incomplet
#include "AI_Agent.h"	// -> re include dans le cpp car class incomplet
#include "Projectile.h"
#include "Weapon.h"
#include "ManagerEntity.h"
#include "Entity.h"
#include "ParticleSystem.h"
#include "SaveAndLoadMap.h"
#include "Building.h"
#include "GameManager.h"





//bool CollisionDetection::PointInsideSquare(float x, float y, sf::RectangleShape rect)
//{
//
//}
constexpr int PLAYER_DMG = 34;
constexpr int AI_AGENT_DMG = 20;



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

float CollisionDetection::SimpleClamp(float value, float low, float high)
{
	return (value < low) ? low : (value > high) ? high : value;
}


bool CollisionDetection::CirclePartialyInSquare(sf::CircleShape circle, sf::RectangleShape rect, sf::Vector2f nextPosition)
{
	//float rw = rect.getSize().x;
	//float rh = rect.getSize().y;

	//
	//float rxTL = rect.getPosition().x;
	//
	//float ryTR = rect.getPosition().y;


	//float cr = circle.getRadius();

	//
	//float cx = nextPosition.x + cr;
	//
	//float cy = nextPosition.y + cr;



	//if ((cx - cr >= rxTL && cx - cr <= rxTL + rw) && (cy - cr >= ryTR && cy - cr <= ryTR + rh))	// Si point gauche haut cercle dans rectangle
	//{
	//	return true;
	//}
	//else if ((cx + cr >= rxTL && cx + cr <= rxTL + rw) && (cy - cr >= ryTR && cy - cr <= ryTR + rh))	// Si point droit haut cercle dans rectangle
	//{
	//	return true;
	//}
	//else if ((cx - cr >= rxTL && cx - cr <= rxTL + rw) && (cy + cr >= ryTR && cy + cr <= ryTR + rh))	// Si point bas gauche cercle dans rectangle
	//{
	//	return true;
	//}
	//else if ((cx + cr >= rxTL && cx + cr <= rxTL + rw) && (cy + cr >= ryTR && cy + cr <= ryTR + rh))	// Si point bas droit cercle dans rectangle
	//{
	//	return true;
	//}
	//return false;



	float rw = rect.getSize().x;
	float rh = rect.getSize().y;

	float rxCenter = rect.getPosition().x;
	float ryCenter = rect.getPosition().y;

	float cr = circle.getRadius();

	float cx = nextPosition.x;
	float cy = nextPosition.y;

	// Calculate the distance between the center of the circle and the center of the rectangle
	float dx = std::abs(cx - rxCenter);
	float dy = std::abs(cy - ryCenter);

	// Check if the distance is within the bounds of the rectangle
	if (dx <= (rw / 2.0f + cr) && dy <= (rh / 2.0f + cr)) {
		return true; 
	}

	return false; 
}

bool CollisionDetection::CircleIsInCircle(sf::CircleShape& circle1, sf::CircleShape& circle2)
{
	float distance = static_cast<float>(sqrt(pow(circle1.getPosition().x - circle2.getPosition().x, 2) + pow(circle1.getPosition().y - circle2.getPosition().y, 2)));

	if (distance <= circle1.getRadius() + circle2.getRadius()) {
		return true;
	}
	else {
		return false;
	}
}



void CollisionDetection::KeepCircleOutsideCircle(sf::CircleShape& circle1, sf::CircleShape& circle2)
{
	sf::Vector2f vecteurDirecteur = AI_Agent::NormalizedVector(circle1.getPosition() - circle2.getPosition());

	float currentDistance = static_cast<float>(sqrt(pow(circle1.getPosition().x - circle2.getPosition().x, 2) + pow(circle1.getPosition().y - circle2.getPosition().y, 2)));
	float maxDistance = circle1.getRadius() + circle2.getRadius();

	float offset = maxDistance - currentDistance;

	circle1.setPosition(circle1.getPosition() + (vecteurDirecteur * offset));
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
		if (managerEntity.GetEntityGarbage().find(i->first) != managerEntity.GetEntityGarbage().end()) continue;

		// Check if the current entity should be simulated
		if (i->first->GetEntityCollisionType() == CollisionType::None_CollisionType) continue;

		// Since only the moving objects are moving I don't calcuate collisions based on static object such as building entity.
		if (i->first->GetEntityType() == EntityType::Building_Entity) continue;


		for (auto x = managerEntity.GetEntityDictionary().begin(); x != managerEntity.GetEntityDictionary().end(); ++x)
		{
			if (managerEntity.GetEntityGarbage().find(x->first) != managerEntity.GetEntityGarbage().end()) continue;

			// Check if the current entity is simulating with itself
			if (i->first == x->first) continue;
			// Check if the second entity have collision
			if (x->first->GetEntityCollisionType() == CollisionType::None_CollisionType) continue;
			// Check if entities are from the same faction
			if (i->first->GetEntityFaction() == x->first->GetEntityFaction()) continue;


			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Player_Entity)
			{

				if (CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape()))
				{
					std::cout << "Rentre dans le cercle" << std::endl;

					managerEntity.RemoveEntity(i->first);
					x->first->DecreaseLife(AI_AGENT_DMG);

					managerEntity.GetParticleSystem().Burst(x->first->GetEntityCircleShape().getPosition() + sf::Vector2f(x->first->GetEntityCircleShape().getRadius(), x->first->GetEntityCircleShape().getRadius()), 35, 100, 0.2, 2, sf::Color::Red, i->first->GetEntityCircleShape().getPosition() + sf::Vector2f(i->first->GetEntityCircleShape().getRadius(), i->first->GetEntityCircleShape().getRadius()), 70);
					break;
				}
			}

			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::AI_Entity)
			{
				if (CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape()))
				{
					//std::cout << "Rentre dans le cercle" << std::endl;
					managerEntity.RemoveEntity(i->first);
					x->first->DecreaseLife(PLAYER_DMG);

					managerEntity.GetParticleSystem().Burst(x->first->GetEntityCircleShape().getPosition() + sf::Vector2f(x->first->GetEntityCircleShape().getRadius(), x->first->GetEntityCircleShape().getRadius()), 35, 100, 0.2, 2, sf::Color::Red, i->first->GetEntityCircleShape().getPosition() + sf::Vector2f(i->first->GetEntityCircleShape().getRadius(), i->first->GetEntityCircleShape().getRadius()), 70);
					break;
				}
			}

			if (i->first->GetEntityType() == EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Building_Entity)
			{
				if (x->first->GetEntityCollisionType() == CollisionType::Rectangle && CirclePartialyInSquare(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape(), i->first->GetEntityCircleShape().getPosition())) {
					std::cout << "Collision avec mur rectangulaire ou carre" << std::endl;
					managerEntity.GetParticleSystem().Burst(i->first->GetEntityCircleShape().getPosition(), 10, 200, 0.1, 2, sf::Color::White, sf::Vector2f(-1, -1), 360);
					managerEntity.RemoveEntity(i->first);
					
					break;
				}

				if (x->first->GetEntityCollisionType() == CollisionType::Circle && CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape())) {
					std::cout << "Collision avec mur circulaire" << std::endl;
					managerEntity.RemoveEntity(i->first);
					break;
				}
			}
			
			
			if (i->first->GetEntityType() != EntityType::Projectile_Entity && x->first->GetEntityType() == EntityType::Building_Entity) {

				//if (x->first->GetEntityCollisionType() == CollisionType::Rectangle && CirclePartialyInSquare(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape(), i->first->GetEntityCircleShape().getPosition())) {
				//	std::cout << "Collision avec mur rectangulaire ou carre" << std::endl;

				//	//KeepCircleOutsideRectangle(i->first->GetEntityCircleShape(), x->first->GetEntityRectangleShape());
				//	break;
				//}


				if (x->first->GetEntityCollisionType() == CollisionType::Circle && CircleIsInCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape())) {
					//std::cout << "Collision avec mur circulaire" << std::endl;
					KeepCircleOutsideCircle(i->first->GetEntityCircleShape(), x->first->GetEntityCircleShape());
					break;
				}
			}

		}

	}


}

sf::Vector2f CollisionDetection::ClampCircleOutsideRectangles(sf::CircleShape& circle, sf::Vector2f nextPosition, sf::Vector2f currentPosition)
{
	
	std::list<Building*>& buildingsList = _gameManager->GetMapManager().GetBuildings();
	std::list<Building*>::iterator it = buildingsList.begin();

	std::list<sf::RectangleShape*> listRectangles;

	// Getting all rectangles type building
	while (it != buildingsList.end())	// Parcours Liste
	{
		if ((*it)->GetEntityCollisionType() == CollisionType::Rectangle) {
			listRectangles.push_back(&(*it)->GetEntityRectangleShape());
		}
		it++;
	}

	std::list<sf::RectangleShape*>::iterator it_r = listRectangles.begin();

	while (it_r != listRectangles.end())	// Parcours Liste
	{
		if (CollisionDetection::CirclePartialyInSquare(circle, **it_r, nextPosition))	// Si nextPosition dans rectangle
		{
			return currentPosition;
		}
		it_r++;
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

GameManager& CollisionDetection::GetGameManager()
{
	return *_gameManager;
}

void CollisionDetection::SetGameManager(GameManager* gameManager)
{
	_gameManager = gameManager;
}