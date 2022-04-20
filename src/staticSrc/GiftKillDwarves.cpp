#include "staticInclude/GiftKillDwarves.h"
#include "Controller.h"

void GiftKillDwarves::activateGift(Controller& game)
{
	DeleteObj();
	game.deleteDwarves();
}