#ifndef LEVELLOADERSTRUCTS
#define LEVELLOADERSTRUCTS

#include <string>

using namespace std;
using namespace sf;

struct BSP
{
	float m_roomPadding;
	float m_roomPositionPadding;
	Vector2f m_maxRoomSize;
	Vector2f m_minRoomSize;
	Vector2f m_bspStartingPosition;
	float m_roomConnectionDistance;
	float m_roomConnectionOffset;
	float m_roomConnectionOffsetHW;
	int m_bspDepth;
	Vector2f m_bspAreaSize;
};

struct BSPData
{
	shared_ptr<BSP> m_bsp = make_shared<BSP>();
};

#endif