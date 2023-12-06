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
		//std::cout << "player pos " << _player->circleShape.getPosition().x << " " << _player->circleShape.getPosition().y << std::endl;

		sf::Vector2i _playerPos = sf::Vector2i(_player->circleShape.getPosition().x, _player->circleShape.getPosition().y);
		window.setPosition(_playerPos);

		sf::View playerView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
		playerView.setCenter(_player->circleShape.getPosition());
		window.setView(playerView);
	}
	
}