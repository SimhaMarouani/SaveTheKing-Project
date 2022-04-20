#include "movingInclude/Mage.h"
#include "staticInclude/Fire.h"
#include "resourcesManager.h"

Mage::Mage(sf::Vector2f position, sf::Vector2f size, Board& board)
    :Player(Elements::mage, position, size, board)
{}

void Mage::handleCollision(Fire& fire)
{
    ResourcesManager::instance().playSound(Sounds::fire);
    fire.DeleteObj();
}

void Mage::handleCollision(Teleport& teleport)
{
    m_icon.setPosition(m_prevPos);
}