#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>

using namespace std;
using namespace sf;

enum class DoorDirection
{
	North, 
	East,
	South,
	West
};

class Door
{
public:
	Door() = default;
	Door(DoorDirection t_direction, Vector2f t_position);
	~Door();

	Vector2f getPosition();
	DoorDirection getDirection();
	bool getMarked();

	void setMarked(bool t_marked);
private:
	DoorDirection m_direction;
	Vector2f m_doorPosition;
	bool m_marked;
};