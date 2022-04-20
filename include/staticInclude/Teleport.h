#pragma once
#include "staticInclude/StaticObjects.h"

class Teleport : public StaticObjects
{
public:
	Teleport(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::teleport, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& gameObject) { gameObject.handleCollision(*this); }

	sf::Vector2f getPosition() { return m_icon.getPosition(); }
};