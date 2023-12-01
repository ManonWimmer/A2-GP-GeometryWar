#include "EnemyBulletCollision.h"


//bool EnemyBulletCollision::BulletTouchWall(Projectile& bullet)
//{
//	std::list<sf::RectangleShape>::iterator it = this->rectList.begin();
//	while (it != this->rectList.end())
//	{
//		/*if (CirclePartialyInSquare(bullet.shape, *it, bullet.shape.getPosition()))
//		{
//			return true;
//		}
//		else
//		{
//			it++;
//		}*/
//	}
//
//	return false;
//}
//
//void EnemyBulletCollision::BulletsCollideWall(std::list<Projectile*>& bulletsList)
//{
//	std::list<Projectile*>::iterator it = bulletsList.begin();
//
//	while (it != bulletsList.end())
//	{
//		if (BulletTouchWall(*(*(it))))
//		{
//			// Detruire bullet
//		}
//
//		it++;
//	}
//}