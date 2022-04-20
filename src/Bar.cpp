#include "Bar.h"
#include "Controller.h"

Bar::Bar()
	: m_timelessLevel(false), m_timeEnd(false), m_stopTimer(false)
{
	m_barBackground.setSize(sf::Vector2f(BAR_WIDTH, WINDOW_HEIGHT));
	m_barBackground.setFillColor(sf::Color::White);

	this->m_levelText.setFont(*ResourcesManager::instance().getFont());
	this->m_levelText.setCharacterSize(CHAR_SIZE);
	this->m_levelText.setPosition(100, 140);
	this->m_levelText.setColor(sf::Color::White);

	this->m_stageTimeText.setFont(*ResourcesManager::instance().getFont());
	this->m_stageTimeText.setCharacterSize(CHAR_SIZE);
	this->m_stageTimeText.setPosition(45, 245);
	this->m_stageTimeText.setColor(sf::Color::White);

	m_currPlayerIcon.setSize(sf::Vector2f(94.f, 95.f));
	m_currPlayerIcon.setPosition(sf::Vector2f(115.f, 340.f));

	m_thiefWithKey.setSize(sf::Vector2f(105.f, 105.f));
	m_thiefWithKey.setPosition(sf::Vector2f(115.f, 490.f));
}

Bar::~Bar()
{}

void Bar::updateTime(float time)
{
	if (!m_timelessLevel)
	{
		m_stageTimeSec += time;
		m_stageTimeSec -= m_Timer.getElapsedTime().asSeconds() ;

		int leftMinutes = ((int)m_stageTimeSec) / 60;
		int leftSeconds = ((int)m_stageTimeSec) % 60;

		if (m_stageTimeSec <= -1)
			m_timeEnd = true;

		std::string minString = leftMinutes < 10 ? "0" + std::to_string(leftMinutes) : std::to_string(leftMinutes);
		std::string secString = leftSeconds < 10 ? "0" + std::to_string(leftSeconds) : std::to_string(leftSeconds);

		m_stageTimeText.setString("Time left: " + minString + ":" + secString);
	}
	else
	{
		m_stageTimeSec += 0;
		m_stageTimeSec += this->m_Timer.getElapsedTime().asSeconds();
		int minutesCounter = ((int)this->m_stageTimeSec) / 60;
		int secondsCounter = ((int)this->m_stageTimeSec) % 60;

		std::string minString = minutesCounter < 10 ? "0" + std::to_string(minutesCounter) : std::to_string(minutesCounter);
		std::string secString = secondsCounter < 10 ? "0" + std::to_string(secondsCounter) : std::to_string(secondsCounter);

		m_stageTimeText.setString("   Timer: " + minString + ":" + secString);
	}
	m_Timer.restart();
}

void Bar::draw(sf::RenderWindow &window)
{
	updateTime(0);
	window.draw(m_levelText);
	window.draw(m_stageTimeText);
	window.draw(m_currPlayerIcon);
	window.draw(m_thiefWithKey);
}

void Bar::updateLevel(int time, int level)
{
	m_timeEnd = false;
	if (time == -1) //if a timeless level
	{
		m_timelessLevel = true;
		m_stageTimeSec = 0;
		m_stageTimeSec++;
	}
	else
	{
		m_timelessLevel = false;
		m_stageTimeSec = time;
	}

	m_levelText.setString("Level: " + std::to_string(level));
	m_Timer.restart();
}

bool Bar::timeOut() const
{
	return m_timeEnd;
}

void Bar::decreaseTime()
{
	m_stageTimeSec -= m_stageTimeSec / 4;
}

void Bar::increaseTime()
{
	m_stageTimeSec += 15;
}

void Bar::updateCurrPlayer(int player)
{
	m_currPlayerIcon.setTexture(ResourcesManager::instance().getIcon(Elements(player)));
}

void Bar::updadeThiefWithKey(bool hasKey)
{
	if(hasKey)
		m_thiefWithKey.setTexture(ResourcesManager::instance().getIcon(Elements::thiefKey));
	else
		m_thiefWithKey.setTexture(ResourcesManager::instance().getIcon(Elements::thief));
}

void Bar::stopTimer()
{
	m_stopTimer = true;
}

void Bar::continueTimer()
{
	m_stopTimer = false;
	m_Timer.restart();
}

bool Bar::isTimerStopped() const
{
	return m_stopTimer;
}

void Bar::startTimer()
{
	m_Timer.restart();
}