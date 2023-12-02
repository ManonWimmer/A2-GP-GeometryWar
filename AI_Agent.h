#ifndef AI_AGENT_H
#define AI_AGENT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ManagerEntity.h"

class AI_Agent : public Entity {
public:
    AI_Agent(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius, sf::Vector2f spawnPosition, float speed, Player& player);


    bool CheckFieldOfViewCorners();
    bool CheckFieldOfViewEdges();
    void UpdateFieldView();
    void DrawAgentRenderer(sf::RenderWindow& window);
    void SetTarget(sf::CircleShape* target);
    float GetAngle(sf::Vector2f targetedVector);
    float GetPositif(float value);
    void Chase(float deltaTime);
    float GetMagnitude(sf::Vector2f vector);
    float GetDistanceFromAgent(sf::Vector2f vector);
    float GetDistanceBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2);
    sf::Vector2f GetFieldViewPointWorldCoordinates(sf::Vector2f point);
    sf::Vector2f NormalizedVector(sf::Vector2f source);
    sf::CircleShape& GetCircle();
    sf::Vector2f& GetDirection();
    Player& currentPlayer;

    int GetLife();
    void SetLife(int value);
    void DecreaseLife(int value);
    int ClampInteger(int value, int minimum, int maximum);
    void Death();


    // function update
    virtual void Update(sf::RenderWindow& window, float deltaTime) override;

    //Function coming from Entity
    sf::CircleShape& GetEntityCircleShape() override;

private:
    sf::CircleShape _circle;
    sf::ConvexShape fieldView;
    sf::Vector2f _direction;
    sf::CircleShape* _target = nullptr;
    float _speed;
    float _rotationSpeed;
    float _currentFieldViewRotation;

    sf::CircleShape fvCorner1;
    sf::CircleShape fvCorner2;
    sf::CircleShape fvCorner3;

    int _life;
    float coolDown;
    float currentShootTimer;

public: 
    bool isDead;


};

#endif


