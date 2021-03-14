#include "BSPFloor.h"

BSPFloor::BSPFloor(shared_ptr<BSPData> t_bspData) :
	m_bspData(t_bspData),
	m_bspHead(make_shared<BSPNode>(0,Vector2f(0.0f,0.0f), Vector2f(0.0f, 0.0f))), 
	m_corridors(vector<VertexArray>())
{
	loadData();
	generateBSP();
	auto start = chrono::steady_clock::now();
	setupRooms();
	setupCorridors();
	auto end = chrono::steady_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	s_bsp_runtime_post = seconds.count() / 1000.0f;
}

BSPFloor::~BSPFloor()
{
}

/// <summary>
/// Checks if the room is the correct location and position in relation to the current door
/// </summary>
/// <param name="t_door1"></param>
/// <param name="t_door2"></param>
/// <returns>true, if the door is in the correct location</returns>
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
			if (t_door1->getPosition().y > t_door2->getPosition().y + ROOM_CONNECTION_OFFSET &&
				t_door1->getPosition().x < t_door2->getPosition().x + ROOM_CONNECTION_OFFSET_HW && t_door1->getPosition().x > t_door2->getPosition().x - ROOM_CONNECTION_OFFSET_HW)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::South)
		{
			if (t_door1->getPosition().y + ROOM_CONNECTION_OFFSET < t_door2->getPosition().y &&
				t_door1->getPosition().x  + ROOM_CONNECTION_OFFSET_HW > t_door2->getPosition().x && t_door1->getPosition().x - ROOM_CONNECTION_OFFSET_HW < t_door2->getPosition().x)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::East)
		{
			if (t_door1->getPosition().x + ROOM_CONNECTION_OFFSET< t_door2->getPosition().x &&
				t_door1->getPosition().y + ROOM_CONNECTION_OFFSET_HW > t_door2->getPosition().y && t_door1->getPosition().y - ROOM_CONNECTION_OFFSET_HW < t_door2->getPosition().y)
			{
				return true;
			}
		}
		else if (t_door1->getDirection() == DoorDirection::West)
		{
			if (t_door1->getPosition().x > t_door2->getPosition().x + ROOM_CONNECTION_OFFSET &&
				t_door1->getPosition().y < t_door2->getPosition().y + ROOM_CONNECTION_OFFSET_HW && t_door1->getPosition().y > t_door2->getPosition().y - ROOM_CONNECTION_OFFSET_HW)
			{
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// Handles keyboard input for the BSP floor
/// </summary>
/// <param name="t_event"></param>
void BSPFloor::keyInput(Event& t_event)
{
	if (t_event.key.code == Keyboard::R)
	{
		toggleBool(m_renderRooms);
	}
	else if (t_event.key.code == Keyboard::B)
	{
		toggleBool(m_renderBSP);
	}
	else if (t_event.key.code == Keyboard::C)
	{
		toggleBool(m_renderCorridors);
	}
}

/// <summary>
/// Renders the bsp floor
/// </summary>
/// <param name="t_window"></param>
void BSPFloor::render(shared_ptr<RenderWindow> t_window)
{
	if (m_renderBSP)
	{
		BSPTree::renderLeafNodes(t_window, m_bspHead);
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

/// <summary>
/// Executes the bsp algorithm and saves the root node
/// </summary>
void BSPFloor::generateBSP()
{
	shared_ptr<BSPTree> bspTree = make_shared<BSPTree>(m_bspData);
	bspTree->setPadding(MAX_ROOM_SIZE.x, MAX_ROOM_SIZE.y, MAX_ROOM_SIZE.x, MAX_ROOM_SIZE.y);
	bspTree->setMinRoomsize(MAX_ROOM_SIZE);
	m_bspHead = bspTree->bsp(BSP_STARTING_POSITION,BSP_AREA_SIZE, BSP_DEPTH);
}

/// <summary>
/// Generates the rooms based on the BSP Nodes
/// </summary>
void BSPFloor::setupRooms()
{
	shared_ptr<vector<shared_ptr<BSPNode>>> leafNodes = make_shared<vector<shared_ptr<BSPNode>>>();
	BSPTree::getLeafNodes(m_bspHead, leafNodes);
	for (shared_ptr<BSPNode> node : *leafNodes)
	{
		Vector2f size = Vector2f(randomFloat(MIN_ROOM_SIZE.x, node->getNodeData()->getSize().x - ROOM_SIZE_PADDING), randomFloat(MIN_ROOM_SIZE.y, node->getNodeData()->getSize().y - ROOM_SIZE_PADDING));
		Vector2f position = Vector2f(randomFloat(node->getNodeData()->getPosition().x + ROOM_POSITION_PADDING, node->getNodeData()->getPosition().x + (node->getNodeData()->getSize().x - size.x) - ROOM_POSITION_PADDING),
									 randomFloat(node->getNodeData()->getPosition().y + ROOM_POSITION_PADDING, node->getNodeData()->getPosition().y + (node->getNodeData()->getSize().y - size.y) - ROOM_POSITION_PADDING));
		m_rooms.push_back(make_shared<Room>(node->getIdentifier(), position, size, Vector2f(0.0f,0.0f)));
	}
}

/// <summary>
/// Generates the corridors from each of the rooms
/// </summary>
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
									if (distance < ROOM_CONNECTION_DISTANCE)
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

/// <summary>
/// loads the bsp data from yaml
/// </summary>
void BSPFloor::loadData()
{
	ROOM_SIZE_PADDING = m_bspData->m_bsp->m_roomPadding;
	ROOM_POSITION_PADDING = m_bspData->m_bsp->m_roomPositionPadding;
	MAX_ROOM_SIZE = m_bspData->m_bsp->m_maxRoomSize;
	MIN_ROOM_SIZE = m_bspData->m_bsp->m_minRoomSize;
	ROOM_CONNECTION_OFFSET = m_bspData->m_bsp->m_roomConnectionOffset;
	ROOM_CONNECTION_OFFSET_HW = m_bspData->m_bsp->m_roomConnectionOffsetHW;
	ROOM_CONNECTION_DISTANCE = m_bspData->m_bsp->m_roomConnectionDistance;
	BSP_AREA_SIZE = m_bspData->m_bsp->m_bspAreaSize;
	BSP_DEPTH = m_bspData->m_bsp->m_bspDepth;
	BSP_STARTING_POSITION = m_bspData->m_bsp->m_bspStartingPosition;

	m_renderBSP = m_bspData->m_bsp->m_renderBSP;
	m_renderCorridors = m_bspData->m_bsp->m_renderCorridor;
	m_renderRooms = m_bspData->m_bsp->m_renderRooms;
}