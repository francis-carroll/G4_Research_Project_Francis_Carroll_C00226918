#include "BSPNode.h"

BSPNode::BSPNode() :
	m_identifier(-1),
	m_nodeData(new BSPNodeData(Vector2f(0.0f, 0.0f), Vector2f(0.0f, 0.0f))),
	m_leftNode(nullptr),
	m_rightNode(nullptr),
	m_shape(new RectangleShape())
{
}

BSPNode::BSPNode(int t_id, Vector2f t_position, Vector2f t_nodeSize) :
	m_identifier(t_id),
	m_nodeData(new BSPNodeData(t_position, t_nodeSize)), 
	m_leftNode(nullptr),
	m_rightNode(nullptr),
	m_shape(new RectangleShape())
{
	setupShape();
}

BSPNode::BSPNode(int t_id, BSPNodeData t_nodeData) :
	m_identifier(t_id),
	m_nodeData(new BSPNodeData(t_nodeData)), 
	m_leftNode(nullptr),
	m_rightNode(nullptr),
	m_shape(new RectangleShape())
{
	setupShape();
}

BSPNode::~BSPNode()
{
	delete m_nodeData;
	delete m_leftNode;
	delete m_rightNode;
	delete m_shape;
}

int BSPNode::getIdentifier()
{
	return m_identifier;
}

BSPNode* BSPNode::getLeftNode()
{
	return m_leftNode;
}

BSPNode* BSPNode::getRightNode()
{
	return m_rightNode;
}

BSPNodeData* BSPNode::getNodeData()
{
	return m_nodeData;
}

void BSPNode::setIdentifier(int t_identifier)
{
	m_identifier = t_identifier;
}

void BSPNode::setNodeData(BSPNodeData t_nodeData)
{
	m_nodeData = new BSPNodeData(t_nodeData);
}

void BSPNode::setLeftNode(BSPNode* t_node)
{
	m_leftNode = t_node;
}

void BSPNode::setRightNode(BSPNode* t_node)
{
	m_rightNode = t_node;
}

void BSPNode::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(*m_shape);
}

/// <summary>
/// sets up the bsp nodes shape
/// </summary>
void BSPNode::setupShape()
{
	m_shape->setPosition(m_nodeData->getPosition());
	m_shape->setSize(m_nodeData->getSize());
	m_shape->setFillColor(sf::Color::White);
	m_shape->setOutlineThickness(1.0f);
	m_shape->setOutlineColor(sf::Color::Black);
}
