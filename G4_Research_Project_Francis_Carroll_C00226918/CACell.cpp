#include "CACell.h"

CACell::CACell(Vector2f t_position, Vector2f t_size) : 
	m_cell(make_shared<RectangleShape>()),
	m_position(t_position),
	m_size(t_size),
	m_cellState(make_shared<CellState>(CellState::None))
{
	setup();
}

CACell::~CACell()
{
}

void CACell::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(*m_cell);
}

void CACell::setup()
{
	m_cell->setPosition(m_position);
	m_cell->setSize(m_size);
	m_cell->setFillColor(Color::White);
	m_cell->setOutlineColor(Color::Black);
	m_cell->setOutlineThickness(1.0f);
}
