#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>

using namespace std;
using namespace sf;

/// <summary>
/// The current state of a node at any one stage
/// </summary>
enum class CellState
{
	Floor, 
	Wall
};

/// <summary>
/// A singular cell
/// </summary>
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

	float m_path;
	float m_heuristic;
	CACell* m_previous;
	bool m_marked;
	bool m_processed;
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

/// <summary>
/// Overload struct for the A* algorithm.
/// </summary>
struct CompareNodes
{
	float operator()(CACell* const node1, CACell* const node2)
	{
		return (node1->m_path + node1->m_heuristic) > (node2->m_path + node2->m_heuristic);
	}
};