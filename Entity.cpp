#include <SFML/Graphics.hpp>

class Entity {
public:
	virtual void Update(sf::RenderWindow& window, float& deltaTime);
};