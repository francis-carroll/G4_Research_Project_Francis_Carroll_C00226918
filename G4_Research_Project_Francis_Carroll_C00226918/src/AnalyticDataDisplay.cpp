#include "AnalyticDataDisplay.h"

AnalyticDataDisplay::AnalyticDataDisplay(Vector2f t_position) : 
	m_position(t_position),
	m_button(new Button(Vector2f(SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT - 50.0f), "Main Menu"))
{
	setup();
}

AnalyticDataDisplay::~AnalyticDataDisplay()
{
	delete m_button;
}

void AnalyticDataDisplay::setString(string t_string)
{
	m_content = t_string;
	m_text.setString(m_content);
}

void AnalyticDataDisplay::setString2(string t_string)
{
	m_content2 = t_string;
	m_text2.setString(m_content2);
}

void AnalyticDataDisplay::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(m_bg);
	t_window->draw(m_text);
	t_window->draw(m_text2);
	m_button->render(t_window);
}

void AnalyticDataDisplay::handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window)
{
	m_button->handleMouseInput(t_event, t_window);
}

Button* AnalyticDataDisplay::getButton()
{
	return m_button;
}

void AnalyticDataDisplay::setup()
{
	if (!m_font.loadFromFile("resources/fonts/default.ttf")) { cout << "Font could not be loaded" << endl; }

	m_bg.setPosition(m_position);
	m_bg.setSize(Vector2f(SCREEN_WIDTH - m_position.x - 10.0f, SCREEN_HEIGHT - m_position.y - 10.0f));
	m_bg.setOutlineColor(Color::Black);
	m_bg.setOutlineThickness(1);
	m_bg.setFillColor(Color(0.0f, 0.0f, 200.0f, 200.0f));

	m_text.setFont(m_font);
	m_text.setCharacterSize(20);
	m_text.setPosition(m_position + Vector2f(10.0f, 10.0f));
	m_text.setString(m_content);

	m_text2.setFont(m_font);
	m_text2.setCharacterSize(20);
	m_text2.setPosition(m_position + Vector2f(10.0f + SCREEN_WIDTH / 2.0f, 10.0f));
	m_text2.setString(m_content2);
}
