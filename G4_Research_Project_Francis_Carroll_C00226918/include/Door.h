#pragma once

#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

/// <summary>
/// Direction a door can face
/// </summary>
enum class DoorDirection
{
	North, 
	East,
	South,
	West
};

/// <summary>
/// Door class keeps refernce to the direction and position of the door
/// </summary>
class Door
{
public:
	Door() = default;
	Door(DoorDirection t_direction, Vector2f t_position);
	~Door();

	Vector2f getPosition();
	DoorDirection getDirection();
	bool getMarked();

	void setMarked(bool t_marked);
private:
	DoorDirection m_direction;
	Vector2f m_doorPosition;
	bool m_marked;
};