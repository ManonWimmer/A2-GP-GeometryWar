#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <fstream>
#include "ManagerEntity.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "GameManager.h"
#include "Weapon.h"
#include "EditeurManager.h"
#include "Camera.h"
#include "ParticleSystem.h"
#include "Menu.h"

#include <cstdlib>

constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation
	//sf::RenderWindow window(sf::VideoMode(720, 480), "James Bond");
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "James Bond");
	window.setVerticalSyncEnabled(true);

	sf::Clock frameClock;
	CollisionDetection collisionDetection;
	ManagerEntity entityManager(&collisionDetection);
	entityManager.InitializedParticles(entityManager);

	GameManager gameManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);
	entityManager.AddEntity(&gameManager);

	Menu menu(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType, window, gameManager);
	entityManager.AddEntity(&menu);

	//gameManager.StartLevel(1);

	// Camera
	sf::View mapView = sf::View(sf::FloatRect(0, 0, 800, 600));
	sf::View playerView = sf::View(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));
	Camera camera(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType,  gameManager.GetPlayer(), mapView, playerView);

	entityManager.AddEntity(&camera);

	//EditeurManager editeurManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);

	
	bool hasBurst = false;
	std::srand(std::time(nullptr)); // Initialisation random

	while (window.isOpen())
	{
		
		// Gérer les événéments survenus depuis le dernier tour de boucle
		sf::Event event;
		while (window.pollEvent(event))
		{
			// On gère l'événément
			switch (event.type)
			{
				case sf::Event::Closed:
					// L'utilisateur a cliqué sur la croix => on ferme la fenêtre
					window.close();
					break;

				default:
					break;
			}
		}

		float deltaTime = frameClock.restart().asSeconds();


		
		// Remise au noir de toute la fenêtre
		window.clear();

		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime, entityManager);

		//editeurManager.Update(window, deltaTime);


		// On présente la fenêtre sur l'écran
		window.display();
	}
}