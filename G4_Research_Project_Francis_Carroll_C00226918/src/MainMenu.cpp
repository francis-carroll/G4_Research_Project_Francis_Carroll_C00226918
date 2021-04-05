#include "MainMenu.h"
#include <Game.h>

MainMenu::MainMenu()
{
	sceneSetup();
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(Time t_dt, Game& t_game)
{
	if (m_buttons[(int)ButtonPressed::BSP]->getButtonState() == ButtonState::Clicked)
	{
		s_scene = Scene::BSP;
		m_buttons[(int)ButtonPressed::BSP]->setButtonState(ButtonState::None);
		t_game.getBSPScreen()->initScene();
	}

	if (m_buttons[(int)ButtonPressed::CA]->getButtonState() == ButtonState::Clicked)
	{
		s_scene = Scene::CA;
		m_buttons[(int)ButtonPressed::CA]->setButtonState(ButtonState::None);
		t_game.getCAScreen()->initScene();
	}

	if (m_buttons[(int)ButtonPressed::Comparitive]->getButtonState() == ButtonState::Clicked)
	{
		s_scene = Scene::ComparitiveAnalysis;
		m_buttons[(int)ButtonPressed::Comparitive]->setButtonState(ButtonState::None);
		t_game.getCompAScreen()->sceneSetup();
	}
}

void MainMenu::render(shared_ptr<RenderWindow> t_window)
{
	for (shared_ptr<Button> button : m_buttons)
	{
		button->render(t_window);
	}
}

void MainMenu::handleKeyInput(Event& t_event)
{
}

void MainMenu::handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window)
{
	for (shared_ptr<Button> button : m_buttons)
	{
		button->handleMouseInput(t_event, t_window);
	}
}

void MainMenu::sceneSetup()
{
	m_buttons.push_back(make_shared<Button>(Vector2f(300.0f, 100.0f), "BSP"));
	m_buttons.push_back(make_shared<Button>(Vector2f(300.0f, 200.0f), "CA"));
	m_buttons.push_back(make_shared<Button>(Vector2f(300.0f, 300.0f), "Comparitive Analysis"));
}
