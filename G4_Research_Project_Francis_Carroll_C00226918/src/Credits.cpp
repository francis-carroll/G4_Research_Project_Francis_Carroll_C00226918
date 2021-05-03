#include "Credits.h"

Credits::Credits()
{
}

Credits::~Credits()
{
}

void Credits::update(Time t_dt)
{
	m_position -= Vector2f(0.0f, 6.0f * t_dt.asSeconds());
	m_credits.setPosition(m_position);

	if (m_position.y <= -690.0f)
	{
		s_scene = Scene::MainMenu;
	}
}

void Credits::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(m_credits);
}

void Credits::handleKeyInput(Event& t_event)
{
}

void Credits::handleMouseInput(Event& t_event)
{
}

void Credits::sceneSetup()
{
	if (!m_font.loadFromFile("resources/fonts/default.ttf")) { cout << "Error loading font" << endl; }

	m_credits.setFont(m_font);
	m_credits.setString("				   Developed By\n				   Francis Carroll\n\n\n\n				 Technology Used\n						  SFML\n				         THOR\n					      YAML\n				  Visual Studio 2019\n\n\n\n				  Programmed Using\n							C++\n\n\n\n				    	Thanks To\n					Martin Harrigan,\n For the continued Support and Guidance");
	m_credits.setCharacterSize(25.0f);
	m_credits.setFillColor(Color::White);
	m_position = Vector2f(230.0f, SCREEN_HEIGHT);
	m_credits.setPosition(m_position);
}
