#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include <BSPNode.h>
#include <BSPNodeData.h>
#include <LevelLoader.h>
#include <Globals.h>

#include <queue>
#include <random>
#include <vector>

using namespace std;

/// <summary>
/// Direction of split when the BSP is executing
/// </summary>
enum SplitDirection {
	Vertical, 
	Horizonal
};

/// <summary>
/// BSP Tree contains the algorithm that returns the head to the BSP tree
/// </summary>
class BSPTree
{
public:
	BSPTree(BSPData* t_bspData);
	~BSPTree();

	shared_ptr<BSPNode> bsp(Vector2f t_graphPosition, Vector2f t_graphSize, int t_graphDepth);
	shared_ptr<BSPNode> split(shared_ptr<BSPNodeData> t_node, int t_current);
	shared_ptr<pair<BSPNodeData, BSPNodeData>> randomSplit(shared_ptr<BSPNodeData> t_node, int t_direction);
	static void renderLeafNodes(shared_ptr<RenderWindow> t_window, shared_ptr<BSPNode> t_node);

	//getters
	static void getLeafNodes(shared_ptr<BSPNode> t_node, shared_ptr<vector<shared_ptr<BSPNode>>>);
	static float getDistance(Vector2f t_vector1, Vector2f t_vector2);

	//setters
	void setPadding(float t_h_min, float t_h_max, float t_w_min, float t_w_max);
	void setMinRoomsize(Vector2f t_minRoomSize);
private:
	void loadData();

	float H_MIN;
	float H_MAX;
	float W_MIN;
	float W_MAX;

	Vector2f MIN_ROOM_SIZE;

	int m_nodeCount = 0;
	BSPData* m_bspData;
};

