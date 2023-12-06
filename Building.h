#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include "EntityEnums.h"
#include "Entity.h"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

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


	json SaveBuilding();
	static Building* LoadBuilding(json& file, ManagerEntity& managerEntity, CollisionDetection& collisionDetection);
	std::string buildingName;

private:
	sf::CircleShape buildingCircleShape;
	sf::RectangleShape buildingRectangleShape;

};

