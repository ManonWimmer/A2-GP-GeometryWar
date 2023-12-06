#include "Menu.h"
#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"

Menu::Menu(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, sf::RenderWindow& window, GameManager& gameManager) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _window(window), _gameManager(gameManager)
{
	this->_font = new sf::Font;
	(*_font).loadFromFile("../font/Zeniq.ttf");
	std::cout << "ici" << std::endl;

	this->_titleText = new sf::Text;
	(*_titleText).setFont((*_font));
	(*_titleText).setString("BOND");
	(*_titleText).setCharacterSize(175);
	(*_titleText).setFillColor(sf::Color::White);
	(*_titleText).setStyle(sf::Text::Bold);
	sf::FloatRect textBounds = (*_titleText).getLocalBounds();
	float x = (_window.getSize().x - textBounds.width) / 2;
	float y = (_window.getSize().y - textBounds.height) / 2 - 400;
	(*_titleText).setPosition(x, y);

	this->_game1Text = new sf::Text;
	(*_game1Text).setFont((*_font));
	(*_game1Text).setString("LEVEL I");
	(*_game1Text).setCharacterSize(80);
	(*_game1Text).setFillColor(sf::Color::White);
	textBounds = (*_game1Text).getLocalBounds();
	x = (_window.getSize().x - textBounds.width) / 2;
	y = (_window.getSize().y - textBounds.height) / 2 - 150;
	(*_game1Text).setPosition(x, y);

	this->_game1Rectangle = new sf::RectangleShape;
	(*_game1Rectangle).setSize(sf::Vector2f(400, 115));
	(*_game1Rectangle).setFillColor(sf::Color::Transparent);
	(*_game1Rectangle).setOutlineThickness(2);
	(*_game1Rectangle).setOutlineColor(sf::Color::White);
	sf::FloatRect rectangleBounds = (*_game1Rectangle).getLocalBounds();
	x = (_window.getSize().x - rectangleBounds.width) / 2 + 5;
	y = (_window.getSize().y - rectangleBounds.height) / 2 - 155 + textBounds.height / 2;
	(*_game1Rectangle).setPosition(x, y);

	this->_game2Text = new sf::Text;
	(*_game2Text).setFont((*_font));
	(*_game2Text).setString("LEVEL II");
	(*_game2Text).setCharacterSize(80);
	(*_game2Text).setFillColor(sf::Color::White);
	textBounds = (*_game2Text).getLocalBounds();
	x = (_window.getSize().x - textBounds.width) / 2;
	y = (_window.getSize().y - textBounds.height) / 2;
	(*_game2Text).setPosition(x, y);

	this->_game2Rectangle = new sf::RectangleShape;
	(*_game2Rectangle).setSize(sf::Vector2f(400, 115));
	(*_game2Rectangle).setFillColor(sf::Color::Transparent);
	(*_game2Rectangle).setOutlineThickness(2);
	(*_game2Rectangle).setOutlineColor(sf::Color::White);
	rectangleBounds = (*_game2Rectangle).getLocalBounds();
	x = (_window.getSize().x - rectangleBounds.width) / 2 + 5;
	y = (_window.getSize().y - rectangleBounds.height) / 2 - 5 + textBounds.height / 2;
	(*_game2Rectangle).setPosition(x, y);

	this->_game3Text = new sf::Text;
	(*_game3Text).setFont((*_font));
	(*_game3Text).setString("LEVEL III");
	(*_game3Text).setCharacterSize(80);
	(*_game3Text).setFillColor(sf::Color::White);
	textBounds = (*_game3Text).getLocalBounds();
	x = (_window.getSize().x - textBounds.width) / 2;
	y = (_window.getSize().y - textBounds.height) / 2 + 150;
	(*_game3Text).setPosition(x, y);

	this->_game3Rectangle= new sf::RectangleShape;
	(*_game3Rectangle).setSize(sf::Vector2f(400, 115));
	(*_game3Rectangle).setFillColor(sf::Color::Transparent);
	(*_game3Rectangle).setOutlineThickness(2);
	(*_game3Rectangle).setOutlineColor(sf::Color::White);
	rectangleBounds = (*_game3Rectangle).getLocalBounds();
	x = (_window.getSize().x - rectangleBounds.width) / 2 + 5;
	y = (_window.getSize().y - rectangleBounds.height) / 2 + 145 + textBounds.height / 2;
	(*_game3Rectangle).setPosition(x, y);


	this->_quitText = new sf::Text;
	(*_quitText).setFont((*_font));
	(*_quitText).setString("QUIT");
	(*_quitText).setCharacterSize(80);
	(*_quitText).setFillColor(sf::Color::White);
	textBounds = (*_quitText).getLocalBounds();
	x = (_window.getSize().x - textBounds.width) / 2;
	y = (_window.getSize().y - textBounds.height) / 2 + 350;
	(*_quitText).setPosition(x, y);


	this->_quitRectangle = new sf::RectangleShape;
	(*_quitRectangle).setSize(sf::Vector2f(230, 115));
	(*_quitRectangle).setFillColor(sf::Color::Transparent);
	(*_quitRectangle).setOutlineThickness(2);
	(*_quitRectangle).setOutlineColor(sf::Color::White);
	rectangleBounds = (*_quitRectangle).getLocalBounds();
	x = (_window.getSize().x - rectangleBounds.width) / 2 + 5;
	y = (_window.getSize().y - rectangleBounds.height) / 2 + 345 + textBounds.height / 2;
	(*_quitRectangle).setPosition(x, y);
}

void Menu::Update(sf::RenderWindow& window, float deltaTime)
{
	if (_gameManager.GetMenuState()) 
	{
		window.draw(*_titleText);
		window.draw(*_game1Text);
		window.draw(*_game1Rectangle);
		window.draw(*_game2Text);
		window.draw(*_game2Rectangle);
		window.draw(*_game3Text);
		window.draw(*_game3Rectangle);
		window.draw(*_quitText);
		window.draw(*_quitRectangle);

		CheckMouseInButtons();
	}
}

bool Menu::MouseInRectangle(sf::Vector2i mousePosition, sf::RectangleShape rectangle)
{
	float rectangleWidth = rectangle.getSize().x;
	float rectangleHeight = rectangle.getSize().y;

	float rectangleXTopLeft = rectangle.getPosition().x;
	float rectangleYTopLeft = rectangle.getPosition().y;

	if ((mousePosition.x >= rectangleXTopLeft && mousePosition.x <= rectangleXTopLeft + rectangleWidth) && (mousePosition.y >= rectangleYTopLeft && mousePosition.y <= rectangleYTopLeft + rectangleHeight))
	{
		return true;
	}
	return false;
}

void Menu::CheckMouseInButtons() 
{
	sf::Vector2i mousePosition = sf::Mouse::getPosition(_window);

	if (MouseInRectangle(mousePosition, (*_game1Rectangle))) {
		//std::cout << "hover rectangle 1" << std::endl;
		_game1Rectangle->setOutlineColor(sf::Color(49,203,0,255));
		_game1Text->setFillColor(sf::Color(49, 203, 0, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "click rectangle 1" << std::endl;
			_window.create(sf::VideoMode(720, 480), "James Bond");
			_gameManager.StartLevel(1);
		}
	}
	else {
		_game1Rectangle->setOutlineColor(sf::Color::White);
		_game1Text->setFillColor(sf::Color::White);
	}

	if (MouseInRectangle(mousePosition, (*_game2Rectangle))) {
		//std::cout << "hover rectangle 2" << std::endl;
		_game2Rectangle->setOutlineColor(sf::Color(17, 152, 34, 255));
		_game2Text->setFillColor(sf::Color(17, 152, 34, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "click rectangle 2" << std::endl;
			_window.create(sf::VideoMode(720, 480), "James Bond");
			_gameManager.StartLevel(2);
		}
	}
	else {
		_game2Rectangle->setOutlineColor(sf::Color::White);
		_game2Text->setFillColor(sf::Color::White);
	}

	if (MouseInRectangle(mousePosition, (*_game3Rectangle))) {
		//std::cout << "hover rectangle 3" << std::endl;
		_game3Rectangle->setOutlineColor(sf::Color(42, 114, 33, 255));
		_game3Text->setFillColor(sf::Color(42, 114, 33, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "click rectangle 3" << std::endl;
			_window.create(sf::VideoMode(720, 480), "James Bond");
			_gameManager.StartLevel(3);
		}
	}
	else {
		_game3Rectangle->setOutlineColor(sf::Color::White);
		_game3Text->setFillColor(sf::Color::White);
	}

	if (MouseInRectangle(mousePosition, (*_quitRectangle))) {
		//std::cout << "hover quit" << std::endl;
		_quitRectangle->setOutlineColor(sf::Color(30, 68, 30, 255));
		_quitText->setFillColor(sf::Color(30, 68, 30, 255));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			std::cout << "click quit" << std::endl;
			_window.close();
		}
	}
	else {
		_quitRectangle->setOutlineColor(sf::Color::White);
		_quitText->setFillColor(sf::Color::White);
	}
}
// envoyer vers le start level quand clic sur un des rectangles et mettre inmenu à false,

