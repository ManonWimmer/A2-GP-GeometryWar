#ifndef MANAGERENTITY_H
#define MANAGERENTITY_H

#include <unordered_map>
#include <set>

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
    ManagerEntity(CollisionDetection* collisionDetection);
    void AddEntity(Entity* entity);
    std::unordered_map<Entity*, bool>::iterator GetPair(Entity* entity);
    void RemoveEntity(Entity* entity);
    bool IsEntityActive(Entity* entity);
    void UpdateAllEntities(sf::RenderWindow& window, float deltaTime, ManagerEntity& managerEntity);
    void ClearEntityGarbage();
    void DebugEntities(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, Player& player);
    std::unordered_map<Entity*, bool>& GetEntityDictionary();
    std::set<Entity*>& GetEntityGarbage();

private:
    CollisionDetection* collisionDetection;
    std::unordered_map<Entity*, bool> entityDictionary;
    std::set<Entity*> entityGarbage;
};

#endif