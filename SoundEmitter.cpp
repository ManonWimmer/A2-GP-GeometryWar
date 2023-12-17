#include "SoundEmitter.h"
#include "SoundManager.h"

#include "ManagerEntity.h"
#include "CollisionDetection.h"

SoundEmitter::SoundEmitter(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, SoundManager& soundManager, sf::SoundBuffer* soundBuffer)
	: Entity(managerEntity, collisionDetection, entityType), _soundManager(soundManager)
{
	_sound = new sf::Sound();
	_sound->setVolume(15.0f);
	_sound->setBuffer(*soundBuffer);
	_sound->play();          
}

SoundEmitter::SoundEmitter(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, SoundManager& soundManager, sf::SoundBuffer* soundBuffer, bool loopMode)
	: Entity(managerEntity, collisionDetection, entityType), _soundManager(soundManager)
{
	_sound = new sf::Sound();
	_sound->setVolume(15.0f);
	_sound->setLoop(loopMode);
	_sound->setBuffer(*soundBuffer);
	_sound->play();
}

void SoundEmitter::Update(sf::RenderWindow& window, float deltaTime)
{
	if (_sound->getStatus() != sf::SoundSource::Playing && !_sound->getLoop()) {
		delete _sound;
		DestroyItSelf();
	}
}
