#include "GameManager.h"
#include "AI_Agent.h"
#include "CollisionDetection.h"
#include "ManagerEntity.h"


GameManager::GameManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, Player& player) 
{
	this->_managerEntity = managerEntity;
	this->_collisionDetection = collisionDetection;
	this->_player = player;
}

void GameManager::SpawnEnemy(float radius, sf::Vector2f spawnPosition, float speed)
{
	AI_Agent* ptrEnemy = new AI_Agent(_managerEntity, _collisionDetection, radius, spawnPosition, speed, _player);
	_managerEntity.AddEntity(ptrEnemy);
	_enemies.push_back(ptrEnemy); 
}

void GameManager::CheckEnemiesLife()
{
	if (_enemies.size() > 0)
	{
		std::list<AI_Agent*>::iterator it = _enemies.end();
		_allEnemiesDead = true;

		while (it != _enemies.end())
		{
			if (!((*it)->isDead))
			{
				_allEnemiesDead = false;
			}
			it++;
		}
	}
}

void GameManager::CheckPlayerLife() 
{
	_playerDead = (_player.pv <= 0) ? true : false;
}

void GameManager::CheckGameEnd()
{
	CheckEnemiesLife();
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



