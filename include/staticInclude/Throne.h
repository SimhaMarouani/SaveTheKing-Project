#pragma once
#include "staticInclude/StaticObjects.h"

class Throne : public StaticObjects
{
public:
	Throne(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::throne, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }
};