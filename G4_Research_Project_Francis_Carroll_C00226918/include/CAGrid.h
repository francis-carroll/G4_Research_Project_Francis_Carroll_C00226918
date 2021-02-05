#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CACell.h>

using namespace std;
using namespace sf;

class CAGrid
{
public:
	CAGrid(Vector2f t_position, Vector2f t_size, Vector2f t_gridRowColCount);
	~CAGrid();

	void render(shared_ptr<RenderWindow> t_window);

	CellState calculateState(int t_index);

	int getIndex(int t_row, int t_col);
	Vector2i getRowCol(int t_index);
	shared_ptr<vector<shared_ptr<CACell>>> getCells();
private:
	void splitGrid();
	void calculateNeighbours();

	Vector2f m_position;
	Vector2f m_size;
	Vector2f m_cellCount;

	float m_chanceToBecomeWall;

	shared_ptr<vector<shared_ptr<CACell>>> m_cells;
};

