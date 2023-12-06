#include "Camera.h"
#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"
#include "Player.h"

Camera::Camera(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, Player* player, sf::View& mapView, sf::View& playerView) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _player(player), _mapView(mapView), _playerView(playerView) { }

void Camera::Update(sf::RenderWindow& window, float deltaTime)
{
	_shake = false;

	//if (_shake) window.setPosition(sf::Vector2i(100 + rand() % 25, 100 + rand() % 25));

	if (_player != nullptr) {
		//std::cout << "player pos " << _player->circleShape.getPosition().x << " " << _player->circleShape.getPosition().y << std::endl;
		sf::Vector2i _playerPos = sf::Vector2i(_player->circleShape.getPosition().x, _player->circleShape.getPosition().y);

		window.setPosition(_playerPos);
		_playerView.setCenter(_player->circleShape.getPosition());
		window.setView(_playerView);
	}
	
}