#pragma once

#include <SFML/Graphics.hpp>

#include <BSPFloor.h>
#include <CA.h>

using namespace std;
using namespace sf;

/// <summary>
/// Game contains the main game loop for rendering, updating and handling events
/// </summary>
class Game
{
public:
	Game();
	~Game();
	void run();
	void update(Time t_deltaTime);
	void render();
	void processEvents();
	void handleInput(Event& t_event);
private:
	void keyInput(Event& t_event);
	void mouseInput(Event& t_event);

	shared_ptr<RenderWindow> m_window;
	shared_ptr<BSPFloor> m_bspFloor;
	shared_ptr<CA> m_caGrid;
};