#include "CAScreen.h"

extern float s_ca_runtime_core = 0.0f;
extern float s_ca_runtime_post = 0.0f;

CAScreen::CAScreen() : 
	m_key(nullptr),
	m_dataDisplay(nullptr),
	m_analytics(false),
	m_caGrid(nullptr)
{
}

CAScreen::~CAScreen()
{
}

void CAScreen::update(Time t_dt)
{
	if (m_analytics)
	{
		if (m_dataDisplay->getButton()->getButtonState() == ButtonState::Clicked)
		{
			s_scene = Scene::MainMenu;
			m_dataDisplay->getButton()->setButtonState(ButtonState::None);
			delete m_caGrid;
			delete m_dataDisplay;
			delete m_key;
		}
	}
}

void CAScreen::render(shared_ptr<RenderWindow> t_window)
{
	if (m_caGrid != nullptr)
	{
		m_caGrid->render(t_window);
		if (!m_analytics)
		{
			m_key->render(t_window);
		}
		else
		{
			m_dataDisplay->render(t_window);
		}
	}
}

void CAScreen::handleKeyInput(Event& t_event)
{
	if (t_event.key.code == Keyboard::E)
	{
		m_analytics = true;
		//loading
		
		string message = "";

		instanciateCA(message, "calarge", "Large");
		instanciateCA(message, "camed", "Medium");
		instanciateCA(message, "casmall", "Small");

		m_dataDisplay->setString(message);
	}

	if (m_caGrid != nullptr)
	{
		if (!m_analytics)
		{
			m_caGrid->keyPresses(t_event);
			m_key->keyPresses(t_event);
		}
	}
}

void CAScreen::handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window)
{
	if (m_analytics)
	{
		m_dataDisplay->handleMouseInput(t_event, t_window);
	}
}

void CAScreen::initScene()
{
	CAData* caData = new CAData();
	LevelLoader::load("camed", caData);
	m_caGrid = new CA(caData);
	m_key = new Key(Vector2f(20.0f, 20.0f), Vector2f(220.0f, 120.0f), "Key:\nR - Display Processed CA\nK - Display Key\nE - Finish Execution");
	m_dataDisplay = new AnalyticDataDisplay(Vector2f(10.0f, 10.0f));
	m_analytics = false;
}

void CAScreen::instanciateCA(string& t_message, string t_filename, string t_size)
{
	auto startSmall = chrono::steady_clock::now();
	CAData* caData = new CAData();
	LevelLoader::load(t_filename, caData);
	CA* temp = new CA(caData);
	auto endSmall = chrono::steady_clock::now();
	auto smallSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endSmall - startSmall);
	s_ca_runtime_core = smallSeconds.count() / 1000.0f;
	s_ca_runtime_core -= s_ca_runtime_post;
	t_message += "CA " + t_size + "\nRuntime - " + to_string(s_ca_runtime_core + s_ca_runtime_post) +
		" seconds\n	Core Runtime - \n		" + to_string(s_ca_runtime_core) +
		" seconds\n	Post Processing Runtime - \n		" + to_string(s_ca_runtime_post) + " seconds\n\n";
	delete temp;
}
