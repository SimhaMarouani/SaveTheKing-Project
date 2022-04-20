#include "movingInclude/Warrior.h"
#include "staticInclude/Ork.h"
#include "resourcesManager.h"

Warrior::Warrior(sf::Vector2f position, sf::Vector2f size, Board& board)
    :Player(Elements::warrior, position, size, board)
{}

void Warrior::handleCollision(Ork& ork)
{
    ResourcesManager::instance().playSound(Sounds::killOrk);
    ork.DeleteObj();
}