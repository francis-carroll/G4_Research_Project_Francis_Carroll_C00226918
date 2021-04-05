#pragma once

#include <SFML/Graphics.hpp>

#include <Room.h>
#include <BSPTree.h>
#include <Globals.h>
#include <LevelLoader.h>
#include <chrono>

using namespace std;
using namespace sf;

/// <summary>
/// Contains the rooms, corridors and BSP splitting
/// </summary>
class BSPFloor
{
public:
	BSPFloor(BSPData* t_bspData);
	~BSPFloor();

	void keyInput(Event& t_event);
	void render(shared_ptr<RenderWindow> t_window);
private:
	float ROOM_SIZE_PADDING = 0.0f;
	float ROOM_POSITION_PADDING = 0.0f;
	Vector2f MAX_ROOM_SIZE = Vector2f(0.0f,0.0f);
	Vector2f MIN_ROOM_SIZE = Vector2f(0.0f, 0.0f);
	Vector2f BSP_STARTING_POSITION = Vector2f(0.0f, 0.0f);
	float ROOM_CONNECTION_DISTANCE = 0.0f;
	float ROOM_CONNECTION_OFFSET = 0.0f;
	float ROOM_CONNECTION_OFFSET_HW = 0.0f;
	Vector2f BSP_AREA_SIZE = Vector2f(0.0f, 0.0f);
	int BSP_DEPTH = 0;

	void generateBSP();
	void setupRooms();
	void setupCorridors();
	void loadData();

	bool checkRoomPosition(Door* t_door1, Door* t_door2);

	vector<Room*>* m_rooms;
	BSPNode* m_bspHead;
	vector<VertexArray>* m_corridors;

	bool m_renderRooms;
	bool m_renderBSP;
	bool m_renderCorridors;
	BSPData* m_bspData;
};