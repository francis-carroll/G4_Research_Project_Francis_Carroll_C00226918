#include "CAScreen.h"

extern float s_ca_runtime_core = 0.0f;
extern float s_ca_runtime_post = 0.0f;

CAScreen::CAScreen() : 
	m_key(make_shared<Key>(Vector2f(20.0f,20.0f), Vector2f(220.0f, 120.0f), "Key:\nR - Display Processed CA\nK - Display Key\nE - Finish Execution"))
{
	auto start = chrono::steady_clock::now();
	shared_ptr<CAData> caData = make_shared<CAData>();
	LevelLoader::load("ca", caData);
	m_caGrid = make_shared<CA>(caData);
	auto end = chrono::steady_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	s_ca_runtime_core = seconds.count() / 1000.0f;
	s_ca_runtime_core -= s_ca_runtime_post;
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
	m_key->render(t_window);
}

void CAScreen::handleKeyInput(Event& t_event)
{
	m_caGrid->keyPresses(t_event);
	m_key->keyPresses(t_event);
}

void CAScreen::handleMouseInput(Event& t_event)
{
}
