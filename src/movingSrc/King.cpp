#include "resourcesManager.h"
#include "movingInclude/King.h"

King::King(sf::Vector2f position, sf::Vector2f size, Board& board)
    :Player(Elements::king, position, size, board), m_kingOnThrone(false)
{}

void King::handleCollision(Throne& throne)
{
    ResourcesManager::instance().playSound(Sounds::win);
    m_kingOnThrone = true;
}

bool King::getKingOnThrone()
{
    return m_kingOnThrone;
}