#pragma once
#include "staticInclude/StaticObjects.h"

class Wall : public StaticObjects
{
public:
	Wall(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::wall, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }
};