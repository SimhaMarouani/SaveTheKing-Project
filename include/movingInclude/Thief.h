#pragma once
#include "Player.h"

class Thief : public Player
{
public:
	Thief(sf::Vector2f position, sf::Vector2f size, Board& board);

	void handleCollision(Key& key) override;
	void handleCollision(Gate& gate) override;
	bool thiefHasKey();

private:
	bool m_hasKey = false;
};