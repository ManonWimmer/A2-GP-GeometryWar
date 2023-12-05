#include "AI_Agent.h"

#include <iostream>
#include <math.h>
#include <cmath>

#include "CollisionDetection.h" 
#include "Player.h"

#include "Weapon.h"

AI_Agent::AI_Agent(ManagerEntity& managerEntity, CollisionDetection& collisionDetection, EntityType entityType, Faction entityFaction, CollisionType collisionType, float radius, sf::Vector2f spawnPosition, float speed, Player& player)
    : Entity(managerEntity, collisionDetection, entityType, entityFaction, collisionType), _speed(speed), currentPlayer(player), _currentFieldViewRotation(0), _rotationSpeed(60.0f)
{
    _life = 100;
    coolDown = 3.0f;
    currentShootTimer = 0.0f;

    _circle.setFillColor(sf::Color::Black);
    _circle.setRadius(radius);
    _circle.setOrigin(_circle.getRadius(), _circle.getRadius());

    _circle.setOutlineThickness(radius / 5);
    _circle.setOutlineColor(sf::Color(255, 255, 255, 180));

    _circle.setRadius(radius);
    _circle.setPosition(spawnPosition);
    

    fieldView = sf::ConvexShape();
    fieldView.setPointCount(3);

    fieldView.setPoint(0, sf::Vector2f(0, 0));
    fieldView.setPoint(1, sf::Vector2f(-100, 200));
    fieldView.setPoint(2, sf::Vector2f(100, 200));

    fieldView.setFillColor(sf::Color(255, 255, 255, 180));
    fieldView.setOrigin(fieldView.getPoint(0));
    fieldView.setPosition(_circle.getPosition());

    _target = nullptr;
    //_target->setPosition(640, 360);


    fvCorner1.setRadius(7.0f);
    fvCorner1.setOrigin(fvCorner1.getRadius(), fvCorner1.getRadius());

    fvCorner2.setRadius(7.0f);
    fvCorner2.setOrigin(fvCorner2.getRadius(), fvCorner2.getRadius());

    fvCorner3.setRadius(7.0f);
    fvCorner3.setOrigin(fvCorner3.getRadius(), fvCorner3.getRadius());
}


bool AI_Agent::CheckFieldOfViewCorners()
{

    //std::cout << "Distance from third point: " << GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)), currentPlayer.circleShape.getPosition()) << std::endl;
    if (GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)), currentPlayer.circleShape.getPosition()) <= currentPlayer.circleShape.getRadius()) return true;



    //std::cout << "Distance from third point: " << GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)), currentPlayer.circleShape.getPosition()) << std::endl;
    if (GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)), currentPlayer.circleShape.getPosition()) <= currentPlayer.circleShape.getRadius()) return true;


    //std::cout << "Distance from third point: " << GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)), currentPlayer.circleShape.getPosition()) << std::endl;
    if (GetDistanceBetweenVectors(GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)), currentPlayer.circleShape.getPosition()) <= currentPlayer.circleShape.getRadius()) return true;
    

    return false;
}

bool AI_Agent::CheckFieldOfViewEdges()
{
    float k = 0;

    //EDGE 1
    float c1x = currentPlayer.circleShape.getPosition().x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).x;
    float c1y = currentPlayer.circleShape.getPosition().y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).y;

    float e1x = GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).x;
    float e1y = GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).y;

    k = c1x * e1x + c1y * e1y;

    if (k > 0) {
        float length = std::sqrt(e1x * e1x + e1y * e1y);
        k = k / length;
        if (k < length) {
            if (std::sqrt(c1x * c1x + c1y * c1y - k * k) <= currentPlayer.circleShape.getRadius()) {
                //Player Detected !!
                return true;
            }
        }
    }


    //EDGE 2
    float c2x = currentPlayer.circleShape.getPosition().x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).x;
    float c2y = currentPlayer.circleShape.getPosition().y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).y;
           
    float e2x = GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).x;
    float e2y = GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)).y;

    k = c2x * e2x + c2y * e2y;

    if (k > 0) {
        float length = std::sqrt(e2x * e2x + e2y * e2y);
        k = k / length;
        if (k < length) {
            if (std::sqrt(c2x * c2x + c2y * c2y - k * k) <= currentPlayer.circleShape.getRadius()) {
                //Player Detected !!
                return true;
            }
        }
    }




    //EDGE 3
    float c3x = currentPlayer.circleShape.getPosition().x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).x;
    float c3y = currentPlayer.circleShape.getPosition().y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).y;
           
    float e3x = GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).x - GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).x;
    float e3y = GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)).y - GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)).y;

    k = c3x * e3x + c3y * e3y;

    if (k > 0) {
        float length = std::sqrt(e3x * e3x + e3y * e3y);
        k = k / length;
        if (k < length) {
            if (std::sqrt(c3x * c3x + c3y * c3y - k * k) <= currentPlayer.circleShape.getRadius()) {
                //Player Detected !!
                return true;
            }
        }
    }


    return false;
}

void AI_Agent::UpdateFieldView()
{
    fieldView.setPosition(_circle.getPosition());
    //fieldView.setRotation(_circle.getRotation());


    if (CheckFieldOfViewCorners()) {
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;

        _target = &currentPlayer.circleShape;
    }
    else if (CheckFieldOfViewEdges()) {
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;
        std::cout << "Player Detected" << std::endl;

        _target = &currentPlayer.circleShape;
    }

}

void AI_Agent::DrawAgentRenderer(sf::RenderWindow& window)
{
    window.draw(_circle);
    window.draw(fieldView);



    // Debug stuff for ai vision

    /*fvCorner1.setPosition(GetFieldViewPointWorldCoordinates(fieldView.getPoint(0)));
    fvCorner2.setPosition(GetFieldViewPointWorldCoordinates(fieldView.getPoint(1)));
    fvCorner3.setPosition(GetFieldViewPointWorldCoordinates(fieldView.getPoint(2)));

    window.draw(fvCorner1);
    window.draw(fvCorner2);
    window.draw(fvCorner3);*/
}

void AI_Agent::SetTarget(sf::CircleShape* target) {
    _target = target;
}

float AI_Agent::GetAngle(sf::Vector2f targetedVector)
{
    float pi = 3.141592653589793f;

    return std::atan2(targetedVector.y, targetedVector.x) * 180 / pi;
}

float AI_Agent::GetPositif(float value)
{
    return std::sqrtf(value * value);
}

void AI_Agent::Chase(float deltaTime) {

    if (_target) {

        sf::Vector2f targetPosition = _target->getPosition();
        sf::Vector2f objectPosition = _circle.getPosition();
        sf::Vector2f direction = NormalizedVector(targetPosition - objectPosition);

        float rotationAngle = GetAngle(direction);

        float currentRotation = 0;
        float targetRotation = GetPositif(rotationAngle - 90);

        float distanceToTarget = std::sqrt(std::pow(targetPosition.x - objectPosition.x, 2) + std::pow(targetPosition.y - objectPosition.y, 2));

        if (distanceToTarget > 0.15f) {

            float interpolatedRotation = currentRotation + _rotationSpeed * deltaTime;

            if (round(currentRotation) == round(targetRotation)) {
                //_circle.setRotation(targetRotation);

                /*_currentFieldViewRotation = targetRotation;

                sf::Transform rotationTransform;
                rotationTransform.rotate(targetRotation, fieldView.getOrigin());

                sf::Vector2f rotatedPoint1 = rotationTransform.transformPoint(fieldView.getPoint(1));
                sf::Vector2f rotatedPoint2 = rotationTransform.transformPoint(fieldView.getPoint(2));

                fieldView.setPoint(1, rotatedPoint1);
                fieldView.setPoint(2, rotatedPoint2);*/
            }
            else {
                //_circle.setRotation(interpolatedRotation);
                //std::cout << interpolatedRotation << std::endl;

                //_currentFieldViewRotation = interpolatedRotation;
                sf::Transform rotationTransform;
                rotationTransform.rotate(interpolatedRotation, fieldView.getOrigin());

                sf::Vector2f rotatedPoint1 = rotationTransform.transformPoint(fieldView.getPoint(1));
                sf::Vector2f rotatedPoint2 = rotationTransform.transformPoint(fieldView.getPoint(2));

                fieldView.setPoint(1, rotatedPoint1);
                fieldView.setPoint(2, rotatedPoint2);
            }

        }

        if (_currentFieldViewRotation >= 360) {
            _currentFieldViewRotation = 0;
        }
        else if (_currentFieldViewRotation < 0) {
            _currentFieldViewRotation = 360;
        }

        _circle.move(direction * _speed * deltaTime);

    }
}



float AI_Agent::GetMagnitude(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float AI_Agent::GetDistanceFromAgent(sf::Vector2f vector)
{
    return std::sqrt(std::pow(vector.x - _circle.getPosition().x, 2) + std::pow(vector.y - _circle.getPosition().y, 2));
}

float AI_Agent::GetDistanceBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2)
{
    return std::sqrt(std::pow(vector1.x - vector2.x, 2) + std::pow(vector1.y - vector2.y, 2));
}

sf::Vector2f AI_Agent::GetFieldViewPointWorldCoordinates(sf::Vector2f point)
{
    return point + _circle.getPosition();
}

sf::Vector2f AI_Agent::NormalizedVector(sf::Vector2f source) {
    float length = GetMagnitude(source);

    if (length != 0) {
        return source / length;
    }

    return source;
}

sf::CircleShape& AI_Agent::GetCircle() {
    return _circle;
}

sf::Vector2f& AI_Agent::GetDirection() {

    /*_direction.x = cos(_circle.getRotation());
    _direction.y = sin(_circle.getRotation());*/

    return _direction;
}



void AI_Agent::Death()
{
    //isDead = true;
    //managerEntity.RemoveEntity(this);

}

void AI_Agent::GetWeapon()
{
    _ptrPistol = new Weapon(managerEntity, collisionDetection, EntityType::Weapon_Entity, entityFaction, CollisionType::None_CollisionType, WeaponType::Pistol, _circle);
    managerEntity.AddEntity(_ptrPistol);

}



void AI_Agent::Update(sf::RenderWindow& window, float deltaTime) {


    if (!isDead) {
        Chase(deltaTime);
        UpdateFieldView();
        DrawAgentRenderer(window);

        currentShootTimer += deltaTime;
        if (currentShootTimer >= coolDown) {

        }
    }
}

void AI_Agent::OnDestroy()
{

}

sf::CircleShape& AI_Agent::GetEntityCircleShape()
{
    return _circle;
}
