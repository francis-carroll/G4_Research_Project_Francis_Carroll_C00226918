#pragma once
#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <iostream>
#include <CA.h>
#include <BSPFloor.h>
#include <AnalyticDataDisplay.h>
#include <windows.h>
#include <psapi.h>

using namespace std;
using namespace sf;


class ComparitiveAnalysis
{
public:
	ComparitiveAnalysis();
	~ComparitiveAnalysis();

	void update(Time t_dt);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
	void sceneSetup();
private:
	void initialiseCA(string& t_message, string t_fileName, string t_title);
	void initialiseBSP(string& t_message, string t_fileName, string t_title);
	SIZE_T getMemUsed();

	AnalyticDataDisplay* m_dataDisplay;
	PROCESS_MEMORY_COUNTERS_EX m_pmc;
};