#pragma once
#include <SFML/Audio.hpp>
#include "Macros.h"
#include "Player.h"

class Warrior : public Player
{
public:
	Warrior(sf::Vector2f position, sf::Vector2f size, Board& board);

	void handleCollision(Ork& ork) override;

private:
	sf::Sound m_killOrk;
};