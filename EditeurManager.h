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
	void ObjectsInteraction(sf::RenderWindow& window, float deltaTime);
	void PressedAKey();

	float GetPositiveFloat(float value);
	float GetDistance(sf::Vector2f vector1, sf::Vector2f vector2);
	
	bool IsPointInsideCircle(sf::CircleShape& circle, sf::Vector2f point);
	bool IsPointInsideRectangle(sf::RectangleShape& rectangle, sf::Vector2f point);

	float _draggingMinTime = 0.175f;
	float _draggingCurrentTime;

	float _pressKeyCoolDown = 0.25f;
	float _currentPressKeyTime;

	float _cursorActualisation;
	sf::Cursor _cursor;
	sf::Vector2f _framePassedMousePosition;

	SaveAndLoadMap _mapManager;
	std::list<Building*> _buildings;

	Building* _draggedBuilding;
	Building* _selectedBuilding;
	Building* _hoveredBuilding;

	sf::Color _baseOutlineColor = sf::Color::Transparent;
	sf::Color _hoveredOutlineColor = sf::Color::Cyan;
	sf::Color _selectedOutlineColor = sf::Color::Green;

	bool _isHolding;
	bool _isHovering;

};

