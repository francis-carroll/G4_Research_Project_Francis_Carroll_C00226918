#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <LevelLoader.h>
#include <BSPFloor.h>
#include <chrono>
#include <Key.h>
#include <AnalyticDataDisplay.h>

using namespace std;
using namespace sf;

class BSPScreen
{
public:
	BSPScreen();
	~BSPScreen();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
private:
	void instanciateBSP(string& t_message, string t_filename, string t_size);

	shared_ptr<BSPFloor> m_bspFloor;
	shared_ptr<Key> m_key;
	shared_ptr<AnalyticDataDisplay> m_dataDisplay;
	bool m_analytics;
};