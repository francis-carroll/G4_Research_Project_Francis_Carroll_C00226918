#include "BSPFloor.h"

BSPFloor::BSPFloor() : 
	m_renderBSP(true),
	m_renderRooms(true),
	m_renderCorridors(true),
	m_bspHead(make_shared<BSPNode>(0,Vector2f(0.0f,0.0f), Vector2f(0.0f, 0.0f))), 
	m_corridors(vector<VertexArray>())
{
	generateBSP();
	setupRooms();
	setupCorridors();
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

void BSPFloor::toggleCorridors()
{
	m_renderCorridors = (m_renderCorridors + 1) % 2;
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
	else if (t_event.key.code == Keyboard::C)
	{
		toggleCorridors();
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

	if (m_renderCorridors)
	{
		for (VertexArray v : m_corridors)
		{
			t_window->draw(v);
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
		Vector2f size = Vector2f(BSPTree::randomFloat(MIN_ROOM_SIZE.x, node->getNodeData()->getSize().x - ROOM_SIZE_PADDING), BSPTree::randomFloat(MIN_ROOM_SIZE.y, node->getNodeData()->getSize().y - ROOM_SIZE_PADDING));
		Vector2f position = Vector2f(BSPTree::randomFloat(node->getNodeData()->getPosition().x + ROOM_POSITION_PADDING, node->getNodeData()->getPosition().x + (node->getNodeData()->getSize().x - size.x) - ROOM_POSITION_PADDING),
									 BSPTree::randomFloat(node->getNodeData()->getPosition().y + ROOM_POSITION_PADDING, node->getNodeData()->getPosition().y + (node->getNodeData()->getSize().y - size.y) - ROOM_POSITION_PADDING));
		m_rooms.push_back(make_shared<Room>(node->getIdentifier(), position, size, Vector2f(0.0f,0.f)));
	}
}

void BSPFloor::setupCorridors()
{
	for (shared_ptr<Room> room : m_rooms)
	{
		for (shared_ptr<Room> room2 : m_rooms)
		{
			if (room != room2)
			{
				float distance = BSPTree::getDistance(room->getCenter(), room2->getCenter());

				if (distance < ROOM_DISTANCE) 
				{
					VertexArray line = VertexArray(LinesStrip, 2);
					line[0].position = room->getCenter();
					line[1].position = room2->getCenter();
					line[0].color = Color::Black;
					line[1].color = Color::Blue;
					m_corridors.push_back(line);
				}
			}
		}
	}
}
