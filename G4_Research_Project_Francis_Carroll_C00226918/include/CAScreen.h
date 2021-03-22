#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <CA.h>
#include <LevelLoader.h>
#include <chrono>
#include <Key.h>
#include <AnalyticDataDisplay.h>
#include <string>

using namespace std;
using namespace sf;

class CAScreen
{
public:
	CAScreen();
	~CAScreen();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
private:
	void instanciateCA(string& t_message, string t_filename, string t_size);

	shared_ptr<CA> m_caGrid;
	shared_ptr<Key> m_key;
	shared_ptr<AnalyticDataDisplay> m_dataDisplay;
	bool m_analytics;
};