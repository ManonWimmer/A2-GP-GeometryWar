#include "Entity.h"
#include "ManagerEntity.h"
#include "AI_Agent.h"
#include "CollisionDetection.h" 

ManagerEntity::ManagerEntity(CollisionDetection* collisionDetection) {
    collisionDetection = collisionDetection;
}

void ManagerEntity::AddEntity(Entity* entity) {
    entityDictionary[entity] = true;
}

std::unordered_map<Entity*, bool>::iterator ManagerEntity::GetPair(Entity* entity)
{
    auto it = entityDictionary.find(entity);

    if (it != entityDictionary.end()) {
        return it;  // Dereference the iterator to get the value (std::pair<Entity*, bool>)
    }
    else {
        //Error
        return it;
    }
}

void ManagerEntity::RemoveEntity(std::unordered_map<Entity*, bool>::iterator& iterator) {
    //iterator = entityDictionary.erase(iterator);
    entityGarbage[iterator->first] = true;
}

bool ManagerEntity::IsEntityActive(Entity* entity) {
    auto it = entityDictionary.find(entity);
    return it != entityDictionary.end() && it->second;
}

void ManagerEntity::UpdateAllEntities(sf::RenderWindow& window, float deltaTime, ManagerEntity& managerEntity) {
    for (auto& pair : entityDictionary) {
        pair.first->Update(window, deltaTime);
        pair.first->UpdateBaseEntity(window, deltaTime);
    }

    collisionDetection->CheckAllEntitiesCollisions(managerEntity);
    
    ClearEntityGarbage();
}

void ManagerEntity::ClearEntityGarbage()
{
    for (auto& pair : entityGarbage) {

        entityDictionary.erase(pair.first);

        if (pair.first != nullptr) {
            delete pair.first;
        }
        entityGarbage.erase(pair.first);
    }
}

void ManagerEntity::DebugEntities(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, Player& player)
{
    AddEntity(new AI_Agent(managerEntity, collisionDetection, EntityType::AI_Entity, Faction::EnemiesFaction, CollisionType::Circle, 17.0f, sf::Vector2f(600, 600), 75.0f, player));

}

std::unordered_map<Entity*, bool>& ManagerEntity::GetEntityDictionary()
{
    return entityDictionary;
}

std::unordered_map<Entity*, bool>& ManagerEntity::GetEntityGarbage()
{
    return entityGarbage;
}
