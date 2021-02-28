#include "CAScreen.h"

CAScreen::CAScreen()
{
	shared_ptr<CAData> caData = make_shared<CAData>();
	LevelLoader::load("ca", caData);
	m_caGrid = make_shared<CA>(caData);
}

CAScreen::~CAScreen()
{
}

void CAScreen::update(Time t_dt)
{
}

void CAScreen::render(shared_ptr<RenderWindow> t_window)
{
	m_caGrid->render(t_window);
}

void CAScreen::handleKeyInput(Event t_event)
{
	m_caGrid->keyPresses(t_event);
}

void CAScreen::handleMouseInput(Event t_event)
{
}
