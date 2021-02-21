#include "CA.h"

CA::CA(shared_ptr<CAData> t_caData) : 
	m_caData(t_caData),
	m_colors(make_shared<vector<Color>>()),
	m_cavernCount(0),
	m_caverns(make_shared<vector<shared_ptr<vector<shared_ptr<CACell>>>>>())
{
	m_caGrid = make_shared<CAGrid>(m_caData, m_caData->m_ca->m_caStartingPosition, m_caData->m_ca->m_caGridSize, m_caData->m_ca->m_cellCount);
	m_tempStates = make_shared<vector<CellState>>();
	m_iterations = m_caData->m_ca->m_iterations;
	FLOOR_TO_WALL_CONVERSION = m_caData->m_ca->m_floorToWallConversion;
	WALL_TO_FLOOR_CONVERSION = m_caData->m_ca->m_wallToFloorConversion;
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
		connectCaverns();
	}
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
	int temp = m_cavernCount;
	shared_ptr<vector<shared_ptr<CACell>>> grid = m_caGrid->getCells();
	for (shared_ptr<CACell> c : *grid)
	{
		if (c->getCellState() == CellState::Floor && c->getFillType() == -1)
		{
			m_caverns->push_back(make_shared<vector<shared_ptr<CACell>>>());
			floodFill(c, temp, 2500);
			temp++;
		}
	}

	for (int i = m_cavernCount; i <= temp; i++)
	{
		m_colors->push_back(Color(rand() % 255, rand() % 255, rand() % 255));
	}
	m_cavernCount = temp;

	shared_ptr<vector<shared_ptr<CACell>>> grid2 = m_caGrid->getCells();
	for (shared_ptr<CACell> c : *grid2)
	{
		if (c->getCellState() == CellState::Floor && c->getFillType() != -1)
		{
			c->setupFloodColor(m_colors);
		}
	}
	//connectCaverns();
}

void CA::floodFill(shared_ptr<CACell> t_cell, int t_fillID, int t_depth)
{
	if (t_depth == 0)
		return;
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

void CA::connectCaverns()
{
	shared_ptr<vector<shared_ptr<CACell>>> largest = findLargestCavern();
	for (shared_ptr<vector<shared_ptr<CACell>>> c : *m_caverns)
	{
		if (largest != c)
		{
			for (shared_ptr<CACell> cell : *c)
			{
				cell->setCellState(CellState::Wall);
				cell->setupColor();
			}
		}
	}
}
