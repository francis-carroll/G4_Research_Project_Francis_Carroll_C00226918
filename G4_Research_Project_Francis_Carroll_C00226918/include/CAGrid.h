#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CACell.h>
#include <LevelLoader.h>

using namespace std;
using namespace sf;

/// <summary>
/// The grid that contains all the nodes in the grid
/// </summary>
class CAGrid
{
public:
	CAGrid(CAData* t_caData, Vector2f t_position, Vector2f t_size, Vector2f t_gridRowColCount);
	~CAGrid();

	void render(shared_ptr<RenderWindow> t_window);

	int getIndex(int t_row, int t_col);
	Vector2i getRowCol(int t_index);
	vector<CACell*>* getCells();
private:
	void splitGrid();
	void calculateMooreNeighbours();
	void calculateVonNeumannNeighbours();

	Vector2f m_position;
	Vector2f m_size;
	Vector2f m_cellCount;

	float m_chanceToBecomeWall;

	vector<CACell*>* m_cells;
	CAData* m_caData;
	vector<int>* m_bestDirection;
};

