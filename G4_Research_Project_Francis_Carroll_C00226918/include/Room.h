#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class Room
{
public:
	Room();
	Room(int t_id, Vector2f t_position, Vector2f t_size, Vector2f t_center);
	~Room();

	RectangleShape getRoom();
private:
	void setupShape();

	int m_id;
	Vector2f m_position;
	Vector2f m_size;
	Vector2f m_center;
	RectangleShape m_roomShape;
};

