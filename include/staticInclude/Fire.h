#pragma once
#include "staticInclude/StaticObjects.h"
#include "movingInclude/Dwarf.h"

class Fire : public StaticObjects
{
public:
	Fire(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::fire, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }
};