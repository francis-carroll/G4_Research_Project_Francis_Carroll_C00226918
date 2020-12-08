#include "BSPFloor.h"

BSPFloor::BSPFloor() : 
	m_renderBSP(true),
	m_renderRooms(true),
	m_bspHead(make_shared<BSPNode>(0,Vector2f(0.0f,0.0f), Vector2f(0.0f, 0.0f)))
{
	generateBSP();
	setupRooms();
}

BSPFloor::~BSPFloor()
{
}

void BSPFloor::toggleRooms()
{
	m_renderRooms = (m_renderRooms + 1) % 2;
}

void BSPFloor::toggleBSP()
{
	m_renderBSP = (m_renderBSP + 1) % 2;
}

void BSPFloor::keyPressed(Event& t_event)
{
	if (t_event.key.code == Keyboard::R)
	{
		toggleRooms();
	}
	else if (t_event.key.code == Keyboard::B)
	{
		toggleBSP();
	}
}

void BSPFloor::render(shared_ptr<RenderWindow> t_window)
{
	if (m_renderBSP)
	{
		BSPTree::renderLeafNodes(*t_window, m_bspHead);
	}

	if (m_renderRooms)
	{
		for (shared_ptr<Room> room : m_rooms)
		{
			t_window->draw(room->getRoom());
		}
	}
}

void BSPFloor::generateBSP()
{
	shared_ptr<BSPTree> bspTree = make_shared<BSPTree>();
	bspTree->setPadding(MAX_ROOM_SIZE.x, MAX_ROOM_SIZE.y, MAX_ROOM_SIZE.x, MAX_ROOM_SIZE.y);
	bspTree->setMinRoomsize(MAX_ROOM_SIZE);
	m_bspHead = bspTree->bsp(Vector2f(10.0f, 10.0f), Vector2f(800.0f, 800.0f));
}

void BSPFloor::setupRooms()
{
	shared_ptr<vector<shared_ptr<BSPNode>>> leafNodes = make_shared<vector<shared_ptr<BSPNode>>>();
	BSPTree::getLeafNodes(m_bspHead, leafNodes);
	for (shared_ptr<BSPNode> node : *leafNodes)
	{
		Vector2f size = Vector2f(BSPTree::randomFloat(MIN_ROOM_SIZE.x, node->getNodeData()->getSize().x), BSPTree::randomFloat(MIN_ROOM_SIZE.y, node->getNodeData()->getSize().y));
		m_rooms.push_back(make_shared<Room>(node->getIdentifier(), node->getNodeData()->getPosition(), size, Vector2f(0.0f,0.f)));
	}
}