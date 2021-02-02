#include "CAGrid.h"

CAGrid::CAGrid(Vector2f t_position, Vector2f t_size, Vector2f t_gridRowColCount) :
	m_cells(make_shared<vector<shared_ptr<CACell>>>()),
	m_position(t_position),
	m_size(t_size),
	m_cellCount(t_gridRowColCount),
	m_chanceToBecomeWall(0.45f)
{
	splitGrid();
}

CAGrid::~CAGrid()
{
}

void CAGrid::render(shared_ptr<RenderWindow> t_window)
{
	for (shared_ptr<CACell> cell : *m_cells)
	{
		cell->render(t_window);
	}
}

void CAGrid::splitGrid()
{
	float col = (m_size.x - m_position.x) / m_cellCount.x;
	float row = (m_size.y - m_position.y) / m_cellCount.y;

	for (int i = 0; i < m_cellCount.x; i++)
	{
		for (int j = 0; j < m_cellCount.y; j++)
		{
			if(randomFloat(0, 1) < m_chanceToBecomeWall)
				m_cells->push_back(make_shared<CACell>(Vector2f((i * row) + m_position.x, (j * col) + m_position.y), Vector2f(row, col), CellState::Wall));
			else
				m_cells->push_back(make_shared<CACell>(Vector2f((i * row) + m_position.x, (j * col) + m_position.y), Vector2f(row, col), CellState::None));
		}
	}
}
