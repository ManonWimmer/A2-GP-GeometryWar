#include "EditeurManager.h"
#include "Building.h"
#include <iostream>

EditeurManager::EditeurManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), hoveredBuilding(nullptr)
{

}

void EditeurManager::Update(sf::RenderWindow& window, float deltaTime)
{

	// Clique Gauche pour sélectionner.
	// Maintenir clique gauche pour drag un objet.
	// R pour spawn un rectangle.
	// C pour spawn un cercle.
	// I pour spawn une IA avec des points de patrouille. (le point clair est le point A, le point foncé est le point B)
	// K pour directement spawn une IA fixe.
	// S en ayant un objet sélectionner pour resize.
	// S + Shift en ayant un objet sélectionner pour resize uniformément.
	// F en ayant un objet de sélectionner pour supprimer.
	// P pour sauvegarder la Map
	// M pour charger la Map


	// IMPORTANT
	// Le chargement de la map fonctionne pas !! Regarder du côté de la récupération des données depuis le txt.

	BaseEditeurStuff(window, deltaTime);
	std::string level1 = "Level1.json";
	std::string level2 = "Level2.json";
	std::string level3 = "Level3.json";

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
		mapManager.SaveToJSON(buildings, level2);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M)) {
		buildings = mapManager.LoadFromJSON(level2, managerEntity, collisionDetection);
	}



	if (draggedBuilding == nullptr) {
		HoveringAnObject(window);
		SpawningAnObject(window);

		if (hoveredBuilding != nullptr) {
			SelectingAnObject(window);
		}

		if (selectedBuilding != nullptr) {
			ResizeAnObject(window, deltaTime);
			StartDraggingAnObject(window, deltaTime);
			DeletingAnObject();
		}

	}
	else {

		sf::Vector2i pixelPos = sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()));

		std::cout << "Draged Object Pixel Pos: " << pixelPos.x << " ; " << pixelPos.y << std::endl;

		std::cout << "Draged Object Pos: " << draggedBuilding->GetEntityCircleShape().getPosition().x << " ; " << draggedBuilding->GetEntityCircleShape().getPosition().y << std::endl;
		DraggingAnObject(window, deltaTime);
	}
	

	EndOfUpdateStuff(window, deltaTime);
}

void EditeurManager::DeletingAnObject()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F) && selectedBuilding != nullptr) {

		for (auto it = buildings.begin(); it != buildings.end();) {
			if (*it == selectedBuilding) {
				delete* it; 
				it = buildings.erase(it);
			}
			else {
				++it;
			}
		}

		selectedBuilding = nullptr;
	}
	
}

void EditeurManager::SpawningAnObject(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C) && currentPressKeyTime >= pressKeyCoolDown) {
		buildings.push_back(new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, sf::Vector2f(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()))), "CircularWall"));
		PressedAKey();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && currentPressKeyTime >= pressKeyCoolDown) {
		buildings.push_back(new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Rectangle, sf::Vector2f(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()))), "RectangularWall"));
		PressedAKey();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && currentPressKeyTime >= pressKeyCoolDown) {
		buildings.push_back(new Building(managerEntity, collisionDetection, EntityType::Building_Entity, Faction::None_Faction, CollisionType::Circle, sf::Vector2f(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView()))), "AI_Fixe"));
		PressedAKey();
	}

}

void EditeurManager::DraggingAnObject(sf::RenderWindow& window, float deltaTime)
{

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		if (cursor.loadFromSystem(sf::Cursor::NotAllowed)) {
			window.setMouseCursor(cursor);
		}

		sf::Vector2f mousePosition = sf::Vector2f(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView())));
		switch (draggedBuilding->GetEntityCollisionType()) {
			case CollisionType::Circle:
				draggedBuilding->GetEntityCircleShape().setPosition(mousePosition);
				break;
			case CollisionType::Rectangle:
				draggedBuilding->GetEntityRectangleShape().setPosition(mousePosition);
				break;
		}
	}
	else {
		selectedBuilding = draggedBuilding;
		draggedBuilding = nullptr;
		std::cout << "End Dragging working" << std::endl;
	}

}

void EditeurManager::StartDraggingAnObject(sf::RenderWindow& window, float deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		draggingCurrentTime += deltaTime;

		if (draggingCurrentTime >= draggingMinTime) {
			draggingCurrentTime = 0;

			draggedBuilding = selectedBuilding;
			selectedBuilding = nullptr;
		}
	}
	else {
		draggingCurrentTime = 0;
	}
}

void EditeurManager::SelectingAnObject(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{

		if (cursor.loadFromSystem(sf::Cursor::Hand)) {
			window.setMouseCursor(cursor);
		}

		if(selectedBuilding != nullptr) selectedBuilding->ResetColor();

		hoveredBuilding->ResetColor();

		selectedBuilding = hoveredBuilding;
		hoveredBuilding = nullptr;

		sf::CircleShape* circleShape;
		sf::RectangleShape* rectangleShape;

		switch (selectedBuilding->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				circleShape = &selectedBuilding->GetEntityCircleShape();
				circleShape->setOutlineColor(selectedOutlineColor);
				break;

			case CollisionType::Rectangle:
				rectangleShape = &selectedBuilding->GetEntityRectangleShape();
				rectangleShape->setOutlineColor(selectedOutlineColor);
				break;
		}
		
	}
}

void EditeurManager::HoveringAnObject(sf::RenderWindow& window)
{

	if (buildings.size() <= 0) return;

	if (hoveredBuilding != nullptr) {
		hoveredBuilding->ResetColor();
	}

	std::list<Building*> hoveredBuildings;
	std::list<Building*>::iterator it;
	float closerDistance = FLT_MAX;
	sf::Vector2f mousePosition(sf::Vector2i(window.mapPixelToCoords(sf::Mouse::getPosition(window), window.getView())));


	// Taking only hovered Buildings.
	for (it = buildings.begin(); it != buildings.end(); it++)
	{
		switch ((*it)->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				if (IsPointInsideCircle((*it)->GetEntityCircleShape(), mousePosition)) {
					hoveredBuildings.push_back((*it));
				}
				break;

			case CollisionType::Rectangle:
				if (IsPointInsideRectangle((*it)->GetEntityRectangleShape(), mousePosition)) {
					hoveredBuildings.push_back((*it));
				}
				break;
		}

	}

	if (hoveredBuildings.size() <= 0) return;

	for (it = buildings.begin(); it != buildings.end(); it++)
	{
		float currentDistance = FLT_MAX;
		sf::Vector2f circleShapePosition;
		sf::Vector2f rectangleShapePosition;

		switch ((*it)->GetEntityCollisionType())
		{
			case CollisionType::Circle:
					circleShapePosition = (*it)->GetEntityCircleShape().getPosition();
					currentDistance = GetDistance(circleShapePosition, mousePosition);
				break;

			case CollisionType::Rectangle:
					rectangleShapePosition = (*it)->GetEntityRectangleShape().getPosition();
					currentDistance = GetDistance(rectangleShapePosition, mousePosition);
				break;
		}

		currentDistance = GetPositiveFloat(currentDistance);

		if (currentDistance < closerDistance) 
		{
			closerDistance = currentDistance;
			hoveredBuilding = (*it);
		}

	}


	if (hoveredBuilding == selectedBuilding) {
		hoveredBuilding = nullptr;
		return;
	}

	if (hoveredBuilding != nullptr) {

		sf::CircleShape* circleShape;
		sf::RectangleShape* rectangleShape;

		switch (hoveredBuilding->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				circleShape = &hoveredBuilding->GetEntityCircleShape();
				circleShape->setOutlineColor(hoveredOutlineColor);
				//circleShape->setOutlineThickness(circleShape->getRadius() / 7.0f);
				break;

			case CollisionType::Rectangle:
				rectangleShape = &hoveredBuilding->GetEntityRectangleShape();
				rectangleShape->setOutlineColor(hoveredOutlineColor);
				//rectangleShape->setOutlineThickness((rectangleShape->getSize().x / 2 + rectangleShape->getSize().y / 2) / 7.0f);
				break;
		}
	}
	
}

void EditeurManager::ResizeAnObject(sf::RenderWindow& window, float deltaTime)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		sf::CircleShape* circleShape;
		sf::RectangleShape* rectangleShape;
		sf::Vector2f incrementScale;
		float resizeSpeed = 400.0f;
		bool isNearer;

		float distance = FLT_MAX;
		float scaleChange = FLT_MAX;
		float newRadius = FLT_MAX;

		switch (selectedBuilding->GetEntityCollisionType())
		{
			case CollisionType::Circle:
				circleShape = &selectedBuilding->GetEntityCircleShape();

				distance = GetDistance(framePassedMousePosition, sf::Vector2f(sf::Mouse::getPosition(window)));
				scaleChange = distance * deltaTime * resizeSpeed;
				newRadius = circleShape->getRadius() + (sf::Mouse::getPosition(window).x < framePassedMousePosition.x ? -scaleChange : scaleChange);

				circleShape->setRadius(std::max(newRadius, 0.0f));

				//Actualizing the origin position based on the new radius.
				circleShape->setOrigin(circleShape->getRadius(), circleShape->getRadius());
				break;

			case CollisionType::Rectangle:
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					rectangleShape = &selectedBuilding->GetEntityRectangleShape();
					scaleChange = GetDistance(framePassedMousePosition, sf::Vector2f(sf::Mouse::getPosition(window))) * deltaTime * resizeSpeed;

					// vérifie si le souris s'approche ou s'éloigne
					isNearer = GetDistance(sf::Vector2f(sf::Mouse::getPosition(window)), rectangleShape->getPosition()) < GetDistance(framePassedMousePosition, rectangleShape->getPosition());


					if (isNearer)
					{
						incrementScale = sf::Vector2f(-scaleChange, -scaleChange);
						rectangleShape->setSize(rectangleShape->getSize() + incrementScale);
					}
					else
					{
						incrementScale = sf::Vector2f(scaleChange, scaleChange);
						rectangleShape->setSize(rectangleShape->getSize() + incrementScale);
					}

				}
				else {
					rectangleShape = &selectedBuilding->GetEntityRectangleShape();
					incrementScale = (sf::Vector2f(sf::Mouse::getPosition(window)) - framePassedMousePosition) * deltaTime * resizeSpeed;
					rectangleShape->setSize(rectangleShape->getSize() + incrementScale);
				}

				//Actualizing the origin position based on the new radius.
				rectangleShape->setOrigin(rectangleShape->getSize().x / 2, rectangleShape->getSize().y / 2);

				break;
		}
	}

}

void EditeurManager::EndOfUpdateStuff(sf::RenderWindow& window, float deltaTime)
{
	framePassedMousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
}

void EditeurManager::BaseEditeurStuff(sf::RenderWindow& window, float deltaTime)
{
	currentPressKeyTime += deltaTime;
	cursorActualisation += deltaTime;

	if (cursorActualisation >= 0.3f) {
		cursorActualisation = 0;
		if (cursor.loadFromSystem(sf::Cursor::Arrow)) {
			window.setMouseCursor(cursor);
		}
	}
	

	std::list<Building*>::iterator it;

	for (it = buildings.begin(); it != buildings.end(); it++)
	{
		(*it)->Update(window, deltaTime);
	}
}

void EditeurManager::PressedAKey()
{
	currentPressKeyTime = 0;
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

	sf::FloatRect rectBounds = rectangle.getGlobalBounds();
	return rectBounds.contains(point);

}
