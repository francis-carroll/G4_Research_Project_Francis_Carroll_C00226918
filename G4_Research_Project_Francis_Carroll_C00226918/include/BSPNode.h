#pragma once

#include <SFML/Graphics.hpp>

#include <BSPNodeData.h>

using namespace std;
using namespace sf;

class BSPNode
{
public:
	BSPNode(int t_id = -1, Vector2f t_position = Vector2f(0.0f,0.0f), Vector2f t_nodeSize = Vector2f(0.0f,0.0f));
	BSPNode(int t_id = -1, BSPNodeData t_nodeData = BSPNodeData());
	~BSPNode();

	//getters 
	int getIdentifier();
	shared_ptr<BSPNode> getPreviousNode();
	shared_ptr<BSPNode> getLeftNode();
	shared_ptr<BSPNode> getRightNode();
	shared_ptr<BSPNodeData> getNodeData();

	//setters
	void setIdentifier(int t_identifier);
	void setNodeData(BSPNodeData t_nodeData);
	void setPreviousNode(shared_ptr<BSPNode> t_node);
	void setLeftNode(shared_ptr<BSPNode> t_node);
	void setRightNode(shared_ptr<BSPNode> t_node);

	void draw(RenderWindow& t_window);
private:
	int m_identifier;
	shared_ptr<BSPNodeData> m_nodeData;
	shared_ptr<BSPNode> m_leftNode;
	shared_ptr<BSPNode> m_rightNode;

	//Visalisation of BSP
	RectangleShape m_shape;

	void setupShape();
};

