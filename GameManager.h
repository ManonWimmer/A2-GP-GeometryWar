#pragma once
#include <SFML/Graphics.hpp>
#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"

#include "AI_Agent.h"
#include <list>

class ManagerEntity;



class GameManager : public Entity
{
public:
    GameManager(ManagerEntity&, CollisionDetection&, EntityType entityType, Faction entityFaction, CollisionType collisionType);
    virtual void Update(sf::RenderWindow& window, float deltaTime) override;

    void SpawnEnemy(float, sf::Vector2f, float);
    void CheckEnemiesLife();
    void CheckPlayerLife();
    void CheckGameEnd(); // A changer plus tard par CheckLevelEnd ?
    void StartLevel(int);
    void SwitchMode();

    bool GetMenuState();
    //std::list<AI_Agent*> _enemies;

    Player* GetPlayer();

private:
    ManagerEntity& _managerEntity;
    CollisionDetection& _collisionDetection;
    Player* _player;

    bool _allEnemiesDead;
    bool _playerDead;
    bool _gameWon;
    bool _gameLose;
    std::list<sf::Vector2f> _enemiesStartPositions;

    bool _inMenu;
    bool _isShootEmUp;
};
