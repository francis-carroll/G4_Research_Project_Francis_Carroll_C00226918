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
	bool m_renderRooms;
	bool m_renderBSP;
	bool m_renderCorridor;
	Vector2f m_heightConstraint;
	Vector2f m_widthConstraint;
};

struct BSPData
{
	~BSPData() { delete m_bsp; }
	BSP* m_bsp = new BSP();
};

struct CAS
{
	float m_chanceToBecomeWall;
	Vector2f m_caStartingPosition;
	Vector2f m_caGridSize;
	Vector2f m_cellCount;
	int m_floorToWallConversion;
	int m_wallToFloorConversion;
	int m_iterations;
	int m_recursiveDepth;
	int m_maxCaveSize;
};

struct CAData
{
	~CAData() 
	{ 
		if(m_ca != nullptr)
			delete m_ca; 
	}

	CAS* m_ca = new CAS();
};

#endif