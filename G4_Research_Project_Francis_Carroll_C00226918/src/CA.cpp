#include "CA.h"

CA::CA(CAData* t_caData) :
	m_caData(t_caData),
	m_colors(new vector<Color>()),
	m_cavernCount(0),
	m_caverns(new vector<vector<CACell*>*>()),
	m_tempStates(new vector<CellState>()),
	m_path(new list<CACell*>()),
	m_queue(new queue<CAPostProcess*>()),
	m_renderCavern(false)
{
	loadConstants();
	setup();
	initialIterate();
	auto start = chrono::steady_clock::now();
	removeSmallCaverns();
	//connectCaverns();
	//processCA();
	auto end = chrono::steady_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	s_ca_runtime_post = seconds.count() / 1000.0f;
}

CA::~CA()
{
	delete m_caData;
	delete m_colors;
	delete m_tempStates;
	delete m_path;
	delete m_queue;
	for (vector<CACell*>* cave : *m_caverns)
	{
		delete cave;
	}
	delete m_caverns;
	delete m_caGrid;
}

void CA::render(shared_ptr<RenderWindow> t_window)
{
	m_caGrid->render(t_window);
	t_window->draw(m_outline);
}

void CA::keyPresses(Event& t_event)
{
	if (t_event.key.code == Keyboard::R)
	{
		toggleBool(m_renderCavern);
		setupColors(m_renderCavern);
	}

	if (t_event.key.code == Keyboard::Left)
	{
		if (m_asyncStart.x - m_asyncSize.x < 0)
			m_asyncStart = Vector2f(0, m_asyncStart.y);
		else
			m_asyncStart += Vector2f(-m_asyncSize.x, 0.0f);

		m_outline.setPosition(m_caData->m_ca->m_caStartingPosition + Vector2f(m_caGrid->getCells()->at(0)->getSize().x * (m_asyncStart.x), m_caGrid->getCells()->at(0)->getSize().y * (m_asyncStart.y)));

		iterateInDirection();
	}
	else if (t_event.key.code == Keyboard::Up)
	{
		if (m_asyncStart.y - m_asyncSize.y < 0)
			m_asyncStart = Vector2f(m_asyncStart.x, 0);
		else
			m_asyncStart += Vector2f(0.0f, -m_asyncSize.y);

		iterateInDirection();
	}
	else if (t_event.key.code == Keyboard::Right)
	{
		if (m_asyncStart.x + m_asyncSize.x > m_caData->m_ca->m_cellCount.x - m_asyncSize.x)
			m_asyncStart = Vector2f(m_caData->m_ca->m_cellCount.x - m_asyncSize.x, m_asyncStart.y);
		else
			m_asyncStart += Vector2f(m_asyncSize.x, 0.0f);

		iterateInDirection();
	}
	else if (t_event.key.code == Keyboard::Down)
	{
		if (m_asyncStart.y + m_asyncSize.y > m_caData->m_ca->m_cellCount.y - m_asyncSize.y)
			m_asyncStart = Vector2f(m_asyncStart.y - m_asyncSize.y, m_caData->m_ca->m_cellCount.y);
		else
			m_asyncStart += Vector2f(0.0f, m_asyncSize.y);

		iterateInDirection();
	}
}

void CA::loadConstants()
{
	m_caGrid = new CAGrid(m_caData, m_caData->m_ca->m_caStartingPosition, m_caData->m_ca->m_caGridSize, m_caData->m_ca->m_cellCount);
	m_iterations = m_caData->m_ca->m_iterations;
	m_maxCaveSize = m_caData->m_ca->m_maxCaveSize;
	m_recursiveDepth = m_caData->m_ca->m_recursiveDepth;
	FLOOR_TO_WALL_CONVERSION = m_caData->m_ca->m_floorToWallConversion;
	WALL_TO_FLOOR_CONVERSION = m_caData->m_ca->m_wallToFloorConversion;
	m_asyncSize = m_caData->m_ca->m_asyncSize;
	m_asyncStart = m_caData->m_ca->m_asyncPosition;
}

void CA::initialIterate()
{
	iterateInDirection();
}

void CA::iterate(int t_x, int t_y, int t_width, int t_height)
{
	vector<CACell*>* grid = m_caGrid->getCells();
	for (CACell* c : *grid)
	{
		Vector2i rowCol = m_caGrid->getRowCol(c->getID());
		if(rowCol.x >= t_x && rowCol.x <= t_width &&
			rowCol.y >= t_y && rowCol.y <= t_height)
			m_tempStates->push_back(applyRules(c));
		else 
			m_tempStates->push_back(c->getCellState());
	}

	for (CACell* c : *grid)
	{
		c->setCellState(m_tempStates->at(c->getID()));
		c->getColor();
	}
	m_tempStates->clear();
}

CellState CA::applyRules(CACell* t_current)
{
	int wall = 0;
	int floor = 0;
	vector<CACell*>* neighbours = t_current->getNeighbours();
	for (CACell* cell : *neighbours)
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
	t_current->m_processed = true;
	if (wall < WALL_TO_FLOOR_CONVERSION && t_current->getCellState() == CellState::Wall) return CellState::Floor;
	else if (wall > FLOOR_TO_WALL_CONVERSION && t_current->getCellState() == CellState::Floor) return CellState::Wall;
	else return t_current->getCellState();
}

void CA::processCA()
{
	m_caverns->clear();
	m_cavernCount = 0;
	int temp = m_cavernCount;
	vector<CACell*>* grid1 = m_caGrid->getCells();
	for (CACell* c : *grid1)
	{
		c->setFillType(-1);
	}

	vector<CACell*>* grid = m_caGrid->getCells();
	for (CACell* c : *grid)
	{
		if (c->getCellState() == CellState::Floor && c->getFillType() == -1 && c->m_processed)
		{
			m_caverns->push_back(new vector<CACell*>());
			floodFill(c, temp, m_recursiveDepth);
			temp++;
		}

		processQueue();
	}

	//generates colors for cavern
	generateColorsForCaves(temp);
}

void CA::floodFill(CACell* t_cell, int t_fillID, int t_depth)
{
	if (t_depth == 0)
	{
		m_queue->push(new CAPostProcess(t_cell, t_fillID));
		return;
	}

	if (t_cell->getCellState() != CellState::Floor || t_cell->getFillType() != -1 || !t_cell->m_processed)
		return;

	t_cell->setFillType(t_fillID);
	m_caverns->at(t_fillID)->push_back(t_cell);

	vector<CACell*>* neighbours = t_cell->getNeighbours();
	for (CACell* c : *neighbours)
	{
		floodFill(c, t_fillID, t_depth - 1);
	}
}

vector<CACell*>* CA::findLargestCavern()
{
	vector<CACell*>* largest = new vector<CACell*>();
	int maximum = 0;

	for (vector<CACell*>* cave : *m_caverns)
	{
		if (maximum < (int)cave->size())
		{
			maximum = cave->size();
			largest = cave;
		}
	}
	return largest;
}

void CA::removeSmallCaverns()
{
	vector<vector<CACell*>*>* temp = new vector<vector<CACell*>*>();
	vector<CACell*>* largest = findLargestCavern();
	for (vector<CACell*>* c : *m_caverns)
	{
		if (largest != c && (int)c->size() < m_maxCaveSize)
		{
			for (CACell* cell : *c)
			{
				cell->setCellState(CellState::Wall);
				cell->getColor();
			}
			temp->push_back(c);
		}
	}

	//removes all the caves that have been turned into walls
	for (vector<CACell*>* c : *temp)
	{
		m_caverns->erase(std::remove_if(m_caverns->begin(), m_caverns->end(), [&](vector<CACell*>* t_v) { if (t_v == c) return true; else return false; }), m_caverns->end());
	}
	delete temp;
}

vector<CACell*>* CA::astar(CACell* t_origin, CACell* t_destination)
{
	priority_queue<CACell*, vector<CACell*>, CompareNodes>* open = new priority_queue<CACell*, vector<CACell*>, CompareNodes>();
	queue<CACell*>* closed = new queue<CACell*>();

	t_origin->path = 0;
	t_origin->heuristic = (float)calculateHeuristicCost(t_origin, t_destination);
	open->push(t_origin);


	while (open->size() > 0)
	{
		CACell* current = open->top();

		if (current == t_destination)
		{
			delete closed;
			delete open;
			return constructPath(t_destination);
		}

		open->pop();
		closed->push(current);

		vector<CACell*>* neighbours = current->getNeighbours();
		for (CACell* neighbour : *neighbours)
		{
			//if (neighbour->getCellState() == CellState::Wall) continue;

			float gCost = current->path + 1;
			if (gCost < neighbour->path)
			{
				neighbour->heuristic = (float)calculateHeuristicCost(neighbour, t_destination);
				neighbour->path = gCost;
				neighbour->previous = current;
				if (!neighbour->m_marked)
				{
					neighbour->m_marked = true;
					open->push(neighbour);
				}
			}
		}
	}
	delete closed;
	delete open;
	return nullptr;
}

void CA::connectCaverns()
{
	vector<CACell*>* largest = findLargestCavern();
	for (vector<CACell*>* cave : *m_caverns)
	{
		if (largest != cave)
		{
			int o = rand() % (cave->size() - 1);
			CACell* origin = cave->at(o);
			int l = rand() % (largest->size() - 1);
			CACell* destination = largest->at(l);
			astar(origin, destination);
		}
	}
}

float CA::calculateHeuristicCost(CACell* t_from, CACell* t_to)
{
	return abs(directDistance(t_from->getPosition(), t_to->getPosition()));
}

void CA::processQueue()
{
	while (m_queue->size() != 0)
	{
		if (m_queue->front()->cell->getCellState() == CellState::Floor && m_queue->front()->cell->getFillType() == -1 && m_queue->front()->cell->m_processed)
		{
			floodFill(m_queue->front()->cell, m_queue->front()->fill, m_recursiveDepth);
			delete m_queue->front();
			m_queue->pop();
		}
		else
		{
			delete m_queue->front();
			m_queue->pop();
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

void CA::setupColors(bool t_bool)
{
	if (t_bool)
	{
		//sets the caves colors
		vector<CACell*>* grid = m_caGrid->getCells();
		for (CACell* c : *grid)
		{
			if (c->getCellState() == CellState::Floor && c->getFillType() != -1)
			{
				c->setupFloodColor(m_colors);
			}
		}
	}
	else
	{
		vector<CACell*>* grid2 = m_caGrid->getCells();
		for (CACell* c : *grid2)
		{
			if (c->getCellState() == CellState::Floor)
			{
				c->getColor();
			}
		}
	}
}

void CA::resetGrid()
{
	setupColors(false);
	m_caverns->clear();
	vector<CACell*>* grid = m_caGrid->getCells();
	for (CACell* c : *grid)
	{
		if (c->getCellState() == CellState::Floor)
		{
			c->setFillType(-1);
		}
	}
}

vector<CACell*>* CA::constructPath(CACell* t_goal)
{
	vector<CACell*>* path = new vector<CACell*>();
	CACell* current = t_goal->previous;

	while (current->previous != nullptr)
	{
		path->push_back(current);
		if (current->getCellState() == CellState::Wall)
			current->setCellState(CellState::Floor);
		current = current->previous;
	}
	setupColors(false);
	return path;
}

void CA::setup()
{
	m_outline.setPosition(m_caData->m_ca->m_caStartingPosition + Vector2f(m_caGrid->getCells()->at(0)->getSize().x * (m_asyncStart.x), m_caGrid->getCells()->at(0)->getSize().y * (m_asyncStart.y)));
	m_outline.setSize(Vector2f(m_caGrid->getCells()->at(0)->getSize().x * m_asyncSize.x, m_caGrid->getCells()->at(0)->getSize().y * m_asyncSize.y));
	m_outline.setOutlineThickness(2.0f);
	m_outline.setOutlineColor(Color::Red);
	m_outline.setFillColor(Color(0,0,0,0));
}

void CA::iterateInDirection()
{
	m_outline.setPosition(m_caData->m_ca->m_caStartingPosition + Vector2f(m_caGrid->getCells()->at(0)->getSize().x * (m_asyncStart.x), m_caGrid->getCells()->at(0)->getSize().y * (m_asyncStart.y)));

	for (int i = 0; i < m_iterations; i++)
	{
		//iterate(m_asyncStart.x - (m_asyncSize.x / 2.0f), m_asyncStart.y - (m_asyncSize.y / 2.0f), m_asyncStart.x + m_asyncSize.x + (m_asyncSize.x / 2.0f), m_asyncStart.y + m_asyncSize.y + (m_asyncSize.y / 2.0f));
		iterate(m_asyncStart.x, m_asyncStart.y, m_asyncStart.x + m_asyncSize.x, m_asyncStart.y + m_asyncSize.y);
	}
	processCA();
}
