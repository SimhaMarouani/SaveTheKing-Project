#include "staticInclude/BadGift.h"
#include "Controller.h"

void BadGift::activateGift(Controller& controller)
{
	DeleteObj();
	controller.decTime();
}