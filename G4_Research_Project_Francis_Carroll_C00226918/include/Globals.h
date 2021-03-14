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

static float directDistance(sf::Vector2f t_vector1, sf::Vector2f t_vector2)
{
	return (t_vector2.x - t_vector1.x) + (t_vector2.y - t_vector1.y);
}

static void toggleBool(bool& t_bool)
{
	t_bool = (t_bool + 1) % 2;
}

static int randomInt(int t_min, int t_max)
{
	if (t_max > t_min) {
		return (rand() % (t_max - t_min + 1)) + t_min;
	}
	return 1;
}

static float randomFloat(float t_min, float t_max)
{
	if (t_min < t_max)
	{
		float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

		float range = t_max - t_min;
		return (random * range) + t_min;
	}
	return t_min;
}

enum class Scene
{
	Intro,
	MainMenu,
	Credits,
	CA,
	BSP
};

extern enum Scene s_scene;

extern float s_ca_runtime_core;
extern float s_ca_runtime_post;
extern float s_bsp_runtime_core;
extern float s_bsp_runtime_post;