#ifndef MANAGERENTITY_H
#define MANAGERENTITY_H

#include <unordered_map>

class Entity;

class ManagerEntity {
public:
    ManagerEntity();
    void AddEntity(Entity* entity);
    void RemoveEntity(Entity* entity);
    bool IsEntityActive(Entity* entity);
    void UpdateAllEntities(sf::RenderWindow& window, float deltaTime);

private:
    std::unordered_map<Entity*, bool> entityDictionary;
};

#endif