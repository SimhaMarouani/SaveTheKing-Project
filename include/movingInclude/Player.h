#pragma once
#include "movingInclude/MovingObjects.h"
#include <SFML/Audio.hpp>

class Board;

class Player : public MovingObjects
{
public:
	Player(Elements, const sf::Vector2f&, sf::Vector2f, Board& board);

	void move(float deltaTime);
	void choosePlayer();
	void unchoosePlayer();

	virtual bool getKingOnThrone() { return false; }
	virtual bool thiefHasKey() { return false; }

	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Player&);
	virtual void handleCollision(Wall&);
	virtual void handleCollision(Throne&);
	virtual void handleCollision(Ork&);
	virtual void handleCollision(Key&);
	virtual void handleCollision(Fire&);
	virtual void handleCollision(Gate&);
	virtual void handleCollision(Teleport&);
	virtual void handleCollision(Dwarf& dwarf);
	virtual void handleCollision(GiftKillDwarves&);
	virtual void handleCollision(BadGift&);
	virtual void handleCollision(GiftTime&);

protected:
	Board* m_board;
	sf::Sound m_teleportSound;
};