#include "Board.h"
#include "Controller.h"
#include <typeinfo>

Board::Board() 
: m_height(10), m_width(10), m_initLevelTime(-1)
{}

void Board::loadLevel(int level, Controller& controller)
{
	m_initiateGiftKillDwarf = false;
	m_boardVec.clear();
	m_staticObj.clear();
	m_gifts.clear();

	setLevel(ResourcesManager::instance().getLevelName(level));
	createObject(controller);
}

void Board::setLevel(std::string levelFile/*, float tileSize*/)
{
	auto file = std::ifstream(levelFile + ".txt");

	if (!file.is_open())
		exit(EXIT_FAILURE);

	file >> m_height >> m_width >> m_initLevelTime;
	
	m_tileSize = (WINDOW_HEIGHT) / (std::max(m_width, m_height) + 0.5);
	
	m_xStartBoard = (WINDOW_WIDTH - (m_tileSize + 4) * m_width + BAR_WIDTH) / 2;
	m_yStartBoard = (WINDOW_HEIGHT - (m_tileSize + 4) * m_height) / 2;

	m_boardWidth = (m_tileSize + 4) * m_width;
	m_boardHeight = (m_tileSize + 4) * m_height;

	m_gameBoard.setSize(sf::Vector2f(m_boardWidth, m_boardHeight));
	m_gameBoard.setPosition(sf::Vector2f(m_xStartBoard, m_yStartBoard));
	m_gameBoard.setFillColor(sf::Color(255, 255, 255, 150));
	
	fileToVec(file);
	readTeleports(file);
}

void Board::fileToVec(std::ifstream& file)
{
	auto line = std::string();
	getline(file, line);

	for (int row = 0; row < m_height; row++)
	{
		getline(file, line);
		m_boardVec.push_back(line);
	}
}

void Board::createObject(Controller& controller)
{
	sf::Vector2f position;

	m_size = sf::Vector2f(m_tileSize, m_tileSize);

	//convert a location in a char vector to a location on the window
	for (int row = 0; row < m_height; row++)
	{
		for (int col = 0; col < m_width; col++)
		{
			char playerChar = getChar(row, col);

			if (playerChar == EMPTY_C)
				continue;

			position.x = m_xStartBoard + (m_tileSize + 4) * col;
			position.y = m_yStartBoard + (m_tileSize + 4) * row;


			if (isStaticObj(playerChar))
				createStaticObject(playerChar, position, m_size);

			else
				controller.createMovingObject(playerChar, position, m_size);
		}
	}
}

bool Board::isStaticObj(char object) const
{
	if (object != KING_C && object != MAGE_C && object != THIEF_C && object != WARRIOR_C && object != DWARF_C)
		return true;
	return false;
}

int Board::getRowSize(int index) const
{
	return m_boardVec[index].size();
}

void Board::createStaticObject(char type, sf::Vector2f position, sf::Vector2f size)
{
	switch (type)
	{
	case WALL_C:
		m_staticObj.push_back(std::make_unique<Wall>(position, size));
		break;
	case GATE_C:
		m_staticObj.push_back(std::make_unique<Gate>(position, size));
		break;
	case TELEPORT_C:
		m_staticObj.push_back(std::make_unique<Teleport>(position, size));
		break;
	case THRONE_C:
		m_staticObj.push_back(std::make_unique<Throne>(position, size));
		break;
	case ORK_C:
		m_staticObj.push_back(std::make_unique<Ork>(position, size, *this));
		break;
	case FIRE_C:
		m_staticObj.push_back(std::make_unique<Fire>(position, size));
		break;

	case GIFT_C:
		if (!m_initiateGiftKillDwarf)
		{
			m_gifts.push_back(std::make_unique<GiftKillDwarves>(position, size));
			m_initiateGiftKillDwarf = true;

			break;
		}
		
		switch (m_gifts.size() % 2)
		{
		case 0:
			m_gifts.push_back(std::make_unique<GiftTime>(position, size));
			break;
		case 1:
			m_gifts.push_back(std::make_unique<BadGift>(position, size));
			break;
		}
		break;
	}
}

char Board::getChar(int row, int col) const
{
	return m_boardVec[row][col];
}

void Board::draw(sf::RenderWindow& window)
{
	window.draw(m_gameBoard);

	for (int i = 0; i < m_staticObj.size(); ++i)
	{
		m_staticObj[i]->draw(window);
	}
	
	for (int i = 0; i < m_gifts.size(); ++i)
	{
		m_gifts[i]->draw(window);
	}
}

int Board::getInitLevelTime() const
{
	return m_initLevelTime;
}

void Board::collision(GameObject& gameObj, Controller &controller)
{
	for (int i = 0; i < m_staticObj.size(); ++i)
	{
		if (gameObj.checkCollision(*m_staticObj[i]))
			m_staticObj[i]->handleCollision(gameObj);

		for (int j = 0; j < controller.numOfDwarves(); ++j)
			if (controller.getDwarf(j).checkCollision(*m_staticObj[i]))
				(*m_staticObj[i]).handleCollision((controller.getDwarf(j)));
	}

	// collision with gifts
	for (int i = 0; i < m_gifts.size(); ++i)
	{
		if(gameObj.checkCollision(*m_gifts[i]))
			m_gifts[i]->handleCollision(gameObj);

		if (m_gifts[i]->isActive())
			m_gifts[i]->activateGift(controller);
	}

	std::erase_if(m_staticObj, [](const auto& objct) { return objct->needToDelete();});  // delete object after collision
	std::erase_if(m_gifts, [](const auto& gift) { return gift->needToDelete();});  // delete object after collision
}

void Board::dropKey(sf::Vector2f position)
{
	m_staticObj.push_back(std::make_unique<Key>(position, m_size));
}

void Board::readTeleports(std::ifstream& file)
{
	int numOfPairs, row, col;
	
	m_teleports.clear();

	file >> numOfPairs;

	for (int i = 0; i < numOfPairs; i++)
	{
		sf::Vector2f t;

		file >> row >> col;

		t.x = m_xStartBoard + (m_tileSize + 4) * col;
		t.y = m_yStartBoard + (m_tileSize + 4) * row;
		m_teleports.push_back(Teleports(t,sf::Vector2f()));

		file >> row >> col;

		t.x = m_xStartBoard + (m_tileSize + 4) * col;
		t.y = m_yStartBoard + (m_tileSize + 4) * row;

		m_teleports.back().TelB = t;
	}
}

sf::Vector2f Board::getSecTeleport(sf::Vector2f pos) const
{
	for (int i = 0; i < m_teleports.size(); i++)
	{
		if (m_teleports[i].TelA == pos)
			return m_teleports[i].TelB;

		else if (m_teleports[i].TelB == pos)
			return m_teleports[i].TelA;
	}
	return sf::Vector2f(0, 0);
}