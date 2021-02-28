#include "Intro.h"

Intro::Intro()
{
}

Intro::~Intro()
{
}

void Intro::update(Time t_dt)
{
	s_scene = Scene::MainMenu;
}

void Intro::render(shared_ptr<RenderWindow> t_window)
{
}

void Intro::handleKeyInput(Event t_event)
{
}

void Intro::handleMouseInput(Event t_event)
{
}