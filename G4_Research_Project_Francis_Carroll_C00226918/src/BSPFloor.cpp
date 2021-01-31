#include "BSPFloor.h"

BSPFloor::BSPFloor() : 
	m_renderBSP(true),
	m_renderRooms(false),
	m_renderCorridors(false),
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

bool BSPFloor::checkRoomPosition(shared_ptr<Door> t_door1, shared_ptr<Door> t_door2)
{
	/*connected->getDirection() != DoorDirection::North || connected2->getDirection() != DoorDirection::North &&
	connected->getDirection() != DoorDirection::South || connected2->getDirection() != DoorDirection::South &&
	connected->getDirection() != DoorDirection::West || connected2->getDirection() != DoorDirection::West &&
	connected->getDirection() != DoorDirection::East || connected2->getDirection() != DoorDirection::East*/
	if (t_door1->getDirection() == DoorDirection::North && t_door2->getDirection() == DoorDirection::South ||
		t_door1->getDirection() == DoorDirection::West && t_door2->getDirection() == DoorDirection::East ||
		t_door1->getDirection() == DoorDirection::South && t_door2->getDirection() == DoorDirection::North ||
		t_door1->getDirection() == DoorDirection::East && t_door2->getDirection() == DoorDirection::West)
	{
		if (t_door1->getDirection() == DoorDirection::North)
		{
			if (t_door1->getPosition().y > t_door2->getPosition().y + ROOM_CORRIDOR_OFFSET &&
				t_door1->getPosition().x < t_door2->getPosition().x + ROOM_CORRIDOR_OFFSET_HW && t_door1->getPosition().x > t_door2->getPosition().x - ROOM_CORRIDOR_OFFSET_HW)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::South)
		{
			if (t_door1->getPosition().y + ROOM_CORRIDOR_OFFSET < t_door2->getPosition().y &&
				t_door1->getPosition().x  + ROOM_CORRIDOR_OFFSET_HW > t_door2->getPosition().x && t_door1->getPosition().x - ROOM_CORRIDOR_OFFSET_HW < t_door2->getPosition().x)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::East)
		{
			if (t_door1->getPosition().x + ROOM_CORRIDOR_OFFSET< t_door2->getPosition().x &&
				t_door1->getPosition().y + ROOM_CORRIDOR_OFFSET_HW > t_door2->getPosition().y && t_door1->getPosition().y - ROOM_CORRIDOR_OFFSET_HW < t_door2->getPosition().y)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::West)
		{
			if (t_door1->getPosition().x > t_door2->getPosition().x + ROOM_CORRIDOR_OFFSET &&
				t_door1->getPosition().y < t_door2->getPosition().y + ROOM_CORRIDOR_OFFSET_HW && t_door1->getPosition().y > t_door2->getPosition().y - ROOM_CORRIDOR_OFFSET_HW)
			{
				return true;
			}
		}
	}
	return false;
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
	m_bspHead = bspTree->bsp(Vector2f(10.0f, 10.0f), Vector2f(800.0f, 800.0f), 8);
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
	shared_ptr<Room> bestRoom;
	shared_ptr<Room> bestRoom2;
	shared_ptr<Door> bestVec;
	shared_ptr<Door> bestVec2;
	float bestDistance = 1000000;

	for (shared_ptr<Room> room : m_rooms)
	{
		for (shared_ptr<Door> connected : room->getDoorNodes())
		{
			if(!connected->getMarked())
			{ 
				for (shared_ptr<Room> room2 : m_rooms)
				{
					for (shared_ptr<Door> connected2 : room2->getDoorNodes())
					{
						if (room != room2 && !connected2->getMarked())
						{
							if (checkRoomPosition(connected, connected2))
							{
								float distance = BSPTree::getDistance(connected->getPosition(), connected2->getPosition());

								if (distance < bestDistance)
								{
									if (distance < ROOM_DISTANCE)
									{
										bestDistance = distance;
										bestRoom = room;
										bestRoom2 = room2;
										bestVec = connected;
										bestVec2 = connected2;
									}
								}
							}
						}
					}
				}
				
				/*bestRoom->addConnectedRoom(bestRoom2);
				bestRoom2->addConnectedRoom(bestRoom);*/
				if (bestRoom != nullptr && bestRoom2 != nullptr)
				{
					bestVec->setMarked(true);
					bestVec2->setMarked(true);
					VertexArray line = VertexArray(LinesStrip, 2);
					line[0].position = bestVec->getPosition();
					line[1].position = bestVec2->getPosition();
					line[0].color = Color::Black;
					line[1].color = Color::Blue;
					m_corridors.push_back(line);
				}

				bestDistance = 100000;
				bestRoom = nullptr;
				bestRoom2 = nullptr;
				bestVec = nullptr;
				bestVec2 = nullptr;
			}
		}
	}
}