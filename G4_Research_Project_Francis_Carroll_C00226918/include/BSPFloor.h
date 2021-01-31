#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>
#include <BSPTree.h>
#include <Globals.h>

using namespace std;
using namespace sf;

class BSPFloor
{
public:
	BSPFloor();
	~BSPFloor();

	void keyPressed(Event& t_event);
	void render(shared_ptr<RenderWindow> t_window);
private:
	const float ROOM_SIZE_PADDING = 20.0f;
	const float ROOM_POSITION_PADDING = 2.0f;
	const Vector2f MAX_ROOM_SIZE = Vector2f(50.0f, 50.0f);
	const Vector2f MIN_ROOM_SIZE = Vector2f(10.0f, 10.0f);
	const float ROOM_DISTANCE = 85.0f;
	const float ROOM_CORRIDOR_OFFSET = 7.0f;
	const float ROOM_CORRIDOR_OFFSET_HW = 45.0f;

	void generateBSP();
	void setupRooms();
	void setupCorridors();

	void toggleRooms();
	void toggleBSP();
	void toggleCorridors();
	bool checkRoomPosition(shared_ptr<Door> t_door1, shared_ptr<Door> t_door2);

	vector<shared_ptr<Room>> m_rooms;
	shared_ptr<BSPNode> m_bspHead;
	vector<VertexArray> m_corridors;

	bool m_renderRooms;
	bool m_renderBSP;
	bool m_renderCorridors;
};