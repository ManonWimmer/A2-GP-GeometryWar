#pragma once
#include <list>
#include <set>
#include <unordered_map>
#include <SFML/Audio.hpp>


#include "SoundEnums.h"
#include "Entity.h"

class SoundEmitter;

class SoundManager : public Entity
{
public:
	SoundManager(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType);
	virtual void Update(sf::RenderWindow& window, float deltaTime) override;

	void PlaySound(SoundEnums sound);
	std::unordered_map<SoundEnums, sf::SoundBuffer*>& GetSoundBank();

private:
	void InitializedSoundBank();
	void InitializedSoundBuffer(SoundEnums sound, std::string fileName);
	std::unordered_map<SoundEnums, sf::SoundBuffer*> _soundBank;
	std::set<SoundEmitter*> _playedSounds;


	// Sound File Path
	std::string _globalFilePath = "../sounds/";
	std::string _audioType = ".wav";

	std::string fileName_MusicMainMenu = "007_James_Bond_Theme";

	std::string fileName_ShotPistolSound = "pistol_shot";
	std::string fileName_ImpactConcreteSound = "Concrete_4";
	std::string fileName_ImpactBloodSound = "Concrete_7";
	std::string fileName_DeathSound = "Player_Death_Scream_Sound_Effect_Fourth_Variation";

	std::string fileName_UIButtonHoverSound = "Hover_sound";
	std::string fileName_UIButtonClickSound = "Click_sound";
};