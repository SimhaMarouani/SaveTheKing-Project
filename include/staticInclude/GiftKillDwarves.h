#pragma once
#include "staticInclude/Gift.h"

class controller;

class GiftKillDwarves : public Gift
{
public:
	using Gift::Gift;

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }

	void activateGift(Controller& game);
};