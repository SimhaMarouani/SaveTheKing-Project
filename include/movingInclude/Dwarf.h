#pragma once
#include "movingInclude/MovingObjects.h"

class Dwarf : public MovingObjects
{
public:
	Dwarf(sf::Vector2f position, sf::Vector2f size);

	void move(float deltaTime);
	void changeDirection();

	virtual void handleCollision(GameObject&);
	virtual void handleCollision(Dwarf&);
	virtual void handleCollision(Player&);
	virtual void handleCollision(Wall&);
	virtual void handleCollision(Throne&);
	virtual void handleCollision(Ork&);
	virtual void handleCollision(Key&);
	virtual void handleCollision(Fire&);
	virtual void handleCollision(Gate&);
	virtual void handleCollision(Teleport&);
	virtual void handleCollision(GiftKillDwarves&);
	virtual void handleCollision(BadGift&);
	virtual void handleCollision(GiftTime&);

	sf::Keyboard::Key getDirection() const;

private:
	sf::Clock m_clock;
};
