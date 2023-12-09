#include "GameManager.h"
#include "AI_Agent.h"
#include "CollisionDetection.h"
#include "ManagerEntity.h"
#include "SaveAndLoadMap.h"
#include "Menu.h"
#include "Camera.h"
#include "Entity.h"

GameManager::GameManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _managerEntity(managerEntity), _collisionDetection(collisionDetection)
{
	_inMenu = true;
	_gameEnded = true;
}

void GameManager::Update(sf::RenderWindow& window, float deltaTime) 
{
	//std::cout << _gameEnded << std::endl;
	if (!_inMenu)
	{
		CheckGameEnd();


		if ((_gameLose || _gameWon) && window.getSize() != sf::Vector2u(1920, 1080) && _gameEnded)
		{
			std::cout << "creation nouv " << std::endl;
			window.create(sf::VideoMode(1920, 1080), "James Bond", sf::Style::Fullscreen);
		}
	}
}

bool GameManager::GetMenuState()
{
	return _inMenu;
}
int GameManager::GetCurrentLevel()
{
	return _currentLevel;
}

void GameManager::SwitchMode()
{
	if (_isShootEmUp)
	{
		_isShootEmUp = false;
		SwitchToInfiltration();
	}
	else
	{
		_isShootEmUp = true;
		SwitchToShootEmUp();
	}
}
void GameManager::SwitchToShootEmUp()
{

}
void GameManager::SwitchToInfiltration()
{
	
}

void GameManager::CheckShootEmUp()
{
	std::unordered_map<Entity*, bool>::iterator it;

	for (it = managerEntity.GetEntityDictionary().begin(); it != managerEntity.GetEntityDictionary().end(); it++)
	{
		if (it->first->GetEntityType() == EntityType::AI_Entity) {

			if (it->first->isChasing) {

				ActivateShootEmUp();
			}
		}
	}
}

void GameManager::ActivateShootEmUp()
{
	std::unordered_map<Entity*, bool>::iterator it;

	for (it = managerEntity.GetEntityDictionary().begin(); it != managerEntity.GetEntityDictionary().end(); it++)
	{
		if (it->first->GetEntityType() == EntityType::AI_Entity) {
			it->first->isChasing = true;
		}
	}

	_mapManager->ClearCurrentMap(managerEntity);
}

void GameManager::InitializedGameManager(sf::RenderWindow& window, GameManager& gameManager)
{
	_mapManager = new SaveAndLoadMap();

	_menu = new Menu(managerEntity, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType, window, gameManager);
	managerEntity.AddEntity(_menu);

	_camera = new Camera(managerEntity, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType, gameManager);
	managerEntity.AddEntity(_camera);
}

void GameManager::SpawnEnemy(float radius, sf::Vector2f spawnPosition, float speed)
{
	AI_Agent* ptrEnemy = new AI_Agent(_managerEntity, _collisionDetection, EntityType::AI_Entity, Faction::EnemiesFaction, CollisionType::Circle, radius, spawnPosition, speed, (*_player));
	_managerEntity.AddEntity(ptrEnemy);
}

void GameManager::CheckEnemiesLife()
{
	/*if (_enemies.size() > 0)
	{
		std::list<AI_Agent*>::iterator it = _enemies.begin();
		_allEnemiesDead = true;

		while (it != _enemies.end())
		{
			if (!((*it)->isDead))
			{
				_allEnemiesDead = false;
			}
			it++;
		}
	}*/

	std::unordered_map<Entity*, bool>::iterator it = managerEntity.GetEntityDictionary().begin();

	_allEnemiesDead = true;

	while (it != managerEntity.GetEntityDictionary().end())
	{
		if (it->first->GetEntityType() == EntityType::AI_Entity)
		{
			if (it->first->GetLife() > 0)
			{
				_allEnemiesDead = false;
			}
		}
		it++;
	}
}

void GameManager::CheckPlayerLife() 
{
	if (_player != nullptr) {
		_playerDead = (_player->GetLife() <= 0) ? true : false;
	}

}

void GameManager::SetWinAndLoseFalse() {
	_gameLose = false;
	_gameWon = false;
}
bool GameManager::GetLose() {
	return _gameLose;
}
bool GameManager::GetWin() {
	return _gameWon;
}

void GameManager::CheckGameEnd()
{

	if (!_gameEnded) {
		CheckEnemiesLife();
		CheckPlayerLife();

		if (_playerDead)
		{
			std::cout << "Player dead, lose" << std::endl;
			_gameLose = true;
			_inMenu = true;
			_gameEnded = true;
		}
		else if (_allEnemiesDead)
		{
			std::cout << "All enemies dead, won" << std::endl;
			_gameWon = true;
			_inMenu = true;
			_gameEnded = true;
		}

		if (_gameEnded) {
			std::unordered_map<Entity*, bool>::iterator it2 = managerEntity.GetEntityDictionary().begin();

			while (it2 != managerEntity.GetEntityDictionary().end())
			{
				if ((it2->first->GetEntityType() == EntityType::AI_Entity || it2->first->GetEntityType() == EntityType::Player_Entity || it2->first->GetEntityType() == EntityType::Building_Entity || it2->first->GetEntityType() == EntityType::Projectile_Entity || it2->first->GetEntityType() == EntityType::Weapon_Entity) && it2->second == true)
				{
					it2->second = false;
				}
				it2++;
			}
		}
	}
}



void GameManager::StartLevel(int levelNumber)
{
	_gameEnded = false;

	std::cout << "start level " << levelNumber << std::endl;
	_inMenu = false;

	if (_player == nullptr) {
		std::cout << "add player" << std::endl;
		_player = new Player(managerEntity, collisionDetection, EntityType::Player_Entity, Faction::PlayerFaction, CollisionType::Circle, sf::Vector2f(100, 0));
		managerEntity.AddEntity(_player);
	}

	switch (levelNumber) {
		case 1:
			std::cout << "case 1" << std::endl;
			_mapManager->LoadMap("Level1.json", managerEntity, collisionDetection);
			_enemiesStartPositions = { sf::Vector2f(1200, 80), sf::Vector2f(1200, 640), sf::Vector2f(120, 640), sf::Vector2f(1000, 80), sf::Vector2f(600, 80),  sf::Vector2f(600, 640) };
		break;
	}

	std::cout << _enemiesStartPositions.size() << std::endl;


	if (_enemiesStartPositions.size() > 0)
	{
		std::cout << "Test enemies start positions" << std::endl;

		std::list<sf::Vector2f>::iterator it = _enemiesStartPositions.begin();

		while (it != _enemiesStartPositions.end())
		{
			std::cout << "while" << std::endl;
			SpawnEnemy(15.0f, *it, 75.0f);
			it++;
		}
	}
}

Player* GameManager::GetPlayer()
{
	return _player;
}

SaveAndLoadMap& GameManager::GetMapManager()
{
	return *_mapManager;
}
