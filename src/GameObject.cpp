#include "Macros.h"
#include "GameObject.h"
#include "resourcesManager.cpp"

GameObject::GameObject(Elements object, sf::Vector2f position, sf::Vector2f size)
{
	m_icon.setTexture(ResourcesManager::instance().getIcon(object));

	m_icon.setSize(size);
	m_icon.setPosition(position);
}

bool GameObject::checkCollision(GameObject& obj)
{
	if (&obj == this) return false;
	return m_icon.getGlobalBounds().intersects(obj.m_icon.getGlobalBounds()); 
}

void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_icon);
}