#include "Menu.h"
#include "Macros.h"
#include "Window.h"
#include "resourcesManager.h"

Menu::Menu()
	: m_lastHoverd(0), m_helpPressed(false)
{
	loadButtonMenu();

	m_background.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_background.setTexture(ResourcesManager::instance().getBackground(Backgrounds::menu));

	m_help.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_help.setTexture(ResourcesManager::instance().getBackground(Backgrounds::help));
}

void Menu::menuEvent(sf::RenderWindow &window, Window& classWindow)
{
	if (m_helpPressed)
		printHelp(window);
	else
		printMenu(window);

	if (auto event = sf::Event{}; window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window.close();
			break;

		case sf::Event::MouseMoved:
			handleHover(window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }));
			break;

		case sf::Event::MouseButtonReleased:
			handleClick(sf::Vector2f(event.mouseButton.x, event.mouseButton.y), window, classWindow);
			break;
		}
	}
}

void Menu::loadButtonMenu()
{
	for (int i = 0; i < buttonNum; ++i)
	{
		m_menuButtons[i] = Button(buttonlocation(i), textlocation(i), m_buttonSize, m_menuButtonName[i], 55);
	}
}

void Menu::printMenu(sf::RenderWindow &window)
{
	window.draw(m_background);
	for (int i = 0; i < buttonNum - 1; ++i)
	{
		m_menuButtons[i].printButton(window);
	}
	window.display();
}

void Menu::handleHover(const sf::Vector2f location)
{
	sf::Vector2f size = m_menuButtons[m_lastHoverd].getSize();
	m_menuButtons[m_lastHoverd].setScaleButon(sf::Vector2f(1, 1));
	
	for (int i = 0; i < buttonNum; ++i)
	{
		if (m_menuButtons[i].contain(location))
		{
			auto size = m_menuButtons[i].getSize();
			m_menuButtons[i].setScaleButon(sf::Vector2f(1.2, 1.2));
			m_lastHoverd = i;
		}
	}
}

void Menu::handleClick(const sf::Vector2f location, sf::RenderWindow& window, Window& classWindow)
{
	int option = -1;
	for (int i = 0; i < buttonNum; ++i)
	{
		if (m_menuButtons[i].contain(location))
			option = i;
	}

	switch (option)
	{
	case StartGame:
		if (!m_helpPressed)
		{
			classWindow.setStartPressed();
			m_menuButtons[StartGame].changeText("CONTINUE");
		}
		break;

	case Help:
			m_helpPressed = true;
		break;

	case Exit:
		if (!m_helpPressed)
			window.close();
		break;

	default:
		m_helpPressed = false;
		break;
	}
}

sf::Vector2f Menu::buttonlocation(int i)
{
	return sf::Vector2f(1000, 350 + i * 160);
}

sf::Vector2f Menu::textlocation(int i)
{
	return sf::Vector2f(1000, 340 + i * 160);
}

void Menu::printHelp(sf::RenderWindow& window)
{
	window.clear();
	window.draw(m_help);
	window.display();
}