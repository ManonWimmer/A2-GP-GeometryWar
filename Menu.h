#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "EntityEnums.h"
#include "Entity.h"
#include "GameManager.h"

class ManagerEntity;

class Menu : public Entity
{
public:
	//Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, Player* player, sf::View& mapView, sf::View& playerView);
	Menu(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::RenderWindow& window, GameManager& gameManager);
	
	void Update(sf::RenderWindow& window, float deltaTime);
	void CheckMouseInButtonsMenu();
	bool MouseInRectangle(sf::Vector2i mousePosition, sf::RectangleShape rectangle);
	void CheckMouseInBackToMenu();

private:
	sf::RenderWindow& _window;
	GameManager& _gameManager;
	sf::Font* _font;
	sf::Text* _titleText;
	sf::Text* _game1Text;
	sf::Text* _game2Text;
	sf::Text* _game3Text;
	sf::Text* _quitText;
	sf::RectangleShape* _game1Rectangle;
	sf::RectangleShape* _game2Rectangle;
	sf::RectangleShape* _game3Rectangle;
	sf::RectangleShape* _quitRectangle;

	sf::Text* _wonTitleText;
	sf::Text* _loseTitleText;
	sf::Text* _backToMenuText;
	sf::RectangleShape* _backToMenuRectangle;
};


