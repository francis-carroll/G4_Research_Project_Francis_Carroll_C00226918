#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <Globals.h>
#include <Button.h>

using namespace std;
using namespace sf;

/// <summary>
/// Displays the analytical data for each screen.
/// </summary>
class AnalyticDataDisplay
{
public:
	AnalyticDataDisplay(Vector2f t_position);
	~AnalyticDataDisplay();

	void setString(string t_string);
	void setString2(string t_string);
	void render(shared_ptr<RenderWindow> t_window);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
	Button* getButton();
private:
	void setup();

	Vector2f m_position;
	RectangleShape m_bg;
	Text m_text;
	Text m_text2;
	Font m_font;
	string m_content;
	string m_content2;
	Button* m_button;
};