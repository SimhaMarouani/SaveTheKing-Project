#include "movingInclude/Player.h"
#include "resourcesManager.h"
#include "Board.h"
#include "Macros.h"

Player::Player(Elements player, const sf::Vector2f& position, sf::Vector2f size, Board& board)
	:MovingObjects(player, position, size), m_board(&board)
{
	m_icon.setFillColor(sf::Color(160, 169, 184));
}

void Player::move(float deltaTime)
{
	m_prevPos = m_icon.getPosition();
	m_icon.move(m_direction * m_speedPerSecond * deltaTime);
}

void Player::choosePlayer()
{
	m_icon.setFillColor(sf::Color::White);
}

void Player::unchoosePlayer()
{
	m_icon.setFillColor(sf::Color(160, 169, 184));
}

void Player::handleCollision(GameObject& object)
{
    if (&object == this)
        return;

    object.handleCollision(*this);
}

void Player::handleCollision(Player& player)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Wall& wall)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Ork& ork)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Fire& fire)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Key& key)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Teleport& teleport)
{
    ResourcesManager::instance().playSound(Sounds::teleport);

    auto pos = teleport.getPosition();
    auto nextPos = m_board->getSecTeleport(pos);

    if (m_direction == sf::Vector2f(-1, 0))
    {
        m_icon.setPosition(sf::Vector2f(nextPos.x - m_icon.getSize().x, nextPos.y));
    }

    if (m_direction == sf::Vector2f(1, 0))
    {
        m_icon.setPosition(sf::Vector2f(nextPos.x + m_icon.getSize().x, nextPos.y));
    }

    if (m_direction == sf::Vector2f(0, 1))
    {
        m_icon.setPosition(sf::Vector2f(nextPos.x , nextPos.y + m_icon.getSize().y));
    }

    if (m_direction == sf::Vector2f(0, -1))
    {
        m_icon.setPosition(sf::Vector2f(nextPos.x, nextPos.y - m_icon.getSize().y));
    }
}

void Player::handleCollision(Throne& throne)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Gate& gate)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(Dwarf& dwarf)
{
    m_icon.setPosition(m_prevPos);
}

void Player::handleCollision(GiftKillDwarves& gift)
{
    ResourcesManager::instance().playSound(Sounds::killDwarfes);
    gift.needToActivate();
}

void Player::handleCollision(BadGift& gift)
{
    ResourcesManager::instance().playSound(Sounds::decTime);
    gift.needToActivate();
}

void Player::handleCollision(GiftTime& gift)
{
    ResourcesManager::instance().playSound(Sounds::incTime);
    gift.needToActivate();
}