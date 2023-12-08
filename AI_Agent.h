#ifndef AI_AGENT_H
#define AI_AGENT_H

#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "ManagerEntity.h"

class Weapon;

class AI_Agent : public Entity {
public:
    AI_Agent(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius, sf::Vector2f spawnPosition, float speed, Player& player);


    bool CheckFieldOfViewCorners();
    bool CheckFieldOfViewEdges();
    void UpdateFieldView(sf::RenderWindow& window, float deltaTime);
    void RotateFieldView(float deltaTime);
    void DrawAgentRenderer(sf::RenderWindow& window);
    void SetTarget(sf::CircleShape* target);
    float GetAngle(sf::Vector2f targetedVector);
    static float GetPositif(float value);
    void Chase(sf::RenderWindow& window, float deltaTime);
    static float GetMagnitude(sf::Vector2f vector);
    float GetDistanceFromAgent(sf::Vector2f vector);
    float GetDistanceBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2);
    sf::Vector2f GetFieldViewPointWorldCoordinates(sf::Vector2f point);
    static sf::Vector2f NormalizedVector(sf::Vector2f source);
    sf::CircleShape& GetCircle();
    sf::Vector2f& GetDirection();

    void Death();
    void GetWeapon();

    //Function coming from Entity
    virtual void Update(sf::RenderWindow& window, float deltaTime) override;
    virtual void OnDestroy() override;
    sf::CircleShape& GetEntityCircleShape() override;

private:
    Player& currentPlayer;
    Weapon* _ptrPistol;
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

    float coolDown = 3.0f;
    float currentShootTimer;

public: 
    bool isDead;
    bool initializedChase;
};

#endif


