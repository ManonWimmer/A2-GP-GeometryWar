#include "Entity.h"
#include "ManagerEntity.h"

Entity::Entity(ManagerEntity& managerEntity) : managerEntity(managerEntity) {}

Entity::~Entity() {}