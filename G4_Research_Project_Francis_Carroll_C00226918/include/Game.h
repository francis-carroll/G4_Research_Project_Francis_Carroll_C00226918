#pragma once

#include <SFML/Graphics.hpp>

#include <Intro.h>
#include <MainMenu.h>
#include <Credits.h>
#include <BSPScreen.h>
#include <CAScreen.h>

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
	void initialiseScenes();
	void keyInput(Event& t_event);
	void mouseInput(Event& t_event);

	shared_ptr<RenderWindow> m_window;

	shared_ptr<Intro> m_intro;
	shared_ptr<MainMenu> m_menu;
	shared_ptr<Credits> m_credits;
	shared_ptr<BSPScreen> m_bsp;
	shared_ptr<CAScreen> m_ca;
};