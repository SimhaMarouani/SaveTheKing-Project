#include "staticInclude/Ork.h"
#include "Board.h"

Ork::Ork(sf::Vector2f position, sf::Vector2f size, Board& board)
	:StaticObjects(Elements::ork, position, size)
{
	m_board = &board;
}

void Ork::DeleteObj()
{
	m_delete = true;
	m_board->dropKey(m_icon.getPosition());
}