#pragma once

#include <SFML/Graphics.hpp>

#include <BSPFloor.h>

using namespace std;
using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
	void update(Time t_deltaTime);
	void render();
	void processEvents();
	void handleInput(Event& event);
private:
	void keyPresses(Event& event);
	void mousePresses(Event& event);

	shared_ptr<RenderWindow> m_window;
	shared_ptr<BSPFloor> m_bspFloor;
};