#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>
#include "CollisionDetection.h"
#include "EntityEnums.h"
#include "Entity.h"

class ManagerEntity;
class Weapon;
class Light;

class Player: public Entity
{
public :
	Player(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f position);

	sf::Vector2f MovePlayer(sf::RenderWindow& window, CollisionDetection, float, float);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;
	Weapon* ptrPistol;

	//Function coming from Entity
	sf::CircleShape& GetEntityCircleShape() override;
	virtual void OnDestroy() override;

	void CheckInvincibility(float);
	sf::CircleShape circleShape;
	int pv;
	float invincibilityCooldown;
	float invincibilityTime;
	bool isInvincible;
	sf::CircleShape fvCorner1;


	Light* _light;

};



#endif