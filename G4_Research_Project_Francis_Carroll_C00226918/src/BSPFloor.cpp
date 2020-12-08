#include "BSPFloor.h"

BSPFloor::BSPFloor() : 
	m_renderBSP(true),
	m_renderRooms(true),
	m_bspHead(make_shared<BSPNode>())
{
	generateBSP();
}

BSPFloor::~BSPFloor()
{
}

void BSPFloor::toggleRooms()
{
	m_renderRooms = m_renderRooms + 1 % 2;
}

void BSPFloor::toggleBSP()
{
	m_renderBSP = m_renderBSP + 1 % 2;
}

void BSPFloor::handleInput(Event& t_event)
{
	if (t_event.KeyPressed) 
	{
		if (t_event.key.code == Keyboard::R)
		{
			toggleRooms();
		}
		else if (t_event.key.code == Keyboard::R)
		{
			toggleBSP();
		}
	}
}

void BSPFloor::generateBSP()
{
	shared_ptr<BSPTree> bspTree = make_shared<BSPTree>();
	bspTree->setPadding(50, 50, 50, 50);
	bspTree->setMinRoomsize(Vector2f(50.0f, 50.0f));
	m_bspHead = bspTree->bsp(Vector2f(10.0f, 10.0f), Vector2f(800.0f, 800.0f));
}

void BSPFloor::setupRooms()
{

}