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
	sf::Vector2i mousePosition = sf::Mouse::getPosition();
	sf::Vector2f bulletOrigin = _rectangle.getPosition();
	// 
	sf::Vector2f bulletDirection;
	Projectile* ptrNewProjectile = new Projectile(bulletOrigin, bulletDirection, 0, _bulletSpeed);

	_weaponPtrProjectiles.push_back(ptrNewProjectile);
}

void Weapon::CheckProjectiles()
{
	if (_weaponPtrProjectiles.size() > 0)
	{
		// For chaque projectile dans la liste de ptr
			// Ajouter à son 
	}
}