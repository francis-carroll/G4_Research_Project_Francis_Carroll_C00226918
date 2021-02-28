#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>

using namespace std;
using namespace sf;

enum class CellState
{
	Floor, 
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
	void addVonNeighbour(shared_ptr<CACell> t_cell);

	void setCellState(CellState t_state);
	void setupColor();
	void setupFloodColor(shared_ptr<vector<Color>> t_colors);
	void setFillType(int t_fillType);
	void setMarked(bool t_marked);

	int getID();
	CellState getCellState();
	shared_ptr<vector<shared_ptr<CACell>>> getNeighbours();
	shared_ptr<vector<shared_ptr<CACell>>> getVonNeighbours();
	int getFillType();
	Vector2f getPosition();
	bool getMarked();

	float path;
	float heuristic;
	shared_ptr<CACell> previous;
private:
	void setup();

	Vector2f m_position;
	Vector2f m_size;
	int m_id;
	int m_fillType;
	bool m_marked;

	shared_ptr<RectangleShape> m_cell;
	CellState m_cellState;
	shared_ptr<vector<shared_ptr<CACell>>> m_mooreNeighbours;
	shared_ptr<vector<shared_ptr<CACell>>> m_vonNeumannNeighbours;
};