#pragma once

#include <SFML/Graphics.hpp>

class Door;

using namespace std;
using namespace sf;

/// <summary>
/// visual room that is generated in the algorithms
/// </summary>
class Room
{
public:
	Room();
	Room(int t_id, Vector2f t_position, Vector2f t_size, Vector2f t_center);
	~Room();

	void addConnectedRoom(Room* t_room);

	RectangleShape* getRoom();
	Vector2f getCenter();
	int getID();
	vector<Room*>* getConnectedRoom();
	vector<Door*>* getDoorNodes();
private:
	void setupShape();

	int m_id;
	Vector2f m_position;
	Vector2f m_size;
	Vector2f m_center;
	RectangleShape* m_roomShape;

	vector<Room*>* m_connectedRooms;
	vector<Door*>* m_doorNodes;
};

#include <Door.h>