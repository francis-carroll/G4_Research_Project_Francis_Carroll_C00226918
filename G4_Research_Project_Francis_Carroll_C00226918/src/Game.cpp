#include "Game.h"

Game::Game() : 
	m_window(make_shared<RenderWindow>(sf::VideoMode(820, 820, 32), "G4 Project", sf::Style::Default))
{
	shared_ptr<BSPData> bspData = make_shared<BSPData>();
	LevelLoader::load("bsp", bspData);
	m_bspFloor = make_shared<BSPFloor>(bspData);

	shared_ptr<CAData> caData = make_shared<CAData>();
	LevelLoader::load("ca", caData);
	m_caGrid = make_shared<CA>(caData);
}

Game::~Game()
{
}

/// <summary>
/// Game loop which runs at 60 fps
/// </summary>
void Game::run()
{
	Clock clock;
	Time timeSinceLastUpdate = Time::Zero;
	Time timePerFrame = seconds(1.f / 60.f); // 60 fps

	while (m_window->isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.getElapsedTime();

		if (timeSinceLastUpdate > timePerFrame)
		{
			processEvents();
			update(timePerFrame);
			timeSinceLastUpdate -= timePerFrame;
			clock.restart();
		}
		render();
	}
}

/// <summary>
/// Updates the application
/// </summary>
/// <param name="t_deltaTime">time since last frame</param>
void Game::update(Time t_deltaTime)
{
}

/// <summary>
/// renders all entities within the application
/// </summary>
void Game::render()
{
	m_window->clear(Color::White);

	//m_bspFloor->render(m_window);
	m_caGrid->render(m_window);

	m_window->display();
}

/// <summary>
/// Processes events in the application
/// </summary>
void Game::processEvents()
{
	Event event;
	while (m_window->pollEvent(event))
	{
		handleInput(event);
	}
}

/// <summary>
/// Handles ecternal input
/// </summary>
/// <param name="t_event">ref to event</param>
void Game::handleInput(Event& t_event)
{
	if (t_event.type == Event::Closed)
	{
		m_window->close();
	}

	if (t_event.type == Event::KeyPressed)
	{
		keyInput(t_event);
	}

	if (t_event.type == Event::MouseButtonPressed)
	{
		mouseInput(t_event);
	}
}

/// <summary>
/// Handles keyboard input
/// </summary>
/// <param name="t_event">ref to event</param>
void Game::keyInput(Event& t_event)
{
	m_bspFloor->keyInput(t_event);
	m_caGrid->keyPresses(t_event);
}

/// <summary>
/// handles mouse input
/// </summary>
/// <param name="t_event">ref to event</param>
void Game::mouseInput(Event& t_event)
{
}
