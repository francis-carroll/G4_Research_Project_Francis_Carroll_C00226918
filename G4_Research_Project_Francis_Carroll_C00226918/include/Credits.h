#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <iostream>

using namespace std;
using namespace sf;

/// <summary>
/// Screen that displays information about project.
/// </summary>
class Credits
{
public:
	Credits();
	~Credits();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event);
	void sceneSetup();
private:
	Text m_credits;
	Font m_font;
	Vector2f m_position;
};