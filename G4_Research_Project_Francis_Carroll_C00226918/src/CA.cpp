#include "CA.h"

CA::CA(int t_iterations)
{
	m_caGrid = make_shared<CAGrid>(Vector2f(10.0f, 10.0f), Vector2f(800.0f, 800.f), Vector2f(500.0f, 500.0f));
	m_tempStates = make_shared<vector<CellState>>();
	m_iterations = t_iterations;
	iterate();
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
		if (cell->getCellState() == CellState::None)
		{
			floor++;
		}
		else if (cell->getCellState() == CellState::Wall)
		{
			wall++;
		}
	}

	if (wall < WALL_TO_FLOOR_CONVERSION && t_current->getCellState() == CellState::Wall) return CellState::None;
	else if (wall > FLOOR_TO_WALL_CONVERSION && t_current->getCellState() == CellState::None) return CellState::Wall;
	else return t_current->getCellState();
}
