#pragma once
#include <SFML/Graphics.hpp>

//grapics
const int WINDOW_WIDTH = 1600;
const int WINDOW_HEIGHT = 900;
const int BOARD_SIZE = 860;
const int BAR_WIDTH = 300;

const int xStartBoard = 395;
const int yStartBoard = 40;

const int CHAR_SIZE = 30;

//moving statistics
const float BASE_SPEED = 130.0;
const float STEP = 30.0;

//for functions
const float SIGMA = 4.0;
const int DELTA_TIME = 5;

const char TELEPORT_C = 'X', 
			THRONE_C = '@',
			EMPTY_C = ' ',
			FIRE_C = '*',
			WALL_C = '=',
			GATE_C = '#',
			ORK_C = '!',
			DWARF_C = '^',
			KEY_C = 'F',
			GIFT_C = 'G',
			KING_C = 'K',
			THIEF_C = 'T',
			MAGE_C = 'M',
			WARRIOR_C = 'W';

const sf::Vector2f STAND = { 0,0 };
const sf::Vector2f DirectionVec[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

enum class Elements
{
	king, mage, warrior, thief, dwarf, teleport,
	throne, fire, wall, ork, key, gift, gate, thiefKey
};

enum class Backgrounds
{
	menu, game, win, lose, help, button, reload, music
};

enum class Sounds
{
	gameSound, killOrk, teleport, decTime, incTime, killDwarfes, fire, win
};

// add enum to sounds

enum class Direction
{
	Left, Right, Up, Down, 
};

struct Teleports
{
	sf::Vector2f TelA, 
			  	TelB;
};