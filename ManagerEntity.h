#ifndef MANAGERENTITY_H
#define MANAGERENTITY_H

#include <unordered_map>

class Entity;
class CollisionDetection;
class Player;

//enum EntityType
//{
//    Player_Entity,
//    AI_Entity,
//    Weapon_Entity,
//    Projectile_Entity,
//    Objectif_Entity,
//    None_Entity,
//};

class ManagerEntity {
public:
    ManagerEntity();
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    bool IsEntityActive(Entity* entity);
    void UpdateAllEntities(sf::RenderWindow& window, float deltaTime);
    void DebugEntities(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, Player& player);
    std::unordered_map<Entity*, bool>& GetEntityDictionary();

private:
    std::unordered_map<Entity*, bool> entityDictionary;
};

#endif