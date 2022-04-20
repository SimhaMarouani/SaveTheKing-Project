#pragma once
#include "staticInclude/StaticObjects.h"
#include "movingInclude/Player.h"
#include "movingInclude/Dwarf.h"

class Board;

class Ork : public StaticObjects
{
public:
	Ork(sf::Vector2f position, sf::Vector2f size, Board& board);

	void handleCollision(GameObject& object) { object.handleCollision(*this); }
	void handleCollision(Player& player) { player.handleCollision(*this); }
	void handleCollision(Dwarf& dwarf) { dwarf.handleCollision(*this); }
	void DeleteObj();

private:
	Board* m_board;
};