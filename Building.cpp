#include "Building.h"
#include <iostream>

Building::Building(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f spawnPoint)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{

	buildingCircleShape.setFillColor(sf::Color::White);
	buildingCircleShape.setRadius(30.0f);
	buildingCircleShape.setOrigin(buildingCircleShape.getRadius(), buildingCircleShape.getRadius());
	buildingCircleShape.setPosition(spawnPoint);

	buildingRectangleShape.setFillColor(sf::Color::White);
	buildingRectangleShape.setSize(sf::Vector2f(30.0f, 30.0f));
	buildingRectangleShape.setOrigin(buildingRectangleShape.getSize().x / 2, buildingRectangleShape.getSize().y / 2);
	buildingRectangleShape.setPosition(spawnPoint);

}


void Building::Update(sf::RenderWindow& window, float deltaTime) {


}

void Building::UpdateBuilding(sf::RenderWindow& window, float deltaTime)
{
	switch (collisionType) {
		case CollisionType::Circle:
			window.draw(buildingCircleShape);
			break;

		case CollisionType::Rectangle:
			window.draw(buildingRectangleShape);
			break;
	}
}

sf::CircleShape& Building::GetEntityCircleShape() {
	return buildingCircleShape;
}

sf::RectangleShape& Building::GetEntityRectangleShape() {
	return buildingRectangleShape;
}

void Building::ResetColor()
{
	switch (collisionType)
	{
		case CollisionType::Circle:
			buildingCircleShape.setOutlineColor(sf::Color::White);
			break;

		case CollisionType::Rectangle:
			buildingRectangleShape.setOutlineColor(sf::Color::White);
			break;

		default:
			break;
	}
}
