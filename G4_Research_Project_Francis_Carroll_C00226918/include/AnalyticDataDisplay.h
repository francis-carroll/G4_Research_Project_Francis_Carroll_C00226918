#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
#include <Button.h>

using namespace std;
using namespace sf;

class AnalyticDataDisplay
{
public:
	AnalyticDataDisplay(Vector2f t_position);
	~AnalyticDataDisplay();

	void setString(string t_string);
	void render(shared_ptr<RenderWindow> t_window);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
	void update(Time t_dt);
private:
	void setup();

	Vector2f m_position;
	RectangleShape m_bg;
	Text m_text;
	Font m_font;
	string m_content;
	Button m_button;
};