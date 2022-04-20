#pragma once
#include "staticInclude/StaticObjects.h"
#include "movingInclude/Player.h"
#include "movingInclude/Dwarf.h"

class Gift : public StaticObjects
{
public:
	Gift(sf::Vector2f position, sf::Vector2f size) :StaticObjects(Elements::gift, position, size) {}

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }

	virtual void activateGift(Controller& game) = 0;
	virtual bool isActive() const;
	virtual void needToActivate();

protected:
	bool m_active = false;
};