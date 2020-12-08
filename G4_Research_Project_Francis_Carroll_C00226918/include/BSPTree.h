#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#include <BSPNode.h>
#include <BSPNodeData.h>

#include <queue>
#include <random>
#include <vector>

using namespace std;

enum SplitDirection {
	Vertical, 
	Horizonal
};

class BSPTree
{
public:
	BSPTree();
	~BSPTree();
	shared_ptr<BSPNode> bsp(Vector2f t_graphPosition, Vector2f t_graphSize);
	shared_ptr<BSPNode> split(shared_ptr<BSPNodeData> t_node);
	shared_ptr<pair<BSPNodeData, BSPNodeData>> randomSplit(shared_ptr<BSPNodeData> t_node, int t_direction);
	static int randomInt(int t_min, int t_max);
	static float randomFloat(float t_min, float t_max);
	static void renderLeafNodes(RenderWindow& t_window, shared_ptr<BSPNode> t_node);
	static void renderLeafNodes(shared_ptr<RenderWindow> t_window, shared_ptr<BSPNode> t_node);
	static void getLeafNodes(shared_ptr<BSPNode> t_node, shared_ptr<vector<shared_ptr<BSPNode>>>);
	static float getDistance(Vector2f t_vector1, Vector2f t_vector2);
	void setPadding(float t_h_min, float t_h_max, float t_w_min, float t_w_max);
	void setMinRoomsize(Vector2f t_minRoomSize);
private:
	float H_MIN = 30;
	float H_MAX = 30;
	float W_MIN = 30;
	float W_MAX = 30;

	Vector2f MIN_ROOM_SIZE = Vector2f(50.0f, 50.0f);
};

