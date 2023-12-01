#pragma once
#include <SFML/Graphics.hpp>
#include "ManagerEntity.h"
#include "AI_Agent.h"
#include <list>

class ManagerEntity;

class GameManager
{
public:
    GameManager(ManagerEntity&, CollisionDetection&, Player&);
    void SpawnEnemy(float, sf::Vector2f, float);
    void CheckEnemiesLife();
    void CheckPlayerLife();
    void CheckGameEnd(); // A changer plus tard par CheckLevelEnd ?
    void StartLevel(int);

    std::list<AI_Agent*> _enemies;

private:
    ManagerEntity& _managerEntity;
    CollisionDetection& _collisionDetection;
    Player& _player;

    bool _allEnemiesDead;
    bool _playerDead;
    bool _gameWon;
    bool _gameLose;
    std::list<sf::Vector2f> _enemiesStartPositions;
};
