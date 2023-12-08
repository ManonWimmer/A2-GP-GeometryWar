#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityEnums.h"
#include "Entity.h"
#include "GameManager.h"

class ManagerEntity;
class Player;
class GameManager;

class Camera : public Entity 
{
public:
	Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, GameManager& gameManager);
	void Update(sf::RenderWindow& window, float deltaTime);

	void ChangeToBig(sf::RenderWindow&);
	void ChangeToSmall(sf::RenderWindow&);

private:
	bool _shake;
	GameManager& _gameManager;
	//float _shakeInterval;
};

