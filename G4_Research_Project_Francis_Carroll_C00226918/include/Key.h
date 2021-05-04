#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <Globals.h>

using namespace std;
using namespace sf;

/// <summary>
/// Toggeable key used for siplaying input commands
/// </summary>
class Key
{
public:
	Key(Vector2f t_position, Vector2f t_size, string t_content);
	~Key();

	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void keyPresses(Event& t_event);
private:
	void setup();

	RectangleShape m_bg;
	Text m_text;
	Font m_font;

	bool m_renderKey;
	Vector2f m_position;
	Vector2f m_size;
	string m_content;
};