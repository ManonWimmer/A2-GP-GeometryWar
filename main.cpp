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
		window.clear();
		

		// Affichage
		entityManager.UpdateAllEntities(window, deltaTime, entityManager);
		//collisionDetection.CheckAllEntitiesCollisions(entityManager);

		//editeurManager.Update(window, deltaTime);


		// On pr�sente la fen�tre sur l'�cran
		window.display();
	}
}