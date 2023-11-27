#include "Weapon.h"

Weapon::Weapon(WeaponType weaponType, sf::RectangleShape rectangle)
{
	switch (weaponType)
	{
	case WeaponType::Pistol:
		this->_fireRate = 20;
		this->_bulletSpeed = 150;
		this->_fireTime = 5;
		this->_rectangle = rectangle;
		break;

	default:
		this->_fireRate = 0;
		this->_bulletSpeed = 0;
		this->_fireTime = 0;
		this->_rectangle = rectangle;
		break;
	}
}

void Weapon::Shoot()
{
	// Get positions
	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	sf::Vector2f bulletOrigin = _rectangle.getPosition();
	
	sf::Vector2f bulletDirection;

	// Calcul de la direction du projectile
	sf::Vector2f bulletDirection = static_cast<sf::Vector2f>(mousePosition) - bulletOrigin;

	// Normalisation du vecteur pour obtenir une direction unitaire (longueur 1)
	float length = std::sqrt(bulletDirection.x * bulletDirection.x + bulletDirection.y * bulletDirection.y);
	if (length != 0)
	{
		bulletDirection /= length;
	}

	// Nouveau projectile
	sf::CircleShape projectileShape;
	Projectile* ptrNewProjectile = new Projectile(bulletOrigin, bulletDirection, 0, _bulletSpeed, projectileShape);

	// Ajout � la liste des projectiles
	_weaponPtrProjectiles.push_back(ptrNewProjectile);
}

void Weapon::CheckProjectiles(float deltaTime)
{
	if (_weaponPtrProjectiles.size() > 0)
	{
		// For chaque projectile dans la liste de ptr
		for (Projectile* projectile : _weaponPtrProjectiles)
		{
			// Ajouter � son current time le delta time pass�
			projectile->CurrentTime += deltaTime;

			// Si sup�rieur � son fireTime -> on le delete
			if (projectile->CurrentTime > this->_fireTime)
			{
				delete projectile;
			}
			// Sinon, on d�place le projectile
			else 
			{
				projectile->MoveProjectile(deltaTime);
			}
		}		
	}
}