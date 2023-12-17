#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "ManagerEntity.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "GameManager.h"
#include "Weapon.h"
#include "EditeurManager.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Menu.h"
#include "Light.h"
#include "SoundManager.h"
#include "SoundEmitter.h"

int main()
{
	// Initialisation
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "James Bond", sf::Style::Fullscreen);
	window.setVerticalSyncEnabled(true);

	sf::Clock frameClock;

	CollisionDetection collisionDetection;

	ManagerEntity entityManager(&collisionDetection, &window);
	entityManager.InitializedSystems();
	entityManager.GetSoundManager().PlaySound(SoundEnums::MusicMainMenu);

	GameManager gameManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);
	gameManager.InitializedGameManager(window, gameManager);
	entityManager.AddEntity(&gameManager);
	collisionDetection.SetGameManager(&gameManager);

	bool hasBurst = false;
	std::srand(static_cast<unsigned int>(std::time(nullptr))); // Initialisation random

	//EditeurManager editeurManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);

	while (window.isOpen())
	{
		// G�rer les �v�n�ments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On g�re l'�v�n�ment
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqu� sur la croix => on ferme la fen�tre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();

		// Remise au noir de toute la fen�tre
		window.clear(sf::Color(90, 90, 90, 255));
		
		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime, entityManager);
		//editeurManager.Update(window, deltaTime);

		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}
}