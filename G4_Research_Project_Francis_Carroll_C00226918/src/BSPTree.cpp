#include "BSPTree.h"

BSPTree::BSPTree()
{
}

BSPTree::~BSPTree()
{
}

shared_ptr<BSPNode> BSPTree::bsp(Vector2f t_graphPosition, Vector2f t_graphSize)
{
	return split(make_shared<BSPNodeData>(t_graphPosition, t_graphSize));
}

shared_ptr<BSPNode> BSPTree::split(shared_ptr<BSPNodeData> t_node)
{
	shared_ptr<BSPNode> root = make_shared<BSPNode>(0, *t_node);
	shared_ptr<pair<BSPNodeData, BSPNodeData>> temp = nullptr;

	if (t_node->getSize().y > MIN_ROOM_SIZE.y *2.0f && t_node->getSize().x <= MIN_ROOM_SIZE.x * 2.0f)
	{
		temp = randomSplit(t_node, 1);
	}
	else if (t_node->getSize().x > MIN_ROOM_SIZE.x * 2.0f  && t_node->getSize().y <= MIN_ROOM_SIZE.y * 2.0f)
	{
		//if the node is wider split it vertically
		temp = randomSplit(t_node, 0);
	}
	else if(t_node->getSize().x > MIN_ROOM_SIZE.x * 2.0f && t_node->getSize().y > MIN_ROOM_SIZE.y * 2.0f){
		temp = randomSplit(t_node, randomInt(0, 1));
	}
	//if the room wasnt split, dont split its neighbour
	if (temp != nullptr)
	{
		root->setLeftNode(split(make_shared<BSPNodeData>(temp->first)));
		root->setRightNode(split(make_shared<BSPNodeData>(temp->second)));
	}
	return root;
}

shared_ptr<pair<BSPNodeData, BSPNodeData>> BSPTree::randomSplit(shared_ptr<BSPNodeData> t_node, int t_direction)
{
	BSPNodeData node1; BSPNodeData node2;
	//horizontal
	if (t_direction == 0)
	{
		node1.setPosition(t_node->getPosition());
		node1.setSize(Vector2f(randomFloat(W_MIN, t_node->getSize().x - W_MAX), t_node->getSize().y));

		node2.setPosition(Vector2f(t_node->getPosition().x + node1.getSize().x, t_node->getPosition().y));
		node2.setSize(Vector2f(t_node->getSize().x - node1.getSize().x, t_node->getSize().y));
	}
	//vertical
	else 
	{
		node1.setPosition(t_node->getPosition());
		node1.setSize(Vector2f(t_node->getSize().x, randomFloat(H_MIN, t_node->getSize().y - H_MAX)));

		node2.setPosition(Vector2f(t_node->getPosition().x, t_node->getPosition().y + node1.getSize().y));
		node2.setSize(Vector2f(t_node->getSize().x, t_node->getSize().y - node1.getSize().y));
	}
	return make_shared<pair<BSPNodeData, BSPNodeData>>(node1, node2);
}

int BSPTree::randomInt(int t_min, int t_max)
{
	if (t_max > t_min) {
		return (rand() % (t_max - t_min + 1)) + t_min;
	}
	return 1;
}

float BSPTree::randomFloat(float t_min, float t_max)
{
	if (t_min < t_max)
	{
		float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

		float range = t_max - t_min;
		return (random * range) + t_min;
	}
}

void BSPTree::renderLeafNodes(RenderWindow& t_window, shared_ptr<BSPNode> t_node)
{
	if (t_node->getLeftNode() != nullptr && t_node->getRightNode() != nullptr)
	{
		renderLeafNodes(t_window, t_node->getLeftNode());
		renderLeafNodes(t_window, t_node->getRightNode());
	}
	else {
		t_node->draw(t_window);
	}
}

void BSPTree::setPadding(float t_h_min, float t_h_max, float t_w_min, float t_w_max)
{
	H_MIN = t_h_min;
	H_MAX = t_h_max;
	W_MIN = t_w_min;
	W_MAX = t_w_max;
}

void BSPTree::setMinRoomsize(Vector2f t_minRoomSize)
{
	MIN_ROOM_SIZE = t_minRoomSize;
}
