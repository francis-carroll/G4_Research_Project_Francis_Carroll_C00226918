#include "CACell.h"

CACell::CACell(int t_id, Vector2f t_position, Vector2f t_size) :
	m_cell(make_shared<RectangleShape>()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(CellState(CellState::Floor)), 
	m_id(t_id),
	m_mooreNeighbours(make_shared<vector<shared_ptr<CACell>>>()),
	m_vonNeumannNeighbours(make_shared<vector<shared_ptr<CACell>>>()),
	m_fillType(-1),
	m_marked(false)
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
	m_mooreNeighbours(make_shared<vector<shared_ptr<CACell>>>()),
	m_vonNeumannNeighbours(make_shared<vector<shared_ptr<CACell>>>()),
	m_fillType(-1),
	m_marked(false),
	path(INT32_MAX),
	heuristic(INT32_MAX)
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
	m_mooreNeighbours->push_back(t_cell);
}

void CACell::addVonNeighbour(shared_ptr<CACell> t_cell)
{
	m_vonNeumannNeighbours->push_back(t_cell);
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
	return m_mooreNeighbours;
}

shared_ptr<vector<shared_ptr<CACell>>> CACell::getVonNeighbours()
{
	return m_vonNeumannNeighbours;
}

int CACell::getFillType()
{
	return m_fillType;
}

Vector2f CACell::getPosition()
{
	return m_position;
}

bool CACell::getMarked()
{
	return m_marked;
}

void CACell::setup()
{
	m_cell->setPosition(m_position);
	m_cell->setSize(m_size);
}

void CACell::setupColor()
{
	if(m_cellState == CellState::Floor)
		m_cell->setFillColor(Color::White);
	else
		m_cell->setFillColor(Color::Black);
}

void CACell::setupFloodColor(shared_ptr<vector<Color>> t_colors)
{
	m_cell->setFillColor(t_colors->at(m_fillType));
}

void CACell::setFillType(int t_fillType)
{
	m_fillType = t_fillType;
}

void CACell::setMarked(bool t_marked)
{
	m_marked = t_marked;
}
