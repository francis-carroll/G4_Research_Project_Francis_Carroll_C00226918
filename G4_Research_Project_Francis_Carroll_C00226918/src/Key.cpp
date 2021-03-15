#include "Key.h"

Key::Key(Vector2f t_position, Vector2f t_size, string t_content) : 
	m_renderKey(true),
	m_size(t_size),
	m_position(t_position),
	m_content(t_content)
{
	setup();
}

Key::~Key()
{
}

void Key::update(Time t_dt)
{
}

void Key::render(shared_ptr<RenderWindow> t_window)
{
	if (m_renderKey)
	{
		t_window->draw(m_bg);
		t_window->draw(m_text);
	}
}

void Key::keyPresses(Event& t_event)
{
	if (t_event.key.code == Keyboard::K)
	{
		toggleBool(m_renderKey);
	}
}

void Key::setup()
{
	if (!m_font.loadFromFile("resources/fonts/default.ttf")) { cout << "Font could not be loaded" << endl; }

	m_bg.setSize(m_size);
	m_bg.setPosition(m_position);
	m_bg.setOutlineColor(Color::Black);
	m_bg.setOutlineThickness(1);
	m_bg.setFillColor(Color(0.0f,0.0f,200.0f,200.0f));

	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setPosition(m_position + Vector2f(10.0f,10.0f));
	m_text.setString(m_content);
}
