#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class BSPNodeData
{
public:
	BSPNodeData();
	BSPNodeData(Vector2f t_position, Vector2f t_size);

	void setPosition(Vector2f t_position);
	void setSize(Vector2f t_nodeSize);

	Vector2f getPosition();
	Vector2f getSize();
private:
	Vector2f m_position;
	Vector2f m_nodeSize;
};

