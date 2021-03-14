#include "MainMenu.h"

MainMenu::MainMenu()
{
	sceneSetup();
}

MainMenu::~MainMenu()
{
}

void MainMenu::update(Time t_dt)
{
	if (m_buttons[(int)ButtonPressed::BSP]->getButtonState() == ButtonState::Clicked)
		s_scene = Scene::BSP;

	if (m_buttons[(int)ButtonPressed::CA]->getButtonState() == ButtonState::Clicked)
		s_scene = Scene::CA;
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
	m_buttons.push_back(make_shared<Button>(Vector2f(100.0f, 100.0f), "BSP"));
	m_buttons.push_back(make_shared<Button>(Vector2f(100.0f, 200.0f), "CA"));
}