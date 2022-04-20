#pragma once
#include "GameObject.h"
#include "Macros.h"

class Board;

class MovingObjects : public GameObject
{
public:
	MovingObjects(Elements , const sf::Vector2f& , sf::Vector2f);

	void setDirection(sf::Keyboard::Key key);

	virtual void move(float deltaTime) = 0;
	virtual void handleCollision(GameObject&) = 0;
	virtual void handleCollision(Dwarf&) = 0;
	virtual void handleCollision(Player&) = 0;
	virtual void handleCollision(Wall&);
	virtual void handleCollision(Throne&) = 0;
	virtual void handleCollision(Ork&) = 0;
	virtual void handleCollision(Key&) = 0;
	virtual void handleCollision(Fire&) = 0;
	virtual void handleCollision(Gate&) = 0;
	virtual void handleCollision(Teleport&) = 0;
	virtual void handleCollision(GiftKillDwarves&) = 0;
	virtual void handleCollision(BadGift&) = 0;
	virtual void handleCollision(GiftTime&) = 0;

protected:
	sf::Vector2f m_prevPos;
	sf::Vector2f m_direction;

	float m_speedPerSecond = BASE_SPEED;
};

