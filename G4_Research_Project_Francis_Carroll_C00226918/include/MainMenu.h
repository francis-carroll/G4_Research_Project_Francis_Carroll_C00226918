#pragma once

#include <SFML/Graphics.hpp>
#include <Globals.h>
#include <Button.h>

using namespace std;
using namespace sf;

class CAScreen;

enum class ButtonPressed
{
	BSP,
	CA,
	Comparitive
};

class MainMenu
{
public:
	MainMenu();
	~MainMenu();
	void update(Time t_dt, shared_ptr<CAScreen> t_caScreen);
	void render(shared_ptr<RenderWindow> t_window);
	void handleKeyInput(Event& t_event);
	void handleMouseInput(Event& t_event, shared_ptr<RenderWindow> t_window);
private:
	void sceneSetup();

	vector<shared_ptr<Button>> m_buttons;
};