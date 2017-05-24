//
// Created by frabe808 on 16/12/16.
//

#ifndef TDP005_MATHF_H
#define TDP005_MATHF_H


#include <SFML/System.hpp>

class Mathf
{
public:
	static float distance(const sf::Vector2f &, const sf::Vector2f &);

	static float Lerp (const float f1, const float f2, float amount);

};


#endif //TDP005_MATHF_H
