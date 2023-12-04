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
constexpr float cubeSpeed = 500.f;

int main()
{
	// Initialisation
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Geometry Wars");
	window.setVerticalSyncEnabled(true);

	sf::Clock frameClock;
	CollisionDetection collisionDetection;
	ManagerEntity entityManager(&collisionDetection);
	Player player(entityManager, collisionDetection, EntityType::Player_Entity, Faction::PlayerFaction, CollisionType::Circle);
	GameManager gameManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType, player);

	entityManager.AddEntity(&gameManager);
	entityManager.AddEntity(&player);

	//EditeurManager editeurManager(entityManager, collisionDetection, EntityType::None_Entity, Faction::None_Faction, CollisionType::None_CollisionType);

	//entityManager.DebugEntities(entityManager, collisionDetection, player);

	gameManager.StartLevel(1);
	

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
		//collisionDetection.CheckAllEntitiesCollisions(entityManager);

		//editeurManager.Update(window, deltaTime);


		// On présente la fenêtre sur l'écran
		window.display();
	}
}