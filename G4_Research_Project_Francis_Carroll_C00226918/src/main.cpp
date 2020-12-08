#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"thor-d.lib") 
#pragma comment(lib,"libyaml-cppmdd")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"thor.lib")
#pragma comment(lib,"libyaml-cppmd")
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib")

#include <BSPTree.h>

int main(int, char* argv[])
{

	srand((unsigned)time(nullptr));
	RenderWindow m_window(sf::VideoMode(1000, 1000, 32), "BSP", sf::Style::Default);

	//BSP Algorithm
	BSPTree* tree = new BSPTree;
	tree->setPadding(50, 50, 50, 50);
	tree->setMinRoomsize(Vector2f(50.0f, 50.0f));
	shared_ptr<BSPNode> head = tree->bsp(Vector2f(10.0f, 10.0f), Vector2f(800.0f, 800.0f));

	m_window.clear();
	tree->renderLeafNodes(m_window, head);
	m_window.display();

	system("PAUSE");

	return 0;
}