#include "SoundManager.h"


#include "SoundEmitter.h"
#include <iostream>

SoundManager::SoundManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType)
	: Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType)
{
	InitializedSoundBank();

}

void SoundManager::Update(sf::RenderWindow& window, float deltaTime) {


	/*for (SoundEmitter* emitter : _playedSounds) {
		emitter->Update(window, deltaTime);
	}*/

}


void SoundManager::InitializedSoundBank()
{
	
	for (int i = 0; i < static_cast<int>(SoundEnums::Count); ++i) {
		_soundBank[static_cast<SoundEnums>(i)] = new sf::SoundBuffer();
	}

	InitializedSoundBuffer(SoundEnums::MusicMainMenu, fileName_MusicMainMenu);


	InitializedSoundBuffer(SoundEnums::ShotPistolSound, fileName_ShotPistolSound);
	InitializedSoundBuffer(SoundEnums::ImpactConcreteSound, fileName_ImpactConcreteSound);
	InitializedSoundBuffer(SoundEnums::ImpactBloodSound, fileName_ImpactBloodSound);
	InitializedSoundBuffer(SoundEnums::DeathSound, fileName_DeathSound);


	InitializedSoundBuffer(SoundEnums::UIButtonClickSound, fileName_UIButtonClickSound);
	InitializedSoundBuffer(SoundEnums::UIButtonHoverSound, fileName_UIButtonHoverSound);
}

void SoundManager::InitializedSoundBuffer(SoundEnums sound, std::string fileName)
{
	if (_soundBank[sound]->loadFromFile(_globalFilePath + fileName + _audioType)) return;
	else {
		std::cout << "Error Loading From File: " << fileName << std::endl;
	}
}



void SoundManager::RemoveSound(SoundEmitter& soundEmitter)
{
	//_playedSounds.remove(soundEmitter);
}

std::unordered_map<SoundEnums, sf::SoundBuffer*>& SoundManager::GetSoundBank()
{
	return _soundBank;
}


void SoundManager::PlaySound(SoundEnums sound)
{	
	_playedSounds.insert(new SoundEmitter(managerEntity, collisionDetection, EntityType::Audio_Entity, *this, _soundBank[sound]));
}
