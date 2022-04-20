#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Macros.h"
#include "movingInclude/Player.h"
#include "movingInclude/Dwarf.h"

#include <staticInclude/Ork.h>
#include <staticInclude/Fire.h>
#include <staticInclude/Wall.h>
#include <staticInclude/Teleport.h>
#include <staticInclude/Key.h>
#include <staticInclude/Throne.h>
#include <staticInclude/Gate.h>
#include <staticInclude/Key.h>
#include "staticInclude/StaticObjects.h"
#include "staticInclude/GiftKillDwarves.h"
#include "staticInclude/BadGift.h"
#include "staticInclude/GiftTime.h"

class Controller;

class Board 
{
public:
	Board();

	void loadLevel(int level, Controller& controller);
	void draw(sf::RenderWindow& window);
	void collision(GameObject& gameObj, Controller& controller);
	void dropKey(sf::Vector2f position);
	int getInitLevelTime() const;
	sf::Vector2f getSecTeleport(sf::Vector2f pos) const;

private:
	void fileToVec(std::ifstream &file);		//read a level
	void setLevel(std::string levelFile);
	void createObject(Controller& controller);
	void createStaticObject(char, sf::Vector2f, sf::Vector2f);
	char getChar(int, int) const;
	bool isStaticObj(char object) const;
	int getRowSize(int index) const;
	void readTeleports(std::ifstream& file);


	int m_height;
	int m_width;
	int m_initLevelTime;

	int m_xStartBoard;
	int m_yStartBoard;
	int m_boardWidth;
	int m_boardHeight;
	float m_tileSize;

	bool m_initiateGiftKillDwarf = false;
	int m_giftsCounter = 0;

	std::ifstream m_file;
	std::vector<std::string> m_boardVec;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObj;
	std::vector<std::unique_ptr<Gift>> m_gifts;
	std::vector<Teleports> m_teleports;

	sf::Vector2f m_size;
	
	sf::RectangleShape m_gameBoard;

	sf::Texture m_boardTexture;
};
