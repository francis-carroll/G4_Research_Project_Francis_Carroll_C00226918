#pragma once

#include <SFML/Graphics.hpp>

#include <Globals.h>
#include <CAGrid.h>
#include <LevelLoader.h>
#include <Windows.h>
#include <queue>
#include <chrono>
#include <list>

using namespace std;
using namespace sf;

/// <summary>
/// struct that is used to make the recursive flood fill iterative
/// </summary>
struct CAPostProcess
{
public: 
	CAPostProcess(CACell* t_cell, int t_fill) : cell(t_cell), fill(t_fill) {}
	~CAPostProcess() {};
	CACell* cell;
	int fill;
};

class CA
{
public:
	CA(CAData* t_caData);
	~CA();

	void render(shared_ptr<RenderWindow> t_window);
	void keyPresses(Event& t_event);
private:
	void loadConstants();
	void initialIterate();
	void iterate(int t_x = 0, int t_y = 0, int t_width = INT32_MAX, int t_height = INT32_MAX);
	CellState applyRules(CACell* t_current);
	void processCA();
	void floodFill(CACell* t_cell, int t_fillID, int t_depth);
	vector<CACell*>* findLargestCavern();
	void removeSmallCaverns();
	vector<CACell*>* astar(CACell* t_origin, CACell* t_destination);
	void connectCaverns();
	float calculateHeuristicCost(CACell* t_from, CACell* t_to);
	void processQueue();
	void generateColorsForCaves(int t_max);
	void setupColors(bool t_bool);
	void resetGrid();
	vector<CACell*>* constructPath(CACell* t_goal);
	void setup();
	void iterateInDirection();

	int WALL_TO_FLOOR_CONVERSION = 0;
	int FLOOR_TO_WALL_CONVERSION = 0;
	int m_iterations = 0;
	int m_cavernCount = 0;
	int m_recursiveDepth = 0;
	int m_maxCaveSize = 0;
	Vector2f m_asyncStart = Vector2f(0.0f,0.0f);
	Vector2f m_asyncSize = Vector2f(0.0f, 0.0f);

	bool m_renderCavern;
	bool m_toggleAsyncBorder;
	RectangleShape m_outline;

	vector<CellState>* m_tempStates;
	CAGrid* m_caGrid;
	CAData* m_caData;
	vector<Color>* m_colors;
	vector<vector<CACell*>*>* m_caverns;
	list<CACell*>* m_path;
	queue<CAPostProcess*>* m_queue;
};

