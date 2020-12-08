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

	void handleInput(Event& t_event);
private:
	void generateBSP();
	void setupRooms();

	void toggleRooms();
	void toggleBSP();

	vector<shared_ptr<Room>> m_rooms;
	shared_ptr<BSPNode> m_bspHead;

	bool m_renderRooms;
	bool m_renderBSP;
};