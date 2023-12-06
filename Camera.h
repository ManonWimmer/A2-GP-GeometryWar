#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityEnums.h"
#include "Entity.h"

class ManagerEntity;
class Player;

class Camera : public Entity 
{
public:
	//Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, Player* player, sf::View& mapView, sf::View& playerView);
	Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, Player* player, sf::View& mapView, sf::View& playerView);
	void Update(sf::RenderWindow& window, float deltaTime);

private:
	bool _shake;
	Player* _player;
	sf::View& _mapView;
	sf::View& _playerView;
};

