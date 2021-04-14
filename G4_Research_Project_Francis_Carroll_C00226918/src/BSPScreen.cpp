#include "BSPScreen.h"

extern float s_bsp_runtime_core = 0.0f;
extern float s_bsp_runtime_post = 0.0f;

BSPScreen::BSPScreen() :
	m_key(nullptr),
	m_dataDisplay(nullptr),
	m_bspFloor(nullptr),
	m_analytics(false)
{
}

BSPScreen::~BSPScreen()
{
}

void BSPScreen::update(Time t_dt)
{
	if (m_analytics)
	{
		if (m_dataDisplay->getButton()->getButtonState() == ButtonState::Clicked)
		{
			s_scene = Scene::MainMenu;
			m_dataDisplay->getButton()->setButtonState(ButtonState::None);
			delete m_bspFloor;
			delete m_key;
			delete m_dataDisplay;
		}
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

	if (t_event.key.code == Keyboard::Num1)
	{
		BSPData* bspData = new BSPData();
		LevelLoader::load("bspsmall", bspData);
		m_bspFloor = new BSPFloor(bspData);
	}
	if (t_event.key.code == Keyboard::Num2)
	{
		BSPData* bspData = new BSPData();
		LevelLoader::load("bspmed", bspData);
		m_bspFloor = new BSPFloor(bspData);
	}
	if (t_event.key.code == Keyboard::Num3)
	{
		BSPData* bspData = new BSPData();
		LevelLoader::load("bsplarge", bspData);
		m_bspFloor = new BSPFloor(bspData);
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

void BSPScreen::initScene()
{
	BSPData* bspData = new BSPData();
	LevelLoader::load("bspmed", bspData);
	m_bspFloor = new BSPFloor(bspData);
	m_key = new Key(Vector2f(20.0f, 20.0f), Vector2f(220.0f, 230.0f), "Key:\nB - Display BSP\nR - Display Rooms\nC - Display Connections\nK - Display Key\nE - Finish Execution\n1 - Small Grid\n2 - Medium Grid\n3 - Large Grid");
	m_dataDisplay = new AnalyticDataDisplay(Vector2f(10.0f, 10.0f));
	m_analytics = false;
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
