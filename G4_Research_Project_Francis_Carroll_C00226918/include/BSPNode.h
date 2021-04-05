#pragma once

#include <SFML/Graphics.hpp>

#include <BSPNodeData.h>

using namespace std;
using namespace sf;

/// <summary>
/// Node used in the BSP algorithm
/// </summary>
class BSPNode
{
public:
	BSPNode();
	BSPNode(int t_id, Vector2f t_position, Vector2f t_nodeSize);
	BSPNode(int t_id, BSPNodeData t_nodeData);
	~BSPNode();

	//getters 
	int getIdentifier();
	BSPNode* getLeftNode();
	BSPNode* getRightNode();
	BSPNodeData* getNodeData();

	//setters
	void setIdentifier(int t_identifier);
	void setNodeData(BSPNodeData t_nodeData);
	void setLeftNode(BSPNode* t_node);
	void setRightNode(BSPNode* t_node);

	void render(shared_ptr<RenderWindow> t_window);
private:
	int m_identifier;
	BSPNodeData* m_nodeData;
	BSPNode* m_leftNode;
	BSPNode* m_rightNode;

	//Visalisation of BSP
	RectangleShape* m_shape;

	void setupShape();
};

