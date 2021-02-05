#include "CACell.h"

CACell::CACell(int t_id, Vector2f t_position, Vector2f t_size) :
	m_cell(make_shared<RectangleShape>()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(CellState(CellState::None)), 
	m_id(t_id),
	m_neighbours(make_shared<vector<shared_ptr<CACell>>>())
{
	setup();
	setupColor();
}

CACell::CACell(int t_id, Vector2f t_position, Vector2f t_size, CellState t_state) :
	m_cell(make_shared<RectangleShape>()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(CellState(t_state)),
	m_id(t_id),
	m_neighbours(make_shared<vector<shared_ptr<CACell>>>())
{
	setup();
	setupColor();
}

CACell::~CACell()
{
}

void CACell::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(*m_cell);
}

void CACell::addNeighbour(shared_ptr<CACell> t_cell)
{
	m_neighbours->push_back(t_cell);
}

void CACell::setCellState(CellState t_state)
{
	m_cellState = t_state;
}

int CACell::getID()
{
	return m_id;
}

CellState CACell::getCellState()
{
	return m_cellState;
}

shared_ptr<vector<shared_ptr<CACell>>> CACell::getNeighbours()
{
	return m_neighbours;
}

void CACell::setup()
{
	m_cell->setPosition(m_position);
	m_cell->setSize(m_size);
}

void CACell::setupColor()
{
	if(m_cellState == CellState::None)
		m_cell->setFillColor(Color::White);
	else
		m_cell->setFillColor(Color::Green);
}
