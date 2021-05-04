#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <iostream>

using namespace std;
using namespace sf;

/// <summary>
/// Screen that displays information
/// </summary>
class Intro
{
public:
	Intro();
	~Intro();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event);
private:
	void setup();

	Text m_introText;
	Font m_font;
	Time m_timer;
};