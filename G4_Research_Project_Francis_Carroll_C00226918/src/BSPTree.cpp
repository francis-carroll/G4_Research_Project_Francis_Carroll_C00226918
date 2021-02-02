#include "BSPTree.h"

BSPTree::BSPTree(shared_ptr<BSPData> t_bspData) : 
	m_bspData(t_bspData)
{
	loadData();
}

BSPTree::~BSPTree()
{
}

/// <summary>
/// Return the root node to the BSP tree
/// </summary>
/// <param name="t_graphPosition"></param>
/// <param name="t_graphSize"></param>
/// <param name="t_graphDepth"></param>
/// <returns>shared_ptr<BSPNode></returns>
shared_ptr<BSPNode> BSPTree::bsp(Vector2f t_graphPosition, Vector2f t_graphSize, int t_graphDepth)
{
	return split(make_shared<BSPNodeData>(t_graphPosition, t_graphSize), t_graphDepth);
}

/// <summary>
/// Splits a node and retruns two children nodes if it is possible
/// </summary>
/// <param name="t_node"></param>
/// <param name="t_current"></param>
/// <returns>shared_ptr<BSPNode></returns>
shared_ptr<BSPNode> BSPTree::split(shared_ptr<BSPNodeData> t_node, int t_current)
{
	shared_ptr<BSPNode> root = make_shared<BSPNode>(m_nodeCount, *t_node);
	m_nodeCount++;
	shared_ptr<pair<BSPNodeData, BSPNodeData>> temp = nullptr;

	if (t_current > 0)
	{
		if (t_node->getSize().y > MIN_ROOM_SIZE.y * 2.0f && t_node->getSize().x <= MIN_ROOM_SIZE.x * 2.0f)
		{
			temp = randomSplit(t_node, 1);
		}
		else if (t_node->getSize().x > MIN_ROOM_SIZE.x * 2.0f && t_node->getSize().y <= MIN_ROOM_SIZE.y * 2.0f)
		{
			//if the node is wider split it vertically
			temp = randomSplit(t_node, 0);
		}
		else if (t_node->getSize().x > MIN_ROOM_SIZE.x * 2.0f && t_node->getSize().y > MIN_ROOM_SIZE.y * 2.0f) {
			temp = randomSplit(t_node, randomInt(0, 1));
		}
		//if the room wasnt split, dont split its neighbour
		if (temp != nullptr)
		{
			root->setLeftNode(split(make_shared<BSPNodeData>(temp->first), t_current - 1));
			root->setRightNode(split(make_shared<BSPNodeData>(temp->second), t_current - 1));
		}
		return root;
	}
	return nullptr;
}

/// <summary>
/// Splits the node randomily 
/// </summary>
/// <param name="t_node"></param>
/// <param name="t_direction"></param>
/// <returns></returns>
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

/// <summary>
/// generates a random integer between the t_min and t_max
/// </summary>
/// <param name="t_min"></param>
/// <param name="t_max"></param>
/// <returns>int</returns>
int BSPTree::randomInt(int t_min, int t_max)
{
	if (t_max > t_min) {
		return (rand() % (t_max - t_min + 1)) + t_min;
	}
	return 1;
}

/// <summary>
/// generates a random float between t_min and t_max
/// </summary>
/// <param name="t_min"></param>
/// <param name="t_max"></param>
/// <returns></returns>
float BSPTree::randomFloat(float t_min, float t_max)
{
	if (t_min < t_max)
	{
		float random = (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));

		float range = t_max - t_min;
		return (random * range) + t_min;
	}
}

/// <summary>
/// renders all the leaf nodes of a node
/// </summary>
/// <param name="t_window"></param>
/// <param name="t_node"></param>
void BSPTree::renderLeafNodes(shared_ptr<RenderWindow> t_window, shared_ptr<BSPNode> t_node)
{
	if (t_node->getLeftNode() != nullptr && t_node->getRightNode() != nullptr)
	{
		renderLeafNodes(t_window, t_node->getLeftNode());
		renderLeafNodes(t_window, t_node->getRightNode());
	}
	else {
		t_node->render(t_window);
	}
}

/// <summary>
/// returns all the leaf nodes of a node
/// </summary>
/// <param name="t_node"></param>
/// <param name="t_container"></param>
void BSPTree::getLeafNodes(shared_ptr<BSPNode> t_node, shared_ptr<vector<shared_ptr<BSPNode>>> t_container)
{
	if (t_node->getLeftNode() != nullptr && t_node->getRightNode() != nullptr)
	{
		getLeafNodes(t_node->getLeftNode(), t_container);
		getLeafNodes(t_node->getRightNode(), t_container);
	}
	else {
		t_container->push_back(t_node);
	}
}

/// <summary>
/// returns the distnace between two vectors
/// </summary>
/// <param name="t_vector1"></param>
/// <param name="t_vector2"></param>
/// <returns></returns>
float BSPTree::getDistance(Vector2f t_vector1, Vector2f t_vector2)
{
	return sqrt(pow(t_vector1.x - t_vector2.x, 2.0f) + pow(t_vector1.y - t_vector2.y, 2.0f));
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

void BSPTree::loadData()
{
	H_MIN = m_bspData->m_bsp->m_heightConstraint.x;
	H_MAX = m_bspData->m_bsp->m_heightConstraint.y;
	W_MAX = m_bspData->m_bsp->m_widthConstraint.x;
	W_MIN = m_bspData->m_bsp->m_widthConstraint.y;
}
