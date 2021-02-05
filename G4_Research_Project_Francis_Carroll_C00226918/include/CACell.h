#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>

using namespace std;
using namespace sf;

enum class CellState
{
	None, 
	Wall
};

class CACell
{
public:
	CACell(int t_id, Vector2f t_position, Vector2f t_size);
	CACell(int t_id, Vector2f t_position, Vector2f t_size, CellState t_state);
	~CACell();

	void render(shared_ptr<RenderWindow> t_window);

	void addNeighbour(shared_ptr<CACell> t_cell);

	void setCellState(CellState t_state);
	void setupColor();

	int getID();
	CellState getCellState();
	shared_ptr<vector<shared_ptr<CACell>>> getNeighbours();
private:
	void setup();

	Vector2f m_position;
	Vector2f m_size;
	int m_id;

	shared_ptr<RectangleShape> m_cell;
	CellState m_cellState;
	shared_ptr<vector<shared_ptr<CACell>>> m_neighbours;
};