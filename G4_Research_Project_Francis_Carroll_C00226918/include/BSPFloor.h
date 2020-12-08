#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>
#include <BSPTree.h>

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
	const Vector2f MAX_ROOM_SIZE = Vector2f(50.0f, 50.0f);
	const Vector2f MIN_ROOM_SIZE = Vector2f(30.0f, 30.0f);

	void generateBSP();
	void setupRooms();

	void toggleRooms();
	void toggleBSP();

	vector<shared_ptr<Room>> m_rooms;
	shared_ptr<BSPNode> m_bspHead;

	bool m_renderRooms;
	bool m_renderBSP;
};