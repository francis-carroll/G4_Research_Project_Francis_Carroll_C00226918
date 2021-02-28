#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <LevelLoader.h>
#include <BSPFloor.h>

using namespace std;
using namespace sf;

class BSPScreen
{
public:
	BSPScreen();
	~BSPScreen();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event t_event);
	void handleMouseInput(Event t_event);
private:
	shared_ptr<BSPFloor> m_bspFloor;
};