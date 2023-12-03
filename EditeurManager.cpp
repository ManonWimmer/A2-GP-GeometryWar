#include "EditeurManager.h"
#include "Building.h"
#include <iostream>

EditeurManager::EditeurManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), hoveredBuilding(nullptr)
{

}

void EditeurManager::Update(sf::RenderWindow& window, float deltaTime)
{
	std::list<Building*>::iterator it;

	for (it = buildings.begin(); it != buildings.end(); it++)
	{
		(*it)->UpdateBuilding(window, deltaTime);
	}

	HoveringAnObject(window);
	SpawningAnObject(window);
}

void EditeurManager::SpawningAnObject(sf::RenderWindow& window)
{
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
		buildings.push_back(new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, sf::Vector2f(sf::Mouse::getPosition(window))));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		buildings.push_back(new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, sf::Vector2f(sf::Mouse::getPosition(window))));
	}
}

void EditeurManager::HoldingAnObject()
{
}

void EditeurManager::HoveringAnObject(sf::RenderWindow& window)
{
	if (buildings.size() <= 0) return;

	std::list<Building*>::iterator it;
	float closerDistance = FLT_MAX;
	sf::Vector2f mousePosition(sf::Mouse::getPosition(window));


	for (it = buildings.begin(); it != buildings.end(); it++)
	{
		float currentDistance = FLT_MAX;

		sf::Vector2f circleShapePosition;
		sf::Vector2f rectangleShapePosition;


		switch ((*it)->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				
				if (IsPointInsideCircle((*it)->GetEntityCircleShape(), mousePosition)) {

					std::cout << "Is inside circle " << std::endl;

					circleShapePosition = (*it)->GetEntityCircleShape().getPosition();
					currentDistance = GetDistance(circleShapePosition, mousePosition);
				}
				break;

			case CollisionType::Rectangle:

				if (IsPointInsideRectangle((*it)->GetEntityRectangleShape(), mousePosition)) {

					std::cout << "Is inside Rectangle " << std::endl;

					rectangleShapePosition = (*it)->GetEntityRectangleShape().getPosition();
					currentDistance = GetDistance(rectangleShapePosition, mousePosition);
				}
				break;

			default:
				currentDistance = 10000;
				break;
		}

		currentDistance = GetPositiveFloat(currentDistance);

		if (currentDistance < closerDistance) {

			std::cout << "New Closer Building" << std::endl;

			closerDistance = currentDistance;

			if (hoveredBuilding != nullptr) {
				hoveredBuilding->ResetColor();
			}

			hoveredBuilding = (*it);
		}

	}


	if (hoveredBuilding != nullptr) {

		sf::CircleShape* circleShape;
		sf::RectangleShape* rectangleShape;

		switch (hoveredBuilding->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				circleShape = &hoveredBuilding->GetEntityCircleShape();
				circleShape->setOutlineColor(sf::Color::Green);
				circleShape->setOutlineThickness(circleShape->getRadius() / 7.0f);
				break;

			case CollisionType::Rectangle:
				rectangleShape = &hoveredBuilding->GetEntityRectangleShape();
				rectangleShape->setOutlineColor(sf::Color::Green);
				rectangleShape->setOutlineThickness((rectangleShape->getSize().x / 2 + rectangleShape->getSize().y / 2) / 7.0f);
				break;
		}
	}
	
}

float EditeurManager::GetPositiveFloat(float value)
{
	return std::sqrtf(value * value);
}

float EditeurManager::GetDistance(sf::Vector2f vector1, sf::Vector2f vector2)
{
	return std::sqrt(std::pow(vector1.x - vector2.x, 2) + std::pow(vector1.y - vector2.y, 2));
}

bool EditeurManager::IsPointInsideCircle(sf::CircleShape& circle, sf::Vector2f point)
{
	//std::cout << circle.getPosition().x << " ; " << circle.getPosition().y << std::endl;

	float distance = std::sqrt((point.x - circle.getPosition().x) * (point.x - circle.getPosition().x) + (point.y - circle.getPosition().y) * (point.y - circle.getPosition().y));

	if (distance <= circle.getRadius()) {
		return true;
	}
	else {
		return false;
	}
}

bool EditeurManager::IsPointInsideRectangle(sf::RectangleShape& rectangle, sf::Vector2f point)
{
	/*sf::Vector2f rectanglePosition = rectangle.getPosition();
	sf::Vector2f rectangleSize = rectangle.getSize();
	
	bool result = point.x >= rectanglePosition.x && point.x <= rectanglePosition.x + rectangleSize.x && point.y >= rectanglePosition.y && point.y <= rectanglePosition.y + rectangleSize.y;
	
	return result;
	*/

	sf::FloatRect rectBounds = rectangle.getGlobalBounds();
	return rectBounds.contains(point);

}
