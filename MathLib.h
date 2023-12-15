#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <list>


class MathLib
{
public:
	static sf::Vector2f NormalizedVector(sf::Vector2f vector);
	static float GetMagnitude(sf::Vector2f vector);
	static float GetDistanceBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2);

	static float Dot(sf::Vector2f& v1, sf::Vector2f& v2);
	
	static bool IsPointInsideCircle(sf::Vector2f point, sf::CircleShape circle);

	static bool IsPointInsideConvexShape(sf::Vector2f point, std::list<sf::Vector2f>& convexShape);

	static bool IsPointInsideConvexShape(sf::Vector2i point, std::list<sf::Vector2f>& convexShape);



	static bool IsRayCircleIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::CircleShape& circle, sf::Vector2f& intersectionPoint);

	static bool IsRayRectangleIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::RectangleShape& rectangle, sf::Vector2f& intersectionPoint);

	static bool IsRaySegmentIntersection(sf::Vector2f rayOrigin, sf::Vector2f rayDirection, sf::Vector2f pointA, sf::Vector2f pointB, sf::Vector2f& intersectionPoint);

};

