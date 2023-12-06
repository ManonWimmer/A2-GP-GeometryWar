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

void Building::SaveBuilding(std::ofstream& file)
{
	if (buildingName == "CircularWall") {
		file << buildingName << " "
			<< buildingCircleShape.getPosition().x << " "
			<< buildingCircleShape.getPosition().y << " "
			<< buildingCircleShape.getRadius() << " "
			<< buildingCircleShape.getRotation() << " "
			<< std::endl;
	}

	if (buildingName == "RectangularWall") {
		file << buildingName << " "
			<< buildingRectangleShape.getPosition().x << " "
			<< buildingRectangleShape.getPosition().y << " "
			<< buildingRectangleShape.getSize().x << " "
			<< buildingRectangleShape.getSize().y << " "
			<< buildingRectangleShape.getRotation() << " "
			<< std::endl;
	}

}

Building* Building::LoadBuilding(std::ifstream& file, ManagerEntity& managerEntity, CollisionDetection& collisionDetection) {
	std::string name;
	sf::Vector2f position;
	float rotation = FLT_MAX;

	//Extracting the name from the file.
	file >> name;

	if (name == "CircularWall") 
	{
		file >> position.x;

		std::cout << name << std::endl;
		std::cout << position.x << std::endl;

		/*float radius;
		file >> position.x;
		file >> position.y;
		file >> radius;
		file >> rotation;
		Building* building = new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, position, name);
		sf::CircleShape& circle = building->GetEntityCircleShape();
		circle.setRadius(radius);
		building->ReplaceOrigin();
		circle.setRotation(rotation);
		return building;*/
		return new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, position, name);
	}


	if (name == "RectangularWall")
	{
		file >> position.x;

		std::cout << name << std::endl;
		std::cout << position.x << std::endl;

		/*sf::Vector2f size;
		file >> position.x;
		file >> position.y;
		file >> size.x;
		file >> size.y;
		file >> rotation;
		Building* building = new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, position, name);
		sf::RectangleShape& rectangle = building->GetEntityRectangleShape();
		rectangle.setSize(size);
		building->ReplaceOrigin();
		rectangle.setRotation(rotation);
		return building;*/
		return new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, position, name);
	}


	return new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, position, name);
}
