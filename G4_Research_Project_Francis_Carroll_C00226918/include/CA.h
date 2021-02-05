#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CAGrid.h>

using namespace std;
using namespace sf;

class CA
{
public:
	CA(int t_iterations = 0);
	~CA();

	void render(shared_ptr<RenderWindow> t_window);
	void keyPresses(Event& t_event);
private:
	void initialIterate();
	void iterate();
	CellState applyRules(shared_ptr<CACell> t_current);

	int WALL_TO_FLOOR_CONVERSION = 3;
	int FLOOR_TO_WALL_CONVERSION = 4;
	int m_iterations;

	shared_ptr<vector<CellState>> m_tempStates;
	shared_ptr<CAGrid> m_caGrid;
};

