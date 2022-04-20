#include "movingInclude/Thief.h"
#include "staticInclude/Key.h"
#include "staticInclude/Gate.h"
#include "resourcesManager.h"

Thief::Thief(sf::Vector2f position, sf::Vector2f size, Board& board)
    :Player(Elements::thief, position, size, board)
{}

void Thief::handleCollision(Key& Key)
{
    if (!m_hasKey)
    {
        Key.DeleteObj();
        m_hasKey = true;
        m_icon.setTexture(ResourcesManager::instance().getIcon(Elements::thiefKey));
    }
}

void Thief::handleCollision(Gate& gate)
{
    if (m_hasKey)
    {
        gate.DeleteObj();
        m_hasKey = false;
        m_icon.setTexture(ResourcesManager::instance().getIcon(Elements::thief));
    }
    m_icon.setPosition(m_prevPos);
}

bool Thief::thiefHasKey()
{
    return m_hasKey;
}