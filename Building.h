#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "EntityEnums.h"
#include "Entity.h"


class Building : public Entity
{

public:
	Building(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f spawnPoint, std::string buildingName);

	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

	void UpdateBuilding(sf::RenderWindow& window, float deltaTime);

	sf::CircleShape& GetEntityCircleShape() override;
	sf::RectangleShape& GetEntityRectangleShape() override;

	void ResetColor();
	void ReplaceOrigin();


	void SaveBuilding(std::ofstream& file);
	static Building* LoadBuilding(std::ifstream& file, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
	std::string buildingName;
private:
	sf::CircleShape buildingCircleShape;
	sf::RectangleShape buildingRectangleShape;

};

