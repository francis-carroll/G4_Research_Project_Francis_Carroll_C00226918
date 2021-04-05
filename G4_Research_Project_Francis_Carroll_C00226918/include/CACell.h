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
	CACell(int t_id = 0, Vector2f t_position = Vector2f(0.0f,0.0f), Vector2f t_size = Vector2f(0.0f,0.0f));
	CACell(int t_id, Vector2f t_position, Vector2f t_size, CellState t_state);
	~CACell();

	void render(shared_ptr<RenderWindow> t_window);

	void addNeighbour(CACell* t_cell);

	void setCellState(CellState t_state);
	void getColor();
	void setupFloodColor(vector<Color>* t_colors);
	void setFillType(int t_fillType);
	void setMarked(bool t_marked);

	int getID();
	CellState getCellState();
	vector<CACell*>* getNeighbours();
	int getFillType();
	Vector2f getPosition();
	Vector2f getSize();
	bool getMarked();

	float path;
	float heuristic;
	CACell* previous;
	bool m_marked;
private:
	void setup();

	Vector2f m_position;
	Vector2f m_size;
	int m_id;
	int m_fillType;

	RectangleShape* m_cell;
	CellState m_cellState;
	vector<CACell*>* m_neighbours;
};

struct CompareNodes
{
	float operator()(CACell* const node1, CACell* const node2)
	{
		return (node1->path + node1->heuristic) > (node2->path + node2->heuristic);
	}
};