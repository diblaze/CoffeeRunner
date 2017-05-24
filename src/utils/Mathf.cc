//
// Created by frabe808 on 16/12/16.
//

#include "Mathf.h"
#include <math.h>

/**
 * Calculates the distance between two vectors.
 * @param a - First vector.
 * @param b - Second vector.
 * @return Distance between the vectors.
 */
float Mathf::distance(const sf::Vector2f& a, const sf::Vector2f& b)
{
	return sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2));
}

/**
 * Lerps from start value to end value.
 * @param f1 - Start value
 * @param f2 - End value
 * @param amount - Time to take to fully lerp.
 * @return Lerped value.
 */
float Mathf::Lerp(const float f1, const float f2, float amount)
{
	return f1 + (f2 - f1) * amount;
}
