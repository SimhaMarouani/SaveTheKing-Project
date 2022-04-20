#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "resourcesManager.h"
#include "Macros.h"

class Controller;

class Bar
{
public:
	Bar();
	~Bar();

	void draw(sf::RenderWindow &window);
	void updateLevel(int time, int level);
	bool timeOut() const;
	void decreaseTime();
	void increaseTime();
	void updateCurrPlayer(int player);
	void updadeThiefWithKey(bool hasKey);
	void stopTimer();
	void continueTimer();
	bool isTimerStopped() const;
	void startTimer();

private:
	void updateTime(float time);

	sf::Clock m_Timer;
	sf::Time m_stageTime;

	float m_stageTimeSec;

	bool m_timelessLevel;
	bool m_timeEnd;
	bool m_stopTimer;

	sf::RectangleShape m_barBackground;
	sf::RectangleShape m_currPlayerIcon;
	sf::RectangleShape m_thiefWithKey;

	sf::Text m_scoreText;
	sf::Text m_stageTimeText;
	sf::Text m_levelText;
};