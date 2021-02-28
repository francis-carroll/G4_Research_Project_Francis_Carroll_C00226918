#include "BSPScreen.h"

BSPScreen::BSPScreen()
{
	shared_ptr<BSPData> bspData = make_shared<BSPData>();
	LevelLoader::load("bsp", bspData);
	m_bspFloor = make_shared<BSPFloor>(bspData);
}

BSPScreen::~BSPScreen()
{
}

void BSPScreen::update(Time t_dt)
{
}

void BSPScreen::render(shared_ptr<RenderWindow> t_window)
{
	m_bspFloor->render(t_window);
}

void BSPScreen::handleKeyInput(Event& t_event)
{
	m_bspFloor->keyInput(t_event);
}

void BSPScreen::handleMouseInput(Event& t_event)
{
}
