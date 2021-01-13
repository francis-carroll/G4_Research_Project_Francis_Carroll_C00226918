#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>

using namespace std;

enum class Direction
{
	NorthSouth,
	NorthEast,
	NorthWest,
	WestEast
};

class Corridor
{
public:
	Corridor(Direction t_direction, shared_ptr<Room> t_room1, shared_ptr<Room> t_room2);
	~Corridor();
private:
	Vector2f m_startPos;
	Vector2f m_endPos;
	shared_ptr<Room> m_startRoom;
	shared_ptr<Room> m_endRoom;
	Direction m_corridorDirection;
};

