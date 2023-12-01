#pragma once
#include <SFML/Graphics.hpp>
#include "ManagerEntity.h"
#include "AI_Agent.h"
#include <list>

class ManagerEntity;

class GameManager
{
public :
	GameManager(ManagerEntity&, CollisionDetection&, Player&);
	void SpawnEnemy(float, sf::Vector2f, float);
	void CheckEnemiesLife();
	void CheckPlayerLife();
	void CheckGameEnd(); // A changer plus tard par CheckLevelEnd ?

private : 
	ManagerEntity _managerEntity;
	CollisionDetection _collisionDetection;
	Player _player;
	std::list<AI_Agent*> _enemies;
	bool _allEnemiesDead;
	bool _playerDead;
	bool _gameWon;
	bool _gameLose;
};

