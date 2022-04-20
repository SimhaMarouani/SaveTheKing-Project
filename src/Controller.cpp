#include "Controller.h"
#include "resourcesManager.h"
#include <typeinfo>

Controller::Controller() 
	:m_currLevel(1), m_winLevel(false), m_currPlayer(0)
{}

void Controller::run()
{
	sf::Clock clock;

	m_board.loadLevel(m_currLevel, *this);
	m_movingObj[m_currPlayer]->choosePlayer(); 

	while (m_window.isOpen())
	{
		if (m_initiate)
			m_bar.updateLevel(m_board.getInitLevelTime(), m_currLevel);	//Read the time from file

		if (m_window.getStartPressed() && m_bar.isTimerStopped())
			m_bar.continueTimer();

		m_bar.updateCurrPlayer(m_currPlayer);
		m_bar.updadeThiefWithKey(thiefHasKey());

		m_window.windowEvent(*this, m_board, m_bar);

		m_movingObj[m_currPlayer]->setDirection(handleKey());
		const auto deltaTime = clock.restart();
		m_movingObj[m_currPlayer]->move(deltaTime.asSeconds());
		moveDwarfves(deltaTime.asSeconds());

		handleCollision(*m_movingObj[m_currPlayer]);
	}
}

bool Controller::thiefHasKey() const
{
	if (Player* player = dynamic_cast<Thief*>(m_movingObj[int(Elements::thief)].get()))
		return player->thiefHasKey();
}

void Controller::createMovingObject(char type, sf::Vector2f position, sf::Vector2f size)
{
	switch (type)
	{
	case KING_C:
		m_movingObj[int(Elements::king)] = (std::make_unique<King>(position, size, m_board));
		break;
	case MAGE_C:
		m_movingObj[int(Elements::mage)] = (std::make_unique<Mage>(position, size, m_board));
		break;
	case THIEF_C:
		m_movingObj[int(Elements::thief)] = (std::make_unique<Thief>(position, size, m_board));
		break;
	case WARRIOR_C:
		m_movingObj[int(Elements::warrior)] = (std::make_unique<Warrior>(position, size, m_board));
		break;
	case DWARF_C:
		m_dwarfves.push_back(std::make_unique<Dwarf>(position, size));
		break;
	}
}

void Controller::draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 4; ++i)
	{
		m_movingObj[i]->draw(window);
	}

	for (int i = 0; i < m_dwarfves.size(); ++i)
	{
		m_dwarfves[i]->draw(window);
	}
}

void Controller::handleCollision(GameObject& gameObject)
{
	for (int i = 0; i < 4; ++i)
	{
		if (gameObject.checkCollision(*m_movingObj[i]))
			gameObject.handleCollision(*m_movingObj[i]);

		for (int j = 0; j < m_dwarfves.size(); ++j)
		{
			if (m_dwarfves[j]->checkCollision(*m_movingObj[i]))
				m_dwarfves[j]->handleCollision(*m_movingObj[i]);

			if (m_movingObj[m_currPlayer]->checkCollision(*m_dwarfves[j]))
				m_movingObj[i]->handleCollision(*m_dwarfves[j]);
		}
	}

	m_board.collision(gameObject, *this);
}

void Controller::newLevel()
{
	m_dwarfves.clear();

	if (m_winLevel)
	{
		m_currLevel++;
		m_winLevel = false;
	}

	if (m_currLevel > ResourcesManager::instance().numOfLevels())
	{
		m_currLevel = 1;
		m_window.homeScreen();
	}

	m_board.loadLevel(m_currLevel, *this);
	m_movingObj[m_currPlayer]->choosePlayer();
	m_bar.updateLevel(m_board.getInitLevelTime(), m_currLevel);
	m_initiate = true;
}

bool Controller::getWinLevel()
{
	if (Player* player = dynamic_cast<King*>(m_movingObj[int(Elements::king)].get()))
		m_winLevel = player->getKingOnThrone();
		
	return m_winLevel;
}

void Controller::moveDwarfves(float deltaTime)
{
	if (m_initiate && m_window.getStartPressed()) // make the dwarves collide
	{
		for (int i = 0; i < m_dwarfves.size(); i++)
			m_dwarfves[i]->setDirection(sf::Keyboard::Right);
			
		m_initiate = false;
	}

	for (int i = 0; i < m_dwarfves.size(); i++)
	{
		m_dwarfves[i]->move(deltaTime);
	}
}

int Controller::numOfDwarves() const
{
	return m_dwarfves.size();
}

Dwarf& Controller::getDwarf(int index) const
{
	return *m_dwarfves[index];
}

void Controller::deleteDwarves()
{
	m_dwarfves.clear();
} 

void Controller::decTime()
{
	m_bar.decreaseTime();
}

void Controller::incTime()
{
	m_bar.increaseTime();
}

int Controller::getCurrPlayer() const
{
	return m_currPlayer;
}

sf::Keyboard::Key Controller::handleKey()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_bar.stopTimer();
		m_window.homeScreen();
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		return sf::Keyboard::Left;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		return sf::Keyboard::Right;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		return sf::Keyboard::Down;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		return sf::Keyboard::Up;

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		// change player when press 'P'
		m_movingObj[m_currPlayer]->unchoosePlayer();
		m_currPlayer = (m_currPlayer + 1) % 4; // 4 = num of players 
		m_movingObj[m_currPlayer]->choosePlayer();
		while (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {}
	}

	return sf::Keyboard::T;
}

bool Controller::getLose()
{
	return (m_bar.timeOut() && !m_winLevel);
}