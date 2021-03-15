#include "BSPScreen.h"

extern float s_bsp_runtime_core = 0.0f;
extern float s_bsp_runtime_post = 0.0f;

BSPScreen::BSPScreen() :
	m_key(make_shared<Key>(Vector2f(20.0f, 20.0f), Vector2f(220.0f, 180.0f), "Key:\nB - Display BSP\nR - Display Rooms\nC - Display Connections\nK - Display Key\nE - Finish Execution"))
{
	auto start = chrono::steady_clock::now();
	shared_ptr<BSPData> bspData = make_shared<BSPData>();
	LevelLoader::load("bsp", bspData);
	m_bspFloor = make_shared<BSPFloor>(bspData);
	auto end = chrono::steady_clock::now();
	auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	s_bsp_runtime_core = seconds.count() / 1000.0f;
	s_bsp_runtime_core -= s_bsp_runtime_post;
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
	m_key->render(t_window);
}

void BSPScreen::handleKeyInput(Event& t_event)
{
	m_bspFloor->keyInput(t_event);
	m_key->keyPresses(t_event);
}

void BSPScreen::handleMouseInput(Event& t_event)
{
}
