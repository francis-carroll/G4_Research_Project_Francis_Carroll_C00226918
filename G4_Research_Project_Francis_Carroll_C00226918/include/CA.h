#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CAGrid.h>
#include <LevelLoader.h>
#include <Windows.h>
#include <queue>
#include <chrono>

using namespace std;
using namespace sf;

/// <summary>
/// struct that is used to make the recursive flood fill iterative
/// </summary>
struct CAPostProcess
{
public: 
	CAPostProcess(shared_ptr<CACell> t_cell, int t_fill) : cell(t_cell), fill(t_fill) {}
	shared_ptr<CACell> cell;
	int fill;
};

class CA
{
public:
	CA(shared_ptr<CAData> t_caData);
	~CA();

	void render(shared_ptr<RenderWindow> t_window);
	void keyPresses(Event& t_event);
private:
	void loadConstants();
	void initialIterate();
	void iterate();
	CellState applyRules(shared_ptr<CACell> t_current);
	void processCA();
	void floodFill(shared_ptr<CACell> t_cell, int t_fillID, int t_depth);
	shared_ptr<vector<shared_ptr<CACell>>> findLargestCavern();
	void removeSmallCaverns();
	void astar(shared_ptr<CACell> t_origin, shared_ptr<CACell> t_destination);
	void connectCaverns();
	int calculateHeuristicCost(shared_ptr<CACell> t_from, shared_ptr<CACell> t_to);
	void processQueue();
	void generateColorsForCaves(int t_max);
	void setupColors(bool t_bool);
	void resetGrid();

	int WALL_TO_FLOOR_CONVERSION;
	int FLOOR_TO_WALL_CONVERSION;
	int m_iterations;
	int m_cavernCount;
	int m_recursiveDepth;
	int m_maxCaveSize;

	bool m_renderCavern;

	shared_ptr<vector<CellState>> m_tempStates;
	shared_ptr<CAGrid> m_caGrid;
	shared_ptr<CAData> m_caData;
	shared_ptr<vector<Color>> m_colors;
	shared_ptr<vector<shared_ptr<vector<shared_ptr<CACell>>>>> m_caverns;
	list<shared_ptr<CACell>> m_path;
	queue<shared_ptr<CAPostProcess>> m_queue;
};

