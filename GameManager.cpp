#include "GameManager.h"
#include "AI_Agent.h"
#include "CollisionDetection.h"
#include "ManagerEntity.h"


GameManager::GameManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType) : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _managerEntity(managerEntity), _collisionDetection(collisionDetection)
{
	
}

void GameManager::Update(sf::RenderWindow& window, float deltaTime) 
{

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
}

void GameManager::CheckPlayerLife() 
{
	//_playerDead = (_player.pv <= 0) ? true : false;
}

void GameManager::CheckGameEnd()
{
	//CheckEnemiesLife();
	CheckPlayerLife();

	if (_playerDead) 
	{
		std::cout << "Player dead, lose" << std::endl;
		_gameLose = true;
	}
	else if (_allEnemiesDead) 
	{
		std::cout << "All enemies dead, won" << std::endl;
		_gameWon = true;
	}
}



void GameManager::StartLevel(int levelNumber)
{
	std::cout << "start level " << levelNumber << std::endl;


	if (_player == nullptr) {
		_player = new Player(managerEntity, collisionDetection, EntityType::Player_Entity, Faction::PlayerFaction, CollisionType::Circle);
		managerEntity.AddEntity(_player);
	}

	switch (levelNumber) {
		case 1:
			std::cout << "case 1" << std::endl;
			_enemiesStartPositions = { sf::Vector2f(1200, 80), sf::Vector2f(1200, 640), sf::Vector2f(80, 640), sf::Vector2f(70, 80) };
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
