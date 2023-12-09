#include "MathLib.h"

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