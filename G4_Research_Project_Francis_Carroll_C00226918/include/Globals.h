#pragma once

#include <SFML/Graphics.hpp>

const float PI = 3.141592653589f;

static float magnitude(sf::Vector2f t_vector) {
	return std::sqrt(std::pow(t_vector.x, 2.0f) + std::pow(t_vector.y, 2.0f));
}

static sf::Vector2f normalise(sf::Vector2f t_vector) {
	if (magnitude(t_vector) > 0) {
		return t_vector / magnitude(t_vector);
	}
	else {
		return t_vector;
	}
}

static void toggleBool(bool& t_bool)
{
	t_bool = (t_bool + 1) % 2;
}