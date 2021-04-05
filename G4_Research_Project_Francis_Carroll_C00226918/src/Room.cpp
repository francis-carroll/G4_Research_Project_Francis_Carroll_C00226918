#include "Room.h"

Room::Room() : 
	m_id(0),
	m_position(Vector2f(0.0f,0.0f)),
	m_size(Vector2f(0.0f, 0.0f)),
	m_center(Vector2f(0.0f, 0.0f)),
	m_roomShape(new RectangleShape()),
	m_connectedRooms(new vector<Room*>()),
	m_doorNodes(new vector<Door*>())
{
	setupShape();
}

Room::Room(int t_id, Vector2f t_position, Vector2f t_size, Vector2f t_center) :
	m_id(t_id),
	m_position(t_position),
	m_size(t_size),
	m_center(Vector2f(t_position.x + (t_size.x /2.0f), t_position.y + (t_size.y / 2.0f))),
	m_roomShape(new RectangleShape()),
	m_connectedRooms(new vector<Room*>()),
	m_doorNodes(new vector<Door*>())
{
	setupShape();
}

Room::~Room()
{
	delete m_connectedRooms;
	delete m_doorNodes;
	delete m_roomShape;
}

/// <summary>
/// Add a connected room to this room
/// </summary>
/// <param name="t_room"></param>
void Room::addConnectedRoom(Room* t_room)
{
	m_connectedRooms->push_back(t_room);
}

RectangleShape* Room::getRoom()
{
	return m_roomShape;
}

Vector2f Room::getCenter()
{
	return m_center;
}

int Room::getID()
{
	return m_id;
}

vector<Room*>* Room::getConnectedRoom()
{
	return m_connectedRooms;
}

vector<Door*>* Room::getDoorNodes()
{
	return m_doorNodes;
}

/// <summary>
/// sets up the visual for the room shape
/// </summary>
void Room::setupShape()
{
	m_roomShape->setFillColor(Color(153, 153, 153));
	m_roomShape->setOutlineThickness(1.0f);
	m_roomShape->setOutlineColor(Color::Black);
	m_roomShape->setPosition(m_position);
	m_roomShape->setSize(m_size);

	m_doorNodes->push_back(new Door(DoorDirection::North, Vector2f(m_position.x + (m_size.x / 2.0f), m_position.y)));
	m_doorNodes->push_back(new Door(DoorDirection::West, Vector2f(m_position.x, m_position.y + (m_size.y / 2.0f))));
	m_doorNodes->push_back(new Door(DoorDirection::East, Vector2f(m_position.x + m_size.x, m_position.y + (m_size.y / 2.0f))));
	m_doorNodes->push_back(new Door(DoorDirection::South, Vector2f(m_position.x + (m_size.x / 2.0f), m_position.y + m_size.y)));
}
