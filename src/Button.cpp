#include "Button.h"
#include "resourcesManager.h"

Button::Button()
	: m_button(sf::Vector2f(10,10))
{}

Button::Button(sf::Vector2f buttonPos, sf::Vector2f textPos, sf::Vector2f buttonSize, std::string buttonName, int textSize)
	: m_buttonSize(buttonSize)
{
	m_button.setSize(m_buttonSize);
	m_button.setTexture(ResourcesManager::instance().getBackground(Backgrounds::button));
	m_button.setPosition(buttonPos);
	m_button.setOrigin(m_buttonSize.x / 2, m_buttonSize.y / 2);

	m_buttonText.setFont(*ResourcesManager::instance().getFont());
	m_buttonText.setString(buttonName);
	m_buttonText.setCharacterSize(textSize);
	m_buttonText.setPosition(textPos);
	m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 2);
}

void Button::setButtonSize(sf::Vector2f buttonSize)
{
	m_button.setSize(buttonSize);
}

void Button::setScaleButon(sf::Vector2f scale)
{
	m_button.setScale(scale);
}

void Button::printButton(sf::RenderWindow& window)
{
	window.draw(m_button);
	window.draw(m_buttonText);
}

bool Button::contain(sf::Vector2f location) 
{
	return m_button.getGlobalBounds().contains(location);
}

void Button::changeText(std::string text)
{
	m_buttonText.setString(text);
	m_buttonText.setOrigin(m_buttonText.getGlobalBounds().width / 2, m_buttonText.getGlobalBounds().height / 2);
}

sf::Vector2f Button::getSize() const
{
	return m_button.getSize();
}

void Button::changeTexture(Backgrounds index)
{
	m_button.setTexture(ResourcesManager::instance().getBackground(index));
}