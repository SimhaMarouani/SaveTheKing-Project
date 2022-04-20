#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

class Controller;
class Wall;
class Throne;
class Fire;
class Ork;
class Key;
class Gate;
class Dwarf;
class Teleport;
class Player;
class GiftKillDwarves;
class BadGift;
class GiftTime;

class GameObject
{
public:
    GameObject(Elements object, sf::Vector2f position, sf::Vector2f size);

    virtual ~GameObject() = default;

    bool checkCollision(GameObject& obj);
    void draw(sf::RenderWindow& window);

    virtual void handleCollision(GameObject&) = 0;
    virtual void handleCollision(Player&) = 0;
    virtual void handleCollision(Dwarf&) = 0;
    virtual void handleCollision(Wall&) = 0;
    virtual void handleCollision(Ork&) = 0;
    virtual void handleCollision(Fire&) = 0;
    virtual void handleCollision(Teleport&) = 0;
    virtual void handleCollision(Throne&) = 0;
    virtual void handleCollision(GiftKillDwarves&) = 0;
    virtual void handleCollision(Gate&) = 0;
    virtual void handleCollision(Key&) = 0; 

protected:
    sf::RectangleShape m_icon;
};