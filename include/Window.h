#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Board.h"
#include "Bar.h"

class Controller;
 
class Window
{
public:
    Window();

    void windowEvent(Controller& controller, Board& board, Bar& bar);
    bool isOpen();
    void homeScreen();
    bool getStartPressed() const;
    void setStartPressed();

private:
    void printStart(Controller& controller, Board& board, Bar& bar);
    void printWindow();
   
    Menu m_menu;
 
    sf::RenderWindow m_window;
    sf::RectangleShape m_gameBackground;
    sf::RectangleShape m_winBackground;
    sf::RectangleShape m_loseBackground;
    Button m_reloadButton;
    Button m_musicButton;
    sf::Sound m_gameSound;

 
    bool m_startPressed = false;
    bool m_winGame = false;
    bool m_loseGame = false;
};