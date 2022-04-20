#include "staticInclude/GiftTime.h"
#include "Controller.h"

void GiftTime::activateGift(Controller& controller)
{
	DeleteObj();
	controller.incTime();
}