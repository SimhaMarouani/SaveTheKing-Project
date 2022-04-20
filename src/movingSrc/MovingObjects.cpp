#include "movingInclude/MovingObjects.h"
#include "Board.h"
#include "staticInclude/Teleport.h"

MovingObjects::MovingObjects(Elements object, const sf::Vector2f& position, sf::Vector2f size)
    : GameObject(object, position, size), m_prevPos(position)
{}

void MovingObjects::setDirection(sf::Keyboard::Key key)
{
    switch (key)
    {
    case sf::Keyboard::Key::Left:
        m_direction = sf::Vector2f(-1, 0);
        break;

    case sf::Keyboard::Key::Right:
        m_direction = sf::Vector2f(1, 0);
        break;

    case sf::Keyboard::Key::Up:
        m_direction = sf::Vector2f(0, -1);
        break;

    case sf::Keyboard::Key::Down:
        m_direction = sf::Vector2f(0, 1);
        break;

    default:
        m_direction = sf::Vector2f(0, 0);
        break;
    }
}

void MovingObjects::handleCollision(Wall& wall)
{
    m_icon.setPosition(m_prevPos);
}