#include "BSPScreen.h"

extern float s_bsp_runtime_core = 0.0f;
extern float s_bsp_runtime_post = 0.0f;

BSPScreen::BSPScreen() :
	m_key(make_shared<Key>(Vector2f(20.0f, 20.0f), Vector2f(220.0f, 180.0f), "Key:\nB - Display BSP\nR - Display Rooms\nC - Display Connections\nK - Display Key\nE - Finish Execution")),
	m_dataDisplay(make_shared<AnalyticDataDisplay>(Vector2f(10.0f, 10.0f))),
	m_analytics(false)
{
	BSPData* bspData = new BSPData();
	LevelLoader::load("bspmed", bspData);
	m_bspFloor = make_shared<BSPFloor>(bspData);
}

BSPScreen::~BSPScreen()
{
}

void BSPScreen::update(Time t_dt)
{
	if (m_analytics)
	{
		m_dataDisplay->update(t_dt);
	}
}

void BSPScreen::render(shared_ptr<RenderWindow> t_window)
{
	m_bspFloor->render(t_window);
	if (!m_analytics)
	{
		m_key->render(t_window);
	}
	else
	{
		m_dataDisplay->render(t_window);
	}
}

void BSPScreen::handleKeyInput(Event& t_event)
{
	if (t_event.key.code == Keyboard::E)
	{
		m_analytics = true;
		//loading

		string message = "";

		instanciateBSP(message, "bsplarge", "Large");
		instanciateBSP(message, "bspmed", "Medium");
		instanciateBSP(message, "bspsmall", "Small");

		m_dataDisplay->setString(message);
	}

	if (!m_analytics)
	{
		m_bspFloor->keyInput(t_event);
		m_key->keyPresses(t_event);
	}
}

void BSPScreen::handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window)
{
	if(m_analytics)
	{
		m_dataDisplay->handleMouseInput(t_event, t_window);
	}
}

void BSPScreen::instanciateBSP(string& t_message, string t_filename, string t_size)
{
	auto startSmall = chrono::steady_clock::now();
	BSPData* bspData = new BSPData();
	LevelLoader::load(t_filename, bspData);
	BSPFloor* temp = new BSPFloor(bspData);
	auto endSmall = chrono::steady_clock::now();
	auto smallSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endSmall - startSmall);
	s_bsp_runtime_core = smallSeconds.count() / 1000.0f;
	s_bsp_runtime_core -= s_bsp_runtime_post;
	t_message += "BSP " + t_size + "\nRuntime - " + to_string(s_bsp_runtime_core + s_bsp_runtime_post) +
		" seconds\n	Core Runtime - \n		" + to_string(s_bsp_runtime_core) +
		" seconds\n	Post Processing Runtime - \n		" + to_string(s_bsp_runtime_post) + " seconds\n\n";
	delete temp;
}
