#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "EntityEnums.h"

class Player;
class AI_Agent;
class Projectile;
class Weapon;
class ManagerEntity;
class Entity;

class CollisionDetection
{
public :

	CollisionDetection() {

	}

	CollisionDetection(std::list<sf::RectangleShape> rectListTemp)
	{
		rectList = rectListTemp;
	}

	void CheckAllEntitiesCollisions(ManagerEntity& managerEntity);
	//bool PointInsideSquare(float, float, sf::RectangleShape);


	sf::Vector2f ClampCircleOutsideRectangles(sf::CircleShape&, std::list<sf::RectangleShape>, sf::Vector2f, sf::Vector2f);
	sf::Vector2f ClampCircleInsideRectangle(sf::CircleShape&, sf::RectangleShape, sf::Vector2f, sf::Vector2f);


	void BulletsCollideWall(std::list<Projectile*>&);
	void WeaponBulletsCollideWall(std::list<Weapon*>);


	void WeaponBulletsTouchPlayerCheck(Player&, std::list<Weapon*> enemyWeapons);
	bool BulletsTouchPlayerCheck(Player&, std::list<Projectile*>& bulletsList);

	std::list<sf::RectangleShape> rectList;

	std::list<sf::CircleShape> playerBullets;
	std::list<sf::CircleShape> enemiesBullets;


private:


	bool CircleIsInCircle(sf::CircleShape circle1, sf::CircleShape circle2);
	void KeepCircleOutsideRectangle(sf::CircleShape circle, sf::RectangleShape rectangle);




	bool CircleIsPartiallyInCircle(sf::CircleShape, sf::CircleShape, sf::Vector2f);

	bool CircleIsInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	bool CirclePartialyInSquare(sf::CircleShape, sf::RectangleShape, sf::Vector2f);

	bool BulletTouchWall(Projectile&);
};

