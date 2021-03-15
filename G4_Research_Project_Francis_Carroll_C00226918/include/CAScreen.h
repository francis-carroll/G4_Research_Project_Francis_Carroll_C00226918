#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <CA.h>
#include <LevelLoader.h>
#include <chrono>
#include <Key.h>

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
	void handleMouseInput(Event& t_event);
private:
	shared_ptr<CA> m_caGrid;
	shared_ptr<Key> m_key;
};