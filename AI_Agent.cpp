#include "AI_Agent.h"

AI_Agent::AI_Agent(ManagerEntity& managerEntity, float radius, sf::Vector2f spawnPosition, float speed)
    : Entity(managerEntity), _speed(speed)
{
    _circle.setFillColor(sf::Color::Yellow);
    _circle.setRadius(radius);
    _circle.setOrigin(_circle.getRadius(), _circle.getRadius());

    _circle.setRadius(radius);
    _circle.setPosition(spawnPosition);

}

void AI_Agent::SetTarget(sf::CircleShape* target) {
    _target = target;
}

void AI_Agent::Chase(float deltaTime) {

    if (_target) {
        sf::Vector2f targetDirection = NormalizedVector(_target->getPosition() - _circle.getPosition());

        _circle.move(targetDirection * _speed * deltaTime);
    }
}

sf::Vector2f AI_Agent::NormalizedVector(sf::Vector2f source) {
    float length = std::sqrt(source.x * source.x + source.y * source.y);

    if (length != 0) {
        return source / length;
    }

    return source;
}

sf::CircleShape& AI_Agent::GetCircle() {
    return _circle;
}

sf::Vector2f& AI_Agent::GetDirection() {
    return _direction;
}

void AI_Agent::Update(sf::RenderWindow& window, float deltaTime) {
    
    Chase(deltaTime);

    window.draw(_circle);
}