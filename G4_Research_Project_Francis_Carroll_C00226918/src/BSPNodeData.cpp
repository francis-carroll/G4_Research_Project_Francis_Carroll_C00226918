#include "BSPNodeData.h"

BSPNodeData::BSPNodeData() :
	m_position(Vector2f(0.0f,0.0f)),
	m_nodeSize(Vector2f(0.0f, 0.0f))
{
}

BSPNodeData::BSPNodeData(Vector2f t_position, Vector2f t_size) :
	m_position(t_position),
	m_nodeSize(t_size)
{
}

void BSPNodeData::setPosition(Vector2f t_position)
{
	m_position = t_position;
}

void BSPNodeData::setSize(Vector2f t_nodeSize)
{
	m_nodeSize = t_nodeSize;
}

Vector2f BSPNodeData::getPosition()
{
	return m_position;
}

Vector2f BSPNodeData::getSize()
{
	return m_nodeSize;
}
