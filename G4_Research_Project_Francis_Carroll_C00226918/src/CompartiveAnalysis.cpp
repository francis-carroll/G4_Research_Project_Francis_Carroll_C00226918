#include "CompartiveAnalysis.h"

ComparitiveAnalysis::ComparitiveAnalysis() : 
	m_dataDisplay(new AnalyticDataDisplay(Vector2f(10.0f,10.0f)))
{
}

ComparitiveAnalysis::~ComparitiveAnalysis()
{
	delete m_dataDisplay;
}

void ComparitiveAnalysis::update(Time t_dt)
{
	if (m_dataDisplay->getButton()->getButtonState() == ButtonState::Clicked)
	{
		s_scene = Scene::MainMenu;
		m_dataDisplay->getButton()->setButtonState(ButtonState::None);
		delete m_dataDisplay;
	}
}

void ComparitiveAnalysis::render(shared_ptr<RenderWindow> t_window)
{
	m_dataDisplay->render(t_window);
}

void ComparitiveAnalysis::handleKeyInput(Event& t_event)
{
}

void ComparitiveAnalysis::handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window)
{
	m_dataDisplay->handleMouseInput(t_event, t_window);
}

void ComparitiveAnalysis::sceneSetup()
{
	m_dataDisplay = new AnalyticDataDisplay(Vector2f(10.0f, 10.0f));

	string bspMessage;
	initialiseBSP(bspMessage, "bsplarge", "Large");
	initialiseBSP(bspMessage, "bspmed", "Medium");
	initialiseBSP(bspMessage, "bspsmall", "Small");

	string caMessage;
	initialiseCA(caMessage, "calarge", "Large");
	initialiseCA(caMessage, "camed", "Medium");
	initialiseCA(caMessage, "casmall", "Small");

	m_dataDisplay->setString(bspMessage);
	m_dataDisplay->setString2(caMessage);
}

void ComparitiveAnalysis::initialiseCA(string& t_message, string t_fileName, string t_title)
{
	auto startSmall = chrono::steady_clock::now();
	auto startMem = getMemUsed();

	CAData* caData = new CAData();
	LevelLoader::load(t_fileName, caData);
	CA* temp = new CA(caData);

	auto endSmall = chrono::steady_clock::now();
	auto endMem = getMemUsed();
	auto smallSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endSmall - startSmall);
	auto memUsed = endMem - startMem;

	s_ca_runtime_core = smallSeconds.count() / 1000.0f;
	delete temp;

	s_ca_runtime_core -= s_ca_runtime_post;
	t_message += "CA " + t_title + "\nRuntime - " + to_string(s_ca_runtime_core + s_ca_runtime_post) +
		" seconds\nCore Runtime - \n		" + to_string(s_ca_runtime_core) +
		" seconds\nPost Processing Runtime - \n		" + to_string(s_ca_runtime_post) +
		" seconds\nMemory Used - \n		" + to_string(memUsed) + " MB\n\n";
}

void ComparitiveAnalysis::initialiseBSP(string& t_message, string t_fileName, string t_title)
{
	auto startSmall = chrono::steady_clock::now();
	auto startMem = getMemUsed();

	BSPData* bspData = new BSPData();
	LevelLoader::load(t_fileName, bspData);
	BSPFloor* temp = new BSPFloor(bspData);

	auto endSmall = chrono::steady_clock::now();
	auto endMem = getMemUsed();

	auto smallSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(endSmall - startSmall);
	auto memUsed = endMem - startMem;

	s_bsp_runtime_core = smallSeconds.count() / 1000.0f;
	delete temp;

	s_bsp_runtime_core -= s_bsp_runtime_post;
	t_message += "BSP " + t_title + "\nRuntime - " + to_string(s_bsp_runtime_core + s_bsp_runtime_post) +
		" seconds\nCore Runtime - \n		" + to_string(s_bsp_runtime_core) +
		" seconds\nPost Processing Runtime - \n		" + to_string(s_bsp_runtime_post) + 
		" seconds\nMemory Used - \n		" + to_string(memUsed) + " MB\n\n";
}

SIZE_T ComparitiveAnalysis::getMemUsed()
{
	PROCESS_MEMORY_COUNTERS_EX pmc = PROCESS_MEMORY_COUNTERS_EX();
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T s = pmc.PrivateUsage;
	return s / 1024 / 1024; //mbs
}
