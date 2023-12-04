#pragma once
#include <list>
#include <SFML/Graphics.hpp>
#include <cfloat>

#include "EntityEnums.h"
#include "Entity.h"
#include "SaveAndLoadMap.h"

class Building;

class EditeurManager : public Entity
{
public:
	EditeurManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
	void DeletingAnObject();
	void SpawningAnObject(sf::RenderWindow& window);
	void DraggingAnObject(sf::RenderWindow& window, float deltaTime);
	void StartDraggingAnObject(sf::RenderWindow& window, float deltaTime);

	void SelectingAnObject(sf::RenderWindow& window);
	void HoveringAnObject(sf::RenderWindow& window);

	void ResizeAnObject(sf::RenderWindow& window, float deltaTime);

	void EndOfUpdateStuff(sf::RenderWindow& window, float deltaTime);
	void BaseEditeurStuff(sf::RenderWindow& window, float deltaTime);
	void PressedAKey();

	float GetPositiveFloat(float value);
	float GetDistance(sf::Vector2f vector1, sf::Vector2f vector2);
	
	bool IsPointInsideCircle(sf::CircleShape& circle, sf::Vector2f point);
	bool IsPointInsideRectangle(sf::RectangleShape& rectangle, sf::Vector2f point);

	float draggingMinTime = 0.175f;
	float draggingCurrentTime;

	float pressKeyCoolDown = 0.25f;
	float currentPressKeyTime;

	float cursorActualisation;
	sf::Cursor cursor;
	sf::Vector2f framePassedMousePosition;

	//std::list<Building*> buildings;
	SaveAndLoadMap mapManager;
	std::list<Building*> buildings;

	Building* draggedBuilding;
	Building* selectedBuilding;
	Building* hoveredBuilding;

	sf::Color baseOutlineColor = sf::Color::Transparent;
	sf::Color hoveredOutlineColor = sf::Color::Cyan;
	sf::Color selectedOutlineColor = sf::Color::Green;

	bool isHolding;
	bool isHovering;

};

