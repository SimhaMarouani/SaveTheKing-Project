#include "resourcesManager.h"
#include "movingInclude/Dwarf.h"

Dwarf::Dwarf(sf::Vector2f position, sf::Vector2f size)
    :MovingObjects(Elements::dwarf, position, size)
{}

void Dwarf::move(float deltaTime)
{
    m_prevPos = m_icon.getPosition();
    m_icon.move(m_direction * m_speedPerSecond * deltaTime);
}

sf::Keyboard::Key Dwarf::getDirection() const
{
    if (m_direction.x < 0)
        return  sf::Keyboard::Right;
    
    return sf::Keyboard::Left; 
}

void Dwarf::changeDirection()
{
    if (m_clock.restart().asSeconds() > 0.1)
    {
        m_direction.x *= -1;
    }
}

//----------------------------- handle Collisions -------------------------------

void Dwarf::handleCollision(GameObject& object)
{
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Dwarf::handleCollision(Dwarf& dwarf)
{
    changeDirection();
}

void Dwarf::handleCollision(Player& player)
{
    changeDirection();
    m_icon.setPosition(m_prevPos);
}

void Dwarf::handleCollision(Ork& ork)
{
    changeDirection();
}

void Dwarf::handleCollision(Teleport& teleport)
{
    changeDirection();
}

void Dwarf::handleCollision(Wall& wall)
{
    changeDirection();
}

void Dwarf::handleCollision(Key& key)
{
    changeDirection();
}

void Dwarf::handleCollision(Fire& fire)
{
    changeDirection();
}

void Dwarf::handleCollision(Gate& gate)
{
    changeDirection();
}

void Dwarf::handleCollision(Throne& throne)
{
    changeDirection();
}

void Dwarf::handleCollision(GiftKillDwarves& gift)
{
    changeDirection();
}

void Dwarf::handleCollision(BadGift& gift)
{
    changeDirection();
}

void Dwarf::handleCollision(GiftTime& gift)
{
    changeDirection();
}