#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class Window;

#define buttonNum 4

enum Function{StartGame, Help, Exit};

class Menu {
public:
	Menu();

	void menuEvent(sf::RenderWindow& window, Window& classWindow);
	void printMenu(sf::RenderWindow& window);

private:
	void handleHover(const sf::Vector2f location);
	void handleClick(const sf::Vector2f location, sf::RenderWindow& window, Window& classWindow);
	void loadButtonMenu();
	void printHelp(sf::RenderWindow& window);

	/*     background         */
	sf::RectangleShape m_background;

	/*       buttons         */
	std::string m_menuButtonName[buttonNum] = {"START" ,"HELP", "EXIT"};
	Button m_menuButtons[buttonNum];
	sf::Vector2f buttonlocation(int i);
	sf::Vector2f textlocation(int i);
	sf::Vector2f m_buttonSize = sf::Vector2f(350, 120);

	/*       help         */
	sf::RectangleShape m_help;
	bool m_helpPressed;

	int m_fontSize;
	int m_lastHoverd;

};