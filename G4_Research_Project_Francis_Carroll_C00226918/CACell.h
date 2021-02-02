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
	CACell(Vector2f t_position, Vector2f t_size);
	~CACell();

	void render(shared_ptr<RenderWindow> t_window);
private:
	void setup();

	Vector2f m_position;
	Vector2f m_size;

	shared_ptr<RectangleShape> m_cell;
	shared_ptr<CellState> m_cellState;
};