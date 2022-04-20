#pragma once
#include "staticInclude/StaticObjects.h"
#include "movingInclude/Dwarf.h"

class Gate : public StaticObjects
{
public:
	Gate(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::gate, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }
};