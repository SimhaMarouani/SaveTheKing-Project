#pragma once
#include <SFML/Audio.hpp>
#include "Player.h"

class Mage : public Player
{
public:
	Mage(sf::Vector2f position, sf::Vector2f size, Board& board);

	void handleCollision(Fire& fire) override;
	void handleCollision(Teleport& teleport) override;
};