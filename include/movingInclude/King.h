#pragma once
#include "movingInclude/Player.h"
#include"movingInclude/MovingObjects.h"

class King : public Player
{
public:
	King(sf::Vector2f position, sf::Vector2f size, Board& board);

	void handleCollision(Throne& throne) override;
	bool getKingOnThrone() override;

private:
	bool m_kingOnThrone;
};