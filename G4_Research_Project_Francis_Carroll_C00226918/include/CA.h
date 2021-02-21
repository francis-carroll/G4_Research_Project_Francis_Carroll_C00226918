#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CAGrid.h>
#include <LevelLoader.h>
#include <Windows.h>

using namespace std;
using namespace sf;

class CA
{
public:
	CA(shared_ptr<CAData> t_caData);
	~CA();

	void render(shared_ptr<RenderWindow> t_window);
	void keyPresses(Event& t_event);
private:
	void initialIterate();
	void iterate();
	CellState applyRules(shared_ptr<CACell> t_current);
	void processCA();
	void floodFill(shared_ptr<CACell> t_cell, int t_fillID, int t_depth);
	shared_ptr<vector<shared_ptr<CACell>>> findLargestCavern();
	void connectCaverns();

	int WALL_TO_FLOOR_CONVERSION = 3;
	int FLOOR_TO_WALL_CONVERSION = 4;
	int m_iterations;
	int m_cavernCount;

	shared_ptr<vector<CellState>> m_tempStates;
	shared_ptr<CAGrid> m_caGrid;
	shared_ptr<CAData> m_caData;
	shared_ptr<vector<Color>> m_colors;
	shared_ptr<vector<shared_ptr<vector<shared_ptr<CACell>>>>> m_caverns;
};

