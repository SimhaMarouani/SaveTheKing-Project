#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Macros.h"

const int numOfElements = 14;
const int numOfTextures = 8;
const int numOfSounds = 8;

class ResourcesManager
{
public:
	static ResourcesManager& instance();
	const sf::Texture* getIcon(Elements obj) const;
	sf::Texture* getBackground(Backgrounds index);
	const sf::Font* getFont() const;
	std::string getLevelName(int index);
	int numOfLevels();
	void playSound(Sounds index);
	const sf::SoundBuffer* getGameSoundBuffer() const;

private:	
	ResourcesManager();
	ResourcesManager(const ResourcesManager&) = delete;
	ResourcesManager& operator=(const ResourcesManager&) = delete;
	void readLevel();

	sf::Font m_font;

	sf::Texture m_backgroundTextures[numOfTextures];
	std::string m_fileBackground[numOfTextures]{ "Menu.png", "GameBackground.png", "win.png", "Lose.png", "Help.png", "Button.png", "Reload.png", "SoundOnOff.png"};
	
	sf::SoundBuffer m_soundBuffer[numOfSounds];
	std::string m_soundFileNames[numOfSounds] = {"GameSound", "punch", "Teleport", "DecTime", "IncTime", "KillDwarfes", "Fire", "Win"};
	sf::Sound m_Sound[numOfSounds];

	std::vector <std::string> m_levels;
	
	sf::Texture m_textures[numOfElements];
	std::string m_fileNames[numOfElements] = {"King.png", "Mage.png", "Warrior.png", "Thief.png", "Dwarf.png", "Teleport.png",
											"Throne.png", "Fire.png", "Wall.png", "Ork.png", "Key.png", "Gift.png", "Gate.png", "ThiefKey.png"};
};

