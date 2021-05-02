#include "CACell.h"

CACell::CACell(int t_id, Vector2f t_position, Vector2f t_size) :
	m_cell(new RectangleShape()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(CellState(CellState::Floor)), 
	m_id(t_id),
	m_neighbours(new vector<CACell*>()),
	m_fillType(-1),
	m_marked(false),
	m_heuristic(100000),
	m_path(100000),
	m_previous(nullptr),
	m_processed(false)
{
	setup();
	getColor();
}

CACell::CACell(int t_id, Vector2f t_position, Vector2f t_size, CellState t_state) :
	m_cell(new RectangleShape()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(CellState(t_state)),
	m_id(t_id),
	m_neighbours(new vector<CACell*>()),
	m_fillType(-1),
	m_marked(false),
	m_heuristic(100000),
	m_path(100000),
	m_previous(nullptr),
	m_processed(false)
{
	setup();
	getColor();
}

CACell::~CACell()
{
	delete m_cell;
	delete m_neighbours;
}

void CACell::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(*m_cell);
}

void CACell::addNeighbour(CACell* t_cell)
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

vector<CACell*>* CACell::getNeighbours()
{
	return m_neighbours;
}

int CACell::getFillType()
{
	return m_fillType;
}

Vector2f CACell::getPosition()
{
	return m_position;
}

Vector2f CACell::getSize()
{
	return m_size;
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

void CACell::getColor()
{
	if (m_cellState == CellState::Floor)
		m_cell->setFillColor(Color::White);
	else
		m_cell->setFillColor(Color::Black);
}

void CACell::setupFloodColor(vector<Color>* t_colors)
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
