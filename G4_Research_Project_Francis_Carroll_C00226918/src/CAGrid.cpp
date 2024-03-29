#include "CAGrid.h"

CAGrid::CAGrid(CAData* t_caData, Vector2f t_position, Vector2f t_size, Vector2f t_gridRowColCount) :
	m_cells(new vector<CACell*>()),
	m_position(t_position),
	m_size(t_size),
	m_cellCount(t_gridRowColCount),
	m_caData(t_caData),
	m_bestDirection(new vector<int>({ 3,5,1,7 }))
{
	m_chanceToBecomeWall = m_caData->m_ca->m_chanceToBecomeWall;
	splitGrid();
	calculateMooreNeighbours();
	//calculateVonNeumannNeighbours();
}

CAGrid::~CAGrid()
{
	for (CACell* c : *m_cells)
	{
		delete c;
	}
	delete m_cells;
	delete m_bestDirection;
}

void CAGrid::render(shared_ptr<RenderWindow> t_window)
{
	for (CACell* cell : *m_cells)
	{
		cell->render(t_window);
	}
}

int CAGrid::getIndex(int t_row, int t_col)
{
	return int(t_col + (t_row * m_cellCount.y));
}

Vector2i CAGrid::getRowCol(int t_index)
{
	return Vector2i(t_index / int(m_cellCount.y), t_index % int(m_cellCount.y));
}

vector<CACell*>* CAGrid::getCells()
{
	return m_cells;
}

void CAGrid::splitGrid()
{
	float row = (m_size.y - m_position.y) / m_cellCount.y;
	float col = (m_size.x - m_position.x) / m_cellCount.x;

	for (int i = 0; i < m_cellCount.x; i++)
	{
		for (int j = 0; j < m_cellCount.y; j++)
		{
			if(randomFloat(0, 1) < m_chanceToBecomeWall)
				m_cells->push_back(new CACell(getIndex(i, j) , Vector2f((i * col) + m_position.x, (j * row) + m_position.y), Vector2f(col, row), CellState::Wall));
			else
				m_cells->push_back(new CACell(getIndex(i, j), Vector2f((i * col) + m_position.x, (j * row) + m_position.y), Vector2f(col, row), CellState::Floor));
		}
	}
}

void CAGrid::calculateMooreNeighbours()
{
	for (CACell* cell : *m_cells) {
		//for each direction of the node
		for (int d = 0; d < 9; d++) {
			//execpt 4, the current node
			if (d == 4) { continue; }

			Vector2i temp = getRowCol(cell->getID());
			int neighbourRow = temp.x + ((d % 3) - 1); //calculates neighbour rows
			int neighbourCol = temp.y + ((d / 3) - 1); //calculates neighbour columns

			//if the neighbor row or col is outside the boundry, skip
			if (neighbourRow >= 0 && neighbourRow < m_cellCount.x &&
				neighbourCol >= 0 && neighbourCol < m_cellCount.y)
			{
				int nodeIndex = getIndex(neighbourRow, neighbourCol);
				//add the neighbour
				cell->addNeighbour(m_cells->at(nodeIndex));
			}
		}
	}
}

void CAGrid::calculateVonNeumannNeighbours()
{
	for (CACell* cell : *m_cells) {
		//for each direction of the node
		for (int d : *m_bestDirection) {

			Vector2i temp = getRowCol(cell->getID());
			int neighbourRow = temp.x + ((d % 3) - 1); //calculates neighbour rows
			int neighbourCol = temp.y + ((d / 3) - 1); //calculates neighbour columns

			//if the neighbor row or col is outside the boundry, skip
			if (neighbourRow >= 0 && neighbourRow < m_cellCount.x &&
				neighbourCol >= 0 && neighbourCol < m_cellCount.y)
			{
				int nodeIndex = getIndex(neighbourRow, neighbourCol);
				//add the neighbour
				cell->addNeighbour(m_cells->at(nodeIndex));
			}
		}
	}
}
