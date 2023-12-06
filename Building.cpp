#include "Building.h"
#include <iostream>

Building::Building(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::Vector2f spawnPoint, std::string buildingName)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), buildingName(buildingName)
{
	buildingCircleShape.setFillColor(sf::Color::White);
	buildingCircleShape.setRadius(30.0f);
	buildingCircleShape.setOrigin(buildingCircleShape.getRadius(), buildingCircleShape.getRadius());
	buildingCircleShape.setPosition(spawnPoint);
	buildingCircleShape.setOutlineThickness(5.0f);

	buildingRectangleShape.setFillColor(sf::Color::White);
	buildingRectangleShape.setSize(sf::Vector2f(30.0f, 30.0f));
	buildingRectangleShape.setOrigin(buildingRectangleShape.getSize().x / 2, buildingRectangleShape.getSize().y / 2);
	buildingRectangleShape.setPosition(spawnPoint);
	buildingRectangleShape.setOutlineThickness(5.0f);

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
			buildingCircleShape.setOutlineColor(sf::Color::Transparent);
			break;

		case CollisionType::Rectangle:
			buildingRectangleShape.setOutlineColor(sf::Color::Transparent);
			break;

		default:
			break;
	}
}

void Building::ReplaceOrigin()
{
	buildingCircleShape.setOrigin(buildingCircleShape.getRadius(), buildingCircleShape.getRadius());

	buildingRectangleShape.setOrigin(buildingRectangleShape.getSize().x / 2, buildingRectangleShape.getSize().y / 2);
}



json Building::SaveBuilding()
{
	if (buildingName == "CircularWall") {
		sf::Vector2f position = buildingCircleShape.getPosition();
		float radius = buildingCircleShape.getRadius();
		float rotation = buildingCircleShape.getRotation();

		return {
			{"position", {position.x, position.y}},
			{"radius", radius},
			{"rotation", rotation},
			{"name", buildingName}
		};
	}


	if (buildingName == "RectangularWall") {
		sf::Vector2f position = buildingRectangleShape.getPosition();
		sf::Vector2f size = buildingRectangleShape.getSize();
		float rotation = buildingRectangleShape.getRotation();

		return {
			{"position", {position.x, position.y}},
			{"size", {size.x, size.y}},
			{"rotation", rotation},
			{"name", buildingName}
		};
	}

	return { "null", 0 };
}



Building*  Building::LoadBuilding(json& jsonData, ManagerEntity& managerEntity, CollisionDetection& collisionDetection) {
	std::string newBuildingName = jsonData.value("name", "");

	if (newBuildingName == "CircularWall") {
		sf::Vector2f position = {
			jsonData.value("position", json::array({0.0, 0.0}))[0],
			jsonData.value("position", json::array({0.0, 0.0}))[1]
		};

		float radius = jsonData.value("radius", 0.0f);
		float rotation = jsonData.value("rotation", 0.0f);

		Building* newBuilding = new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, position, newBuildingName);
		sf::CircleShape& newCircleShape = newBuilding->GetEntityCircleShape();
		newCircleShape.setPosition(position);
		newCircleShape.setRadius(radius);
		newCircleShape.setRotation(rotation);

		return newBuilding;
	}
	else if (newBuildingName == "RectangularWall") {
		sf::Vector2f position = {
			jsonData.value("position", json::array({0.0, 0.0}))[0],
			jsonData.value("position", json::array({0.0, 0.0}))[1]
		};

		sf::Vector2f size = {
			jsonData.value("size", json::array({0.0, 0.0}))[0],
			jsonData.value("size", json::array({0.0, 0.0}))[1]
		};

		float rotation = jsonData.value("rotation", 0.0f);

		Building* newBuilding = new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, position, newBuildingName);
		sf::RectangleShape& newRectangleShape = newBuilding->GetEntityRectangleShape();
		newRectangleShape.setPosition(position);
		newRectangleShape.setSize(size);
		newRectangleShape.setRotation(rotation);

		return newBuilding;
	}

	return new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, sf::Vector2f(0, 0), "ErrorBuilding");
}


