#pragma once
#include "GameObject.h"

class StaticObjects : public GameObject
{
public:
	using GameObject::GameObject;
	virtual ~StaticObjects() = default;

	virtual void handleCollision(GameObject&) = 0;
	virtual void handleCollision(Player&) = 0;
	virtual void handleCollision(Dwarf&) = 0;
	virtual void handleCollision(Wall&) {};
	virtual void handleCollision(Ork&) {};
	virtual void handleCollision(Fire&) {};
	virtual void handleCollision(Teleport&) {};
	virtual void handleCollision(Throne&) {};
	virtual void handleCollision(Gate&) {};
	virtual void handleCollision(Key&) {};
	virtual void handleCollision(GiftKillDwarves&) {};
	virtual void handleCollision(BadGift&) {};
	virtual void handleCollision(GiftTime&) {};

	void DeleteObj();
	bool needToDelete() const;

protected:
	bool m_delete = false;
};
