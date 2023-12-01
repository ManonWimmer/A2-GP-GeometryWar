#include "Weapon.h"
#include <math.h>

Weapon::Weapon(WeaponType weaponType, sf::CircleShape& ownerObject)
{
	switch (weaponType)
	{
	case WeaponType::Pistol:
		this->FireRate = 0.25;
		this->_bulletSpeed = 800;
		this->FireTime = 2;
		this->ownerObject = &ownerObject;

		aimRectangle.setFillColor(sf::Color::White);
		aimRectangle.setPosition(640, 360);
		aimRectangle.setSize(sf::Vector2f(20, 50));
		aimRectangle.setOrigin(aimRectangle.getSize().x / 2, 0);

		break;

	default:
		this->FireRate = 0.5;
		this->_bulletSpeed = 0;
		this->FireTime = 0;
		this->ownerObject = &ownerObject;
		break;
	}
}

void Weapon::Shoot(sf::RenderWindow &window, sf::Vector2f posPlayer)
{
	std::cout << "shoot" << std::endl;

	// Projectile shape
	sf::CircleShape projectileShape;
	projectileShape.setOutlineColor(sf::Color(255, 204, 229, 255));
	projectileShape.setFillColor(sf::Color::White);
	projectileShape.setOutlineThickness(4);
	projectileShape.setRadius(6);

	// Get positions
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f bulletOrigin = sf::Vector2f(posPlayer.x + ownerObject->getRadius() - projectileShape.getRadius(), posPlayer.y + ownerObject->getRadius() - projectileShape.getRadius());

	//std::cout << "mouse " << mousePosition.x << " " << mousePosition.y << " origin " << bulletOrigin.x << " " << bulletOrigin.y << std::endl;
	
	// Calcul de la direction du projectile
	sf::Vector2f bulletDirection = static_cast<sf::Vector2f>(mousePosition) - bulletOrigin;

	// Normalisation du vecteur pour obtenir une direction unitaire (longueur 1)
	float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (length != 0)
	{
		bulletDirection /= length;
	}

	//std::cout << "bullet direction " << bulletDirection.x << " " << bulletDirection.y << std::endl;

	// Nouveau projectile
	projectileShape.setPosition(bulletOrigin.x, bulletOrigin.y);
	window.draw(projectileShape);
	Projectile* ptrNewProjectile = new Projectile(bulletOrigin, bulletDirection, 0, _bulletSpeed, projectileShape);

	// Ajout à la liste des projectiles
	WeaponPtrProjectiles.push_back(ptrNewProjectile);
	//std::cout << "taille apres push back " << WeaponPtrProjectiles.size() << std::endl;
}

void Weapon::CheckProjectiles(sf::RenderWindow& window, float deltaTime)
{
	//std::cout << "taille liste " << WeaponPtrProjectiles.size() << std::endl;
	// For chaque projectile dans la liste de ptr
	std::list<Projectile*>::iterator it = WeaponPtrProjectiles.begin();

	//std::cout << "projectiles : " << WeaponPtrProjectiles.size() << std::endl;

	while (it != WeaponPtrProjectiles.end())
	{

		// Ajouter à son current time le delta time passé
		(*(*it)).CurrentTime += deltaTime;

		window.draw((* (*it)).ProjectileShape);

		// Si supérieur à son fireTime -> on le delete
		if ((*(*it)).CurrentTime > this->FireTime)
		{
			it = WeaponPtrProjectiles.erase(it);
		}
		// Sinon, on déplace le projectile
		else 
		{
			(*(*it)).MoveProjectile(deltaTime);
			it++;
		}
		
	}		
}

void Weapon::CheckRotationAim(sf::RectangleShape& aimShape, sf::RenderWindow& window)
{
	/*
	sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
	sf::Vector2f origin = sf::Vector2f(aimShape.getPosition().x + aimShape.getSize().x / 2, aimShape.getPosition().y + aimShape.getSize().y / 2);
	//aimShape.setOrigin(aimShape.getSize().x / 2, aimShape.getSize().y / 2);
	sf::Vector2f down = sf::Vector2f(0, 1);

	sf::Vector2f bulletDirection = static_cast<sf::Vector2f>(mousePosition) - origin;

	// Normaliser le vecteur de direction
	float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (length != 0) {
		bulletDirection /= length;
	}

	//float angle = atan2(down.y, down.x) - atan2(bulletDirection.y, bulletDirection.x);
	float angle = atan2((mousePosition.y - origin.y), (mousePosition.x - origin.x));

	// Conversion de l'angle en degrés
	angle = angle * 180.0 / atan(1) * 4; // (atan(1) * 4 = pi)

	if (angle < 0)
	{
		angle = 360 -(-angle);

	}

	std::cout << "angle : " << angle << std::endl;

	aimShape.setRotation(angle);*/

	sf::Vector2f curPos;
	curPos.x = aimShape.getGlobalBounds().left;
	curPos.y = aimShape.getGlobalBounds().top;
	sf::Vector2i position = sf::Mouse::getPosition(window);
	//position = sf::Vector2i(window.mapPixelToCoords(position, playerView));

	const float PI = 3.14159265;

	float dx = curPos.x - position.x;
	float dy = curPos.y - position.y;
	float rotation = (atan2(dy, dx)) * 180 / PI;

	aimShape.setRotation(rotation + 90);
}

void Weapon::UpdateWeapon(sf::RenderWindow& window, float deltaTime)
{
	CheckProjectiles(window, deltaTime);
	window.draw(aimRectangle);

	aimRectangle.setPosition(ownerObject->getPosition().x + ownerObject->getRadius(), ownerObject->getPosition().y + ownerObject->getRadius());


	// Verif si il peut tirer (en fonction de fire rate)
	if (shootPressed)
	{
		timeSinceLastShoot += deltaTime;
		if (timeSinceLastShoot >= FireRate)
		{
			shootPressed = false;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if (!shootPressed)
		{
			shootPressed = true;
			timeSinceLastShoot = 0;
			Shoot(window, ownerObject->getPosition());
		}
	}

	CheckRotationAim(aimRectangle, window);
}

