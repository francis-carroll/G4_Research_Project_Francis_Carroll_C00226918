#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>

using namespace std;
using namespace sf;

class Credits
{
public:
	Credits();
	~Credits();
	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event t_event);
	void handleMouseInput(Event t_event);
};