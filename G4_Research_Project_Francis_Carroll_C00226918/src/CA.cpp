#include "CA.h"

CA::CA(shared_ptr<CAData> t_caData) : 
	m_caData(t_caData),
	m_colors(make_shared<vector<Color>>()),
	m_cavernCount(0),
	m_caverns(make_shared<vector<shared_ptr<vector<shared_ptr<CACell>>>>>()),
	m_tempStates(make_shared<vector<CellState>>())
{
	loadConstants();
	initialIterate();
}

CA::~CA()
{
}

void CA::render(shared_ptr<RenderWindow> t_window)
{
	m_caGrid->render(t_window);
}

void CA::keyPresses(Event& t_event)
{
	if (t_event.key.code == Keyboard::I)
	{
		iterate();
	}
	if (t_event.key.code == Keyboard::P)
	{
		processCA();
	}
	if (t_event.key.code == Keyboard::R)
	{
		processCA();
		removeSmallCaverns();
	}
	/*if (t_event.key.code == Keyboard::C)
	{
		connectCaverns();
	}*/
}

void CA::loadConstants()
{
	m_caGrid = make_shared<CAGrid>(m_caData, m_caData->m_ca->m_caStartingPosition, m_caData->m_ca->m_caGridSize, m_caData->m_ca->m_cellCount);
	m_iterations = m_caData->m_ca->m_iterations;
	m_maxCaveSize = m_caData->m_ca->m_maxCaveSize;
	m_recursiveDepth = m_caData->m_ca->m_recursiveDepth;
	FLOOR_TO_WALL_CONVERSION = m_caData->m_ca->m_floorToWallConversion;
	WALL_TO_FLOOR_CONVERSION = m_caData->m_ca->m_wallToFloorConversion;
}

void CA::initialIterate()
{
	for (int i = 0; i < m_iterations; i++)
	{
		iterate();
	}
}

void CA::iterate()
{
	for (shared_ptr<CACell> c : *m_caGrid->getCells())
	{
		m_tempStates->push_back(applyRules(c));
	}

	for (shared_ptr<CACell> c : *m_caGrid->getCells())
	{
		c->setCellState(m_tempStates->at(c->getID()));
		c->setupColor();
	}
	m_tempStates->clear();
}

CellState CA::applyRules(shared_ptr<CACell> t_current)
{
	int wall = 0;
	int floor = 0;
	for (shared_ptr<CACell> cell : *t_current->getNeighbours())
	{
		if (cell->getCellState() == CellState::Floor)
		{
			floor++;
		}
		else if (cell->getCellState() == CellState::Wall)
		{
			wall++;
		}
	}

	if (wall < WALL_TO_FLOOR_CONVERSION && t_current->getCellState() == CellState::Wall) return CellState::Floor;
	else if (wall > FLOOR_TO_WALL_CONVERSION && t_current->getCellState() == CellState::Floor) return CellState::Wall;
	else return t_current->getCellState();
}

void CA::processCA()
{
	m_caverns->clear();
	int temp = m_cavernCount;

	shared_ptr<vector<shared_ptr<CACell>>> grid = m_caGrid->getCells();
	for (shared_ptr<CACell> c : *grid)
	{
		if (c->getCellState() == CellState::Floor && c->getFillType() == -1)
		{
			m_caverns->push_back(make_shared<vector<shared_ptr<CACell>>>());
			floodFill(c, temp, m_recursiveDepth);
			temp++;
		}

		processQueue();
	}

	//generates colors for cavern
	generateColorsForCaves(temp);

	//sets the caves colors
	shared_ptr<vector<shared_ptr<CACell>>> grid2 = m_caGrid->getCells();
	for (shared_ptr<CACell> c : *grid2)
	{
		if (c->getCellState() == CellState::Floor && c->getFillType() != -1)
		{
			c->setupFloodColor(m_colors);
		}
	}
}

void CA::floodFill(shared_ptr<CACell> t_cell, int t_fillID, int t_depth)
{
	if (t_depth == 0)
	{
		m_queue.push(make_shared<CAPostProcess>(t_cell, t_fillID));
		return;
	}

	if (t_cell->getCellState() != CellState::Floor || t_cell->getFillType() != -1)
		return;

	t_cell->setFillType(t_fillID);
	m_caverns->at(t_fillID)->push_back(t_cell);

	shared_ptr<vector<shared_ptr<CACell>>> neighbours = t_cell->getVonNeighbours();
	for (shared_ptr<CACell> c : *neighbours)
	{
		floodFill(c, t_fillID, t_depth - 1);
	}
}

shared_ptr<vector<shared_ptr<CACell>>> CA::findLargestCavern()
{
	shared_ptr<vector<shared_ptr<CACell>>> largest;
	int maximum = 0;

	for (shared_ptr<vector<shared_ptr<CACell>>> cave : *m_caverns)
	{
		if (maximum < cave->size())
		{
			maximum = cave->size();
			largest = cave;
		}
	}
	return largest;
}

void CA::removeSmallCaverns()
{
	vector<shared_ptr<vector<shared_ptr<CACell>>>> temp;
	shared_ptr<vector<shared_ptr<CACell>>> largest = findLargestCavern();
	for (shared_ptr<vector<shared_ptr<CACell>>> c : *m_caverns)
	{
		if (largest != c && c->size() < m_maxCaveSize)
		{
			for (shared_ptr<CACell> cell : *c)
			{
				cell->setCellState(CellState::Wall);
				cell->setupColor();
			}
			temp.push_back(c);
		}
	}

	//removes all the caves that have been turned into walls
	for (shared_ptr<vector<shared_ptr<CACell>>> c : temp)
	{
		m_caverns->erase(std::remove_if(m_caverns->begin(), m_caverns->end(), [&](shared_ptr<vector<shared_ptr<CACell>>> t_v) { if (t_v == c) return true; else return false; }), m_caverns->end());
	}
}

void CA::astar(shared_ptr<CACell> t_origin, shared_ptr<CACell> t_destination)
{
	list<shared_ptr<CACell>> open;
	list<shared_ptr<CACell>> closed;

	open.push_back(t_origin);

	//reset
	t_origin->path = 0;
	t_origin->heuristic = calculateHeuristicCost(t_origin, t_destination);

	while (open.size() > 0)
	{
		shared_ptr<CACell> lowest = open.front();

		if (lowest == t_destination) return;

		for (shared_ptr<CACell> c : open)
		{
			if (c->path + c->heuristic < lowest->path + lowest->heuristic)
				lowest = c;
		}
		open.remove(lowest);
		closed.push_back(lowest);

		shared_ptr<vector<shared_ptr<CACell>>> neighbours = lowest->getVonNeighbours();
		for (shared_ptr<CACell> neighbour : *neighbours)
		{
			bool contains = false;
			for (shared_ptr<CACell> c : closed)
			{
				if (c == neighbour) continue;
			}
			int gCost = lowest->path + calculateHeuristicCost(lowest, t_destination);
			if (gCost < neighbour->path)
			{
				neighbour->heuristic = calculateHeuristicCost(neighbour, t_destination);
				neighbour->path = gCost;
				neighbour->previous = lowest;

				open.push_back(neighbour);
			}
		}
	}
	closed.clear();
	vector<shared_ptr<CACell>> list1;
	list1.push_back(t_destination);
	shared_ptr<CACell> current = t_destination;
	while (current != nullptr)
	{
		current = current->previous;
		list1.push_back(current);
	}
	for (shared_ptr<CACell> c : list1)
	{
		if (c != nullptr)
		{
			c->setCellState(CellState::Floor);
			c->setupColor();
		}
	}
}

void CA::connectCaverns()
{
	shared_ptr<vector<shared_ptr<CACell>>> largest = findLargestCavern();
	for (shared_ptr<vector<shared_ptr<CACell>>> cave : *m_caverns)
	{
		if (largest != cave)
		{
			int o = rand() % (cave->size());
			shared_ptr<CACell> origin = cave->at(o);
			int l = rand() % (largest->size() - 1);
			shared_ptr<CACell> destination = largest->at(l);
			astar(origin, destination);
		}
	}
}

int CA::calculateHeuristicCost(shared_ptr<CACell> t_from, shared_ptr<CACell> t_to)
{
	int x = abs(t_from->getPosition().x - t_to->getPosition().x);
	int y = abs(t_from->getPosition().y - t_to->getPosition().y);

	int remaining = abs(x - y);

	return remaining;
}

void CA::processQueue()
{
	while (m_queue.size() != 0)
	{
		if (m_queue.front()->cell->getCellState() == CellState::Floor && m_queue.front()->cell->getFillType() == -1)
		{
			floodFill(m_queue.front()->cell, m_queue.front()->fill, m_recursiveDepth);
			m_queue.pop();
		}
		else
		{
			m_queue.pop();
		}
	}
}

void CA::generateColorsForCaves(int t_max)
{
	for (int i = m_cavernCount; i <= t_max; i++)
	{
		m_colors->push_back(Color(rand() % 255, rand() % 255, rand() % 255));
	}
	m_cavernCount = t_max;
}
