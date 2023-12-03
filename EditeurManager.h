#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <cfloat>

#include "EntityEnums.h"
#include "Entity.h"

class Building;

class EditeurManager : public Entity
{
public:
	EditeurManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
	void SpawningAnObject(sf::RenderWindow& window);
	void HoldingAnObject();
	void HoveringAnObject(sf::RenderWindow& window);

	float GetPositiveFloat(float value);
	float GetDistance(sf::Vector2f vector1, sf::Vector2f vector2);
	
	bool IsPointInsideCircle(sf::CircleShape& circle, sf::Vector2f point);
	bool IsPointInsideRectangle(sf::RectangleShape& rectangle, sf::Vector2f point);

	std::list<Building*> buildings;
	Building* selectedBuilding;
	Building* hoveredBuilding;

	bool isHolding;
	bool isHovering;

};

