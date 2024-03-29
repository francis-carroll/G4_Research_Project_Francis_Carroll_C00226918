#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;

/// <summary>
/// The current state of a button
/// </summary>
enum class ButtonState
{
	None,
	Clicked
};

/// <summary>
/// Interactible button
/// </summary>
class Button
{
public:
	Button(Vector2f t_position, string t_text);
	~Button();

	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);

	ButtonState getButtonState();
	void setButtonState(ButtonState t_state);
private:
	void setup();
	bool collision(shared_ptr<RenderWindow> t_window);
	bool hover(Event& t_event, shared_ptr<RenderWindow> t_window);
	bool click(shared_ptr<RenderWindow> t_window);

	string m_textContents;
	Vector2f m_position;
	Vector2f m_padding;

	Text m_buttonText;
	Font m_font;

	RectangleShape m_button;
	ButtonState m_state;
};

