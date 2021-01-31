#include "Door.h"

Door::Door(DoorDirection t_direction, Vector2f t_position) :
	m_direction(t_direction),
	m_doorPosition(t_position),
	m_marked(false)
{
}

Door::~Door()
{
}

Vector2f Door::getPosition()
{
	return m_doorPosition;
}

DoorDirection Door::getDirection()
{
	return m_direction;
}

bool Door::getMarked()
{
	return m_marked;
}

void Door::setMarked(bool t_marked)
{
	m_marked = t_marked;
}
