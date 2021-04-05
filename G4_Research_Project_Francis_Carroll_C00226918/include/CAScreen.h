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
	void initScene();

	CA* m_caGrid;
private:
	void instanciateCA(string& t_message, string t_filename, string t_size);

	Key* m_key;
	AnalyticDataDisplay* m_dataDisplay;
	bool m_analytics;
};