#pragma once
#include "SoundEnums.h"
#include <SFML/Audio.hpp>

#include"EntityEnums.h"
#include "Entity.h"

class SoundManager;
class ManagerEntity;
class CollisionDetection;

class SoundEmitter : public Entity
{
public:
	SoundEmitter(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, SoundManager& soundManager, sf::SoundBuffer* soundBuffer);
	SoundEmitter(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, SoundManager& soundManager, sf::SoundBuffer* soundBuffer, bool loopMode);
	
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

private:
	SoundManager& _soundManager;
	sf::Sound* _sound;
};

