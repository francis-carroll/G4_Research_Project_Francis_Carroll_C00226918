#include "Game.h"

extern enum Scene s_scene = Scene::Intro;

Game::Game() : 
	m_window(make_shared<RenderWindow>(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "G4 Project", sf::Style::Default))
{
	initialiseScenes();
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
	switch (s_scene)
	{
	case Scene::Intro:
		m_intro->update(t_deltaTime);
		break;
	case Scene::MainMenu:
		m_menu->update(t_deltaTime, m_ca);
		break;
	case Scene::Credits:
		m_credits->update(t_deltaTime);
		break;
	case Scene::BSP:
		m_bsp->update(t_deltaTime);
		break;
	case Scene::CA:
		m_ca->update(t_deltaTime);
		break;
	case Scene::ComparitiveAnalysis:
		m_comparitive->update(t_deltaTime);
		break;
	default:
		break;
	}
}

/// <summary>
/// renders all entities within the application
/// </summary>
void Game::render()
{
	m_window->clear(Color::White);

	switch (s_scene)
	{
	case Scene::Intro:
		m_intro->render(m_window);
		break;
	case Scene::MainMenu:
		m_menu->render(m_window);
		break;
	case Scene::Credits:
		m_credits->render(m_window);
		break;
	case Scene::BSP:
		m_bsp->render(m_window);
		break;
	case Scene::CA:
		m_ca->render(m_window);
		break;
	case Scene::ComparitiveAnalysis:
		m_comparitive->render(m_window);
		break;
	default:
		break;
	}

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

	if (t_event.type == Event::MouseButtonPressed || t_event.type == Event::MouseMoved)
	{
		mouseInput(t_event);
	}
}

void Game::initialiseScenes()
{
	m_intro = make_shared<Intro>();
	m_menu = make_shared<MainMenu>();
	m_credits = make_shared<Credits>();
	m_bsp = make_shared<BSPScreen>();
	m_ca = make_shared<CAScreen>();
	m_comparitive = make_shared<ComparitiveAnalysis>();
}

/// <summary>
/// Handles keyboard input
/// </summary>
/// <param name="t_event">ref to event</param>
void Game::keyInput(Event& t_event)
{
	switch (s_scene)
	{
	case Scene::Intro:
		m_intro->handleKeyInput(t_event);
		break;
	case Scene::MainMenu:
		m_menu->handleKeyInput(t_event);
		break;
	case Scene::Credits:
		m_credits->handleKeyInput(t_event);
		break;
	case Scene::BSP:
		m_bsp->handleKeyInput(t_event);
		break;
	case Scene::CA:
		m_ca->handleKeyInput(t_event);
		break;
	case Scene::ComparitiveAnalysis:
		m_comparitive->handleKeyInput(t_event);
		break;
	default:
		break;
	}
}

/// <summary>
/// handles mouse input
/// </summary>
/// <param name="t_event">ref to event</param>
void Game::mouseInput(Event& t_event)
{
	switch (s_scene)
	{
	case Scene::Intro:
		m_intro->handleMouseInput(t_event);
		break;
	case Scene::MainMenu:
		m_menu->handleMouseInput(t_event, m_window);
		break;
	case Scene::Credits:
		m_credits->handleMouseInput(t_event);
		break;
	case Scene::BSP:
		m_bsp->handleMouseInput(t_event, m_window);
		break;
	case Scene::CA:
		m_ca->handleMouseInput(t_event, m_window);
		break;
	case Scene::ComparitiveAnalysis:
		m_comparitive->handleMouseInput(t_event, m_window);
		break;
	default:
		break;
	}
}
