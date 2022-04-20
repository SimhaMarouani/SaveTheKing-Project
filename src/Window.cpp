#include "Controller.h"
#include "Window.h"

Window::Window()
    : m_window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Save The King", sf::Style::Close | sf::Style::Titlebar)
{
    m_gameBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_gameBackground.setTexture(ResourcesManager::instance().getBackground(Backgrounds::game));

    m_winBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_winBackground.setTexture(ResourcesManager::instance().getBackground(Backgrounds::win));
    
    m_loseBackground.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    m_loseBackground.setTexture(ResourcesManager::instance().getBackground(Backgrounds::lose));

    auto reloadPos = sf::Vector2f(225, 690);
    m_reloadButton = Button(reloadPos, reloadPos, sf::Vector2f(100.f, 100.f), "" , 100);
    m_reloadButton.changeTexture(Backgrounds::reload);

    auto musicPos = sf::Vector2f(105, 690);
    m_musicButton = Button(musicPos, musicPos, sf::Vector2f(100.f, 100.f), "" , 100);
    m_musicButton.changeTexture(Backgrounds::music);

    m_gameSound.setBuffer(*(ResourcesManager::instance()).getGameSoundBuffer());
    m_gameSound.setVolume(3);
    m_gameSound.setLoop(true);
    m_gameSound.play();

    // set cute icon :)
    auto image = sf::Image{};
    image.loadFromFile("Icon.png");
    m_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
}

void Window::windowEvent(Controller& controller, Board& board, Bar& bar)
{
    if (m_startPressed)
        printStart(controller, board, bar);
    else
    {
        m_menu.menuEvent(m_window, *this);
        return;
    }

    m_winGame = controller.getWinLevel();
    m_loseGame = controller.getLose();
        
    if (auto event = sf::Event{}; m_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            m_window.close();
            break;
        case sf::Event::MouseButtonReleased:
            if (m_reloadButton.contain(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
                controller.newLevel();
            else if (m_musicButton.contain(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)))
            {
                if (m_gameSound.getStatus() == m_gameSound.Playing)
                    m_gameSound.stop();
                else
                    m_gameSound.play();
            }
            break;
        }
    }

    if (m_loseGame && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        controller.newLevel();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_winGame)
    {
        m_winGame = false;
        controller.newLevel();
    }
}

bool Window::isOpen()
{
    return m_window.isOpen();
}

void Window::printWindow()
{
    m_window.clear();
    m_menu.printMenu(m_window);
    m_window.display();
}

void Window::printStart(Controller& controller, Board &board, Bar& bar)
{
    m_window.draw(m_gameBackground);
    board.draw(m_window);
    controller.draw(m_window);
    bar.draw(m_window);
    m_reloadButton.printButton(m_window);
    m_musicButton.printButton(m_window);

    if(m_winGame)
      m_window.draw(m_winBackground);

    else if(m_loseGame)
        m_window.draw(m_loseBackground);

    m_window.display();
}

void Window::homeScreen()
{
    m_startPressed = false;
}
 
bool Window::getStartPressed() const
{
    return m_startPressed;
}

void Window::setStartPressed()
{
    m_startPressed = true;
}