#include "Game.h"

Game::Game() : 
	m_window(make_shared<RenderWindow>(sf::VideoMode(1000, 1000, 32), "G4 Project", sf::Style::Default)), 
	m_bspFloor(make_shared<BSPFloor>())
{
}

Game::~Game()
{
}

void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Time timePerFrame = seconds(1.f / 60.f); // 60 fps

	while (m_window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::update(Time t_deltaTime)
{
}

void Game::render()
{
	m_window->clear(Color::White);

	m_bspFloor->render(m_window);

	m_window->display();
}

void Game::processEvents()
{
	Event event;
	while (m_window->pollEvent(event))
	{
		handleInput(event);
	}
}

void Game::handleInput(Event& event)
{
	if (event.type == Event::Closed)
	{
		m_window->close();
	}

	if (event.type == Event::KeyPressed)
	{
		keyPresses(event);
	}

	if (event.type == Event::MouseButtonPressed)
	{
		mousePresses(event);
	}
}

void Game::keyPresses(Event& event)
{
	m_bspFloor->keyPressed(event);
}

void Game::mousePresses(Event& event)
{
}
