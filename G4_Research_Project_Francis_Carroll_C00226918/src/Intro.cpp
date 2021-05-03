#include "Intro.h"

Intro::Intro() : 
	 m_timer(seconds(0))
{
	setup();
}

Intro::~Intro()
{
}

void Intro::update(Time t_dt)
{
	m_timer += t_dt;
	if (m_timer.asSeconds() >= 45.0f)
	{
		s_scene = Scene::MainMenu;
		m_timer = seconds(0);
	}
}

void Intro::render(shared_ptr<RenderWindow> t_window)
{
	t_window->draw(m_introText);
}

void Intro::handleKeyInput(Event& t_event)
{
}

void Intro::handleMouseInput(Event& t_event)
{
}

void Intro::setup()
{
	if (!m_font.loadFromFile("resources/fonts/default.ttf")) { cout << "Error loading font" << endl; }

	m_introText.setFont(m_font);
	m_introText.setString("Investigation and analysis of procedural generation techniques\n						    in a dungeon/roguelike game");
	m_introText.setCharacterSize(25.0f);
	m_introText.setFillColor(Color::White);
	m_introText.setPosition(Vector2f(120.0f,350.0f));
}
