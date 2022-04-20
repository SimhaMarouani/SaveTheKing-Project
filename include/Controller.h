#pragma once
#include <memory>
#include <vector>
#include "Bar.h"
#include "Board.h"
#include "Window.h"
#include "Macros.h"
#include "movingInclude/King.h"
#include "movingInclude/Mage.h"
#include "movingInclude/Thief.h"
#include "movingInclude/Warrior.h"

class Controller
{
public:
	Controller();
	void run();
	void createMovingObject(char type, sf::Vector2f position, sf::Vector2f);
	void draw(sf::RenderWindow &window); 

	void newLevel();
	bool getWinLevel();
	bool getLose();

	void decTime();
	void incTime();

	int numOfDwarves() const;
	void deleteDwarves();
	Dwarf& getDwarf(int index) const;
	
private:
	void handleCollision(GameObject& gameObject);
	void moveDwarfves(float deltaTime);
	sf::Keyboard::Key handleKey();
	int getCurrPlayer() const;
	bool thiefHasKey() const;


	Bar m_bar;
	Board m_board;
	Window m_window;

	int m_currPlayer;
	int m_currLevel;

	bool m_winLevel;
	bool m_initiate = true;
	
	std::unique_ptr<Player> m_movingObj[4]; 
	std::vector<std::unique_ptr<Dwarf>> m_dwarfves;
};
