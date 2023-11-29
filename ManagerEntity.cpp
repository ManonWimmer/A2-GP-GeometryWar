#include "Entity.h"
#include "ManagerEntity.h"

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
        if (pair.second) {
            pair.first->Update(window, deltaTime);
        }
    }
}