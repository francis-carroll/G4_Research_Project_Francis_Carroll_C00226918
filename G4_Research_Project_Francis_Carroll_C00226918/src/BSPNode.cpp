#include "BSPNode.h"

BSPNode::BSPNode() :
	m_identifier(-1),
	m_nodeData(make_shared<BSPNodeData>(Vector2f(0.0f,0.0f), Vector2f(0.0f, 0.0f)))
{
}

BSPNode::BSPNode(int t_id, Vector2f t_position, Vector2f t_nodeSize) :
	m_identifier(t_id),
	m_nodeData(make_shared<BSPNodeData>(t_position, t_nodeSize))
{
	setupShape();
}

BSPNode::BSPNode(int t_id, BSPNodeData t_nodeData) :
	m_identifier(t_id),
	m_nodeData(make_shared<BSPNodeData>(t_nodeData))
{
	setupShape();
}

BSPNode::~BSPNode()
{
}

int BSPNode::getIdentifier()
{
	return m_identifier;
}

shared_ptr<BSPNode> BSPNode::getLeftNode()
{
	return m_leftNode;
}

shared_ptr<BSPNode> BSPNode::getRightNode()
{
	return m_rightNode;
}

shared_ptr<BSPNodeData> BSPNode::getNodeData()
{
	return m_nodeData;
}

void BSPNode::setIdentifier(int t_identifier)
{
	m_identifier = t_identifier;
}

void BSPNode::setNodeData(BSPNodeData t_nodeData)
{
	m_nodeData = make_shared<BSPNodeData>(t_nodeData);
}

void BSPNode::setLeftNode(shared_ptr<BSPNode> t_node)
{
	m_leftNode = t_node;
}

void BSPNode::setRightNode(shared_ptr<BSPNode> t_node)
{
	m_rightNode = t_node;
}

void BSPNode::draw(RenderWindow& t_window)
{
	t_window.draw(m_shape);
}

void BSPNode::draw(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(m_shape);
}

void BSPNode::setupShape()
{
	m_shape.setPosition(m_nodeData->getPosition());
	m_shape.setSize(m_nodeData->getSize());
	m_shape.setFillColor(sf::Color::White);
	m_shape.setOutlineThickness(1.0f);
	m_shape.setOutlineColor(sf::Color::Black);
}
