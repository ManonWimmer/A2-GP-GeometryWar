#include "Camera.h"
#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"
#include "Player.h"

Camera::Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, GameManager& gameManager) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _gameManager(gameManager), _shake(false) { }

void Camera::Update(sf::RenderWindow& window, float deltaTime)
{
	_shake = false;

	//if (_shake) window.setPosition(sf::Vector2i(100 + rand() % 25, 100 + rand() % 25));


	Player* _player = _gameManager.GetPlayer();
	if (_player != nullptr) {

		sf::Vector2i _playerPos = sf::Vector2i(_player->circleShape.getPosition().x, _player->circleShape.getPosition().y);

		if (window.getSize() == sf::Vector2u(720, 480))
		{
			window.setPosition(_playerPos);

			sf::View playerView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
			playerView.setCenter(_player->circleShape.getPosition());
			window.setView(playerView);
		}
		else if (window.getSize() == sf::Vector2u(1920, 1080))
		{
			window.setPosition(sf::Vector2i(0, 0));
			
			sf::View playerView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
			if (_gameManager.GetMenuState()) {
				playerView.setCenter(sf::Vector2f(1920 / 2, 1080 / 2));
			}
			else {
				playerView.setCenter(sf::Vector2f(592, 300));
			}
			window.setView(playerView);
		}

	}

}

void Camera::ChangeToBig(sf::RenderWindow& window)
{
	window.create(sf::VideoMode(1920, 1080), "James Bond", sf::Style::Fullscreen);
}
void Camera::ChangeToSmall(sf::RenderWindow& window)
{
	window.create(sf::VideoMode(720, 480), "James Bond");
}