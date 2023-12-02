#include "Entity.h"
#include "ManagerEntity.h"
#include "AI_Agent.h"
#include "CollisionDetection.h" 

ManagerEntity::ManagerEntity() {}

void ManagerEntity::AddEntity(Entity* entity) {
    entityDictionary[entity] = true;
}

void ManagerEntity::RemoveEntity(Entity* entity) {
    entityDictionary.erase(entity);
}

bool ManagerEntity::IsEntityActive(Entity* entity) {
    auto it = entityDictionary.find(entity);
    return it != entityDictionary.end() && it->second;
}

void ManagerEntity::UpdateAllEntities(sf::RenderWindow& window, float deltaTime) {
    for (auto& pair : entityDictionary) {
        pair.first->Update(window, deltaTime);
        pair.first->UpdateBaseEntity(window, deltaTime);
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
