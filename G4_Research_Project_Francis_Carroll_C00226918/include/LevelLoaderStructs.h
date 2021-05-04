#ifndef LEVELLOADERSTRUCTS
#define LEVELLOADERSTRUCTS

#include <string>

using namespace std;
using namespace sf;


/// <summary>
/// Data loaded into project for the BSP algorithm
/// </summary>
struct BSP
{
	float m_roomPadding = 0.0f;
	float m_roomPositionPadding = 0.0f;
	Vector2f m_maxRoomSize = Vector2f(0.0f,0.0f);
	Vector2f m_minRoomSize = Vector2f(0.0f, 0.0f);
	Vector2f m_bspStartingPosition = Vector2f(0.0f, 0.0f);
	float m_roomConnectionDistance = 0.0f;
	float m_roomConnectionOffset = 0.0f;
	float m_roomConnectionOffsetHW = 0.0f;
	int m_bspDepth = 0;
	Vector2f m_bspAreaSize = Vector2f(0.0f, 0.0f);
	bool m_renderRooms = false;
	bool m_renderBSP = false;
	bool m_renderCorridor = false;
	Vector2f m_heightConstraint = Vector2f(0.0f, 0.0f);
	Vector2f m_widthConstraint = Vector2f(0.0f, 0.0f);
};

struct BSPData
{
	~BSPData() { delete m_bsp; }
	BSP* m_bsp = new BSP();
};


/// <summary>
/// Data loaded into project for the CA Algorithm
/// </summary>
struct CAS
{
	float m_chanceToBecomeWall = 0.0f;
	Vector2f m_caStartingPosition = Vector2f(0.0f, 0.0f);
	Vector2f m_caGridSize = Vector2f(0.0f, 0.0f);
	Vector2f m_cellCount = Vector2f(0.0f, 0.0f);
	Vector2f m_asyncSize = Vector2f(0.0f, 0.0f);
	Vector2f m_asyncPosition = Vector2f(0.0f, 0.0f);
	int m_floorToWallConversion = 0;
	int m_wallToFloorConversion = 0;
	int m_iterations = 0;
	int m_recursiveDepth = 0;
	int m_maxCaveSize = 0;
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