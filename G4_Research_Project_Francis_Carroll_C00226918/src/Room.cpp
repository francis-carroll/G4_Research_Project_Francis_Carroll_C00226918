#include "..\include\Room.h"

Room::Room() : 
	m_id(0),
	m_position(Vector2f(0.0f,0.0f)),
	m_size(Vector2f(0.0f, 0.0f)),
	m_center(Vector2f(0.0f, 0.0f))
{
	setupShape();
}

Room::Room(int t_id, Vector2f t_position, Vector2f t_size, Vector2f t_center) :
	m_id(t_id),
	m_position(t_position),
	m_size(t_size),
	m_center(Vector2f(t_position.x + (t_size.x /2.0f), t_position.y + (t_size.y / 2.0f)))
{
	setupShape();
}

Room::~Room()
{
}

RectangleShape Room::getRoom()
{
	return m_roomShape;
}

Vector2f Room::getCenter()
{
	return m_center;
}

void Room::setupShape()
{
	m_roomShape.setFillColor(Color(153, 153, 153));
	m_roomShape.setOutlineThickness(1.0f);
	m_roomShape.setOutlineColor(Color::Black);
	m_roomShape.setPosition(m_position);
	m_roomShape.setSize(m_size);
}
