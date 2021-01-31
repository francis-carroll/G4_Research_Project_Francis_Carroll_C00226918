#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>
#include <BSPTree.h>
#include <Globals.h>
#include <LevelLoader.h>

using namespace std;
using namespace sf;

/// <summary>
/// Contains the rooms, corridors and BSP splitting
/// </summary>
class BSPFloor
{
public:
	BSPFloor(shared_ptr<BSPData> t_bspData);
	~BSPFloor();

	void keyInput(Event& t_event);
	void render(shared_ptr<RenderWindow> t_window);
private:
	float ROOM_SIZE_PADDING;
	float ROOM_POSITION_PADDING;
	Vector2f MAX_ROOM_SIZE;
	Vector2f MIN_ROOM_SIZE;
	Vector2f BSP_STARTING_POSITION;
	float ROOM_CONNECTION_DISTANCE;
	float ROOM_CONNECTION_OFFSET;
	float ROOM_CONNECTION_OFFSET_HW;
	Vector2f BSP_AREA_SIZE;
	int BSP_DEPTH;

	void generateBSP();
	void setupRooms();
	void setupCorridors();
	void loadData();

	bool checkRoomPosition(shared_ptr<Door> t_door1, shared_ptr<Door> t_door2);

	vector<shared_ptr<Room>> m_rooms;
	shared_ptr<BSPNode> m_bspHead;
	vector<VertexArray> m_corridors;

	bool m_renderRooms;
	bool m_renderBSP;
	bool m_renderCorridors;
	shared_ptr<BSPData> m_bspData;
};