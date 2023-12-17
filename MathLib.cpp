#include "MathLib.h"
#include <iostream>


sf::Vector2f MathLib::NormalizedVector(sf::Vector2f vector) {
    float length = GetMagnitude(vector);

    if (length != 0) {
        return vector / length;
    }

    return vector;
}

float MathLib::GetMagnitude(sf::Vector2f vector)
{
    return std::sqrt(vector.x * vector.x + vector.y * vector.y);
}

float MathLib::GetDistanceBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2)
{
    return std::sqrt(static_cast<float>(std::pow(vector1.x - vector2.x, 2)) + static_cast<float>(std::pow(vector1.y - vector2.y, 2)));
}

float MathLib::Dot(sf::Vector2f& v1, sf::Vector2f& v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

bool MathLib::IsPointInsideCircle(sf::Vector2f point, sf::CircleShape circle)
{
    float distance = GetDistanceBetweenVectors(point, circle.getPosition());

    return distance < circle.getRadius();
}



bool MathLib::IsPointInsideConvexShape(sf::Vector2f point, std::list<sf::Vector2f>& convexShape) {

    // Check if the shape has at least 3 vertices
    if (convexShape.size() < 3) {
        return false;
    }

    auto it = convexShape.begin();
    sf::Vector2f prevVertex = *it;
    ++it;

    for (; it != convexShape.end(); ++it) {
        sf::Vector2f currentVertex = *it;
        sf::Vector2f edge = currentVertex - prevVertex;

        if (edge.x * (point.y - prevVertex.y) - edge.y * (point.x - prevVertex.x) > 0) {
            // Point is to the right of the edge, not inside the convex shape
            return false;
        }

        prevVertex = currentVertex;
    }

    return true;

}


bool MathLib::IsPointInsideConvexShape(sf::Vector2i point, std::list<sf::Vector2f>& convexShape) {

    // Check if the shape has at least 3 vertices
    if (convexShape.size() < 3) {
        return false;
    }

    auto it = convexShape.begin();
    sf::Vector2f prevVertex = *it;
    ++it;

    for (; it != convexShape.end(); ++it) {
        sf::Vector2f currentVertex = *it;
        sf::Vector2f edge = currentVertex - prevVertex;

        if (edge.x * (point.y - prevVertex.y) - edge.y * (point.x - prevVertex.x) > 0) {
            // Point is to the right of the edge, not inside the convex shape
            return false;
        }

        prevVertex = currentVertex;
    }

    return true;

}



bool MathLib::IsRayCircleIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::CircleShape& circle, sf::Vector2f& intersectionPoint)
{
    /*sf::Vector2f toCircle = circle.getPosition() - rayOrigin;

    float t = (toCircle.x * rayDirection.x + toCircle.y * rayDirection.y) / (rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);

    if (t >= 0.0f && std::hypot(toCircle.x, toCircle.y) <= circle.getRadius())
    {
        intersectionPoint = rayOrigin + t * rayDirection;
        return true; 
    }

    return false;*/

    /*sf::Vector2f s = rayOrigin - circle.getPosition();
    float b = Dot(s, rayDirection);
    float c = Dot(s, s) - circle.getRadius() * circle.getRadius();
    float h = b * b - c;

    if (h < 0.0f) return false;

    h = std::sqrt(h);
    float t = -b - h;

    intersectionPoint = rayDirection * std::fmaxf(t, 0);
     
    return true;*/

    return false;
}


bool MathLib::IsRayRectangleIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::RectangleShape& rectangle, sf::Vector2f& intersectionPoint)
{
    rayDirection = NormalizedVector(rayDirection);
    float closestDistance = FLT_MAX;
    float newDistance = FLT_MAX;
    sf::Vector2f temporaryVector = intersectionPoint;  // Initialize to ray origin
    bool contact = false;

    // Check if the ray origin is inside the rectangle
    if (rectangle.getGlobalBounds().contains(rayOrigin))
    {
        intersectionPoint = rayOrigin;
        return true;
    }

    for (int i = 0; i <= 3; i++) {


        /*sf::Vector2f sizeOffset = sf::Vector2f(0, 0);

        sizeOffset.x = rectangle.getSize().x * 0.5f;
        sizeOffset.y = rectangle.getSize().y * 0.5f;
        if (rectangle.getPoint(i).x > 0) sizeOffset.x = sizeOffset.x;
        if (rectangle.getPoint(i).x < 0) sizeOffset.x = -sizeOffset.x;
        if (rectangle.getPoint(i).y > 0) sizeOffset.y = sizeOffset.y;
        if (rectangle.getPoint(i).y < 0) sizeOffset.y = -sizeOffset.y;

        if (i < 3) {
            if (IsRaySegmentIntersection(rayOrigin, rayDirection, rectangle.getPosition() + rectangle.getPoint(i) + sizeOffset, rectangle.getPosition() + rectangle.getPoint(i + 1) + sizeOffset, temporaryVector)) contact = true;
        }
        else {
            if (IsRaySegmentIntersection(rayOrigin, rayDirection, rectangle.getPosition() + rectangle.getPoint(i) + sizeOffset, rectangle.getPosition() + rectangle.getPoint(0) + sizeOffset, temporaryVector)) contact = true;
        }*/

        if (i < 3) {
            if (IsRaySegmentIntersection(rayOrigin, rayDirection, rectangle.getPosition() + rectangle.getPoint(i) - (rectangle.getSize() * 0.5f), rectangle.getPosition() + rectangle.getPoint(i + 1) - (rectangle.getSize() * 0.5f), temporaryVector)) contact = true;
        }
        else {
            if (IsRaySegmentIntersection(rayOrigin, rayDirection, rectangle.getPosition() + rectangle.getPoint(i) - (rectangle.getSize() * 0.5f), rectangle.getPosition() + rectangle.getPoint(0) - (rectangle.getSize() * 0.5f), temporaryVector)) contact = true;
        }



        newDistance = GetDistanceBetweenVectors(rayOrigin, temporaryVector);

        if (newDistance < closestDistance) {
            closestDistance = newDistance;
            intersectionPoint = temporaryVector;
        }

    }

    return contact;
}

bool MathLib::IsRaySegmentIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::Vector2f pointA, sf::Vector2f pointB, sf::Vector2f& intersectionPoint)
{
    float x1 = pointA.x;
    float y1 = pointA.y;
    float x2 = pointB.x;
    float y2 = pointB.y;


    float x3 = rayOrigin.x;
    float y3 = rayOrigin.y;
    float x4 = rayOrigin.x + rayDirection.x;
    float y4 = rayOrigin.y + rayDirection.y;


    float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (den == 0) {
        return false;
    }

    float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
    float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;

    if (t > 0 && t < 1 && u > 0) {
        intersectionPoint.x = x1 + t * (x2 - x1);
        intersectionPoint.y = y1 + t * (y2 - y1);

        return true;
    }
    else {
        return false;
    }
}