#pragma once
#include <SFML/Graphics.hpp>
#include "ManagerEntity.h"
#include "EntityEnums.h"
#include "Entity.h"

#include "AI_Agent.h"
#include <list>

class ManagerEntity;
class SaveAndLoadMap;
class Menu;
class Camera;

class GameManager : public Entity
{
public:
    GameManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);
    virtual void Update(sf::RenderWindow& window, float deltaTime) override;



    void InitializedGameManager(sf::RenderWindow& window, GameManager& gameManager);

    void SpawnEnemy(float, sf::Vector2f, float);
    void CheckEnemiesLife();
    void CheckPlayerLife();
    void CheckGameEnd(); // A changer plus tard par CheckLevelEnd ?
    void StartLevel(int);
    void SwitchMode();
    void SwitchToShootEmUp();
    void SwitchToInfiltration();

    void CheckShootEmUp();
    void ActivateShootEmUp();


    void SetWinAndLoseFalse();
    bool GetLose();
    bool GetWin();
    bool GetMenuState();
    int GetCurrentLevel();
    //std::list<AI_Agent*> _enemies;

    Player* GetPlayer();
    SaveAndLoadMap& GetMapManager();

private:
    ManagerEntity& _managerEntity;
    CollisionDetection& _collisionDetection;
    SaveAndLoadMap* _mapManager;

    Player* _player;
    Camera* _camera;
    Menu* _menu;

    bool _allEnemiesDead;
    bool _playerDead;
    bool _gameWon;
    bool _gameLose;
    bool _gameEnded;
    std::list<sf::Vector2f> _enemiesStartPositions;

    bool _inMenu;
    bool _isShootEmUp;

    int _currentLevel;
};
