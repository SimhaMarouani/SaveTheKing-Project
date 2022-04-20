#include "resourcesManager.h"
#include <fstream>

ResourcesManager::ResourcesManager()
{
	if(!m_font.loadFromFile("Font.ttf"))
		exit(EXIT_FAILURE);

	for (int i = 0; i < numOfTextures; ++i)
	{
		if (!m_backgroundTextures[i].loadFromFile(m_fileBackground[i]))
			exit(EXIT_FAILURE);
	}

	for (int i = 0; i < numOfElements; ++i)
	{
		if (!m_textures[i].loadFromFile(m_fileNames[i]))
			exit(EXIT_FAILURE);
	}

	for (int i = 0; i < numOfSounds; ++i)
	{
		if(!m_soundBuffer[i].loadFromFile(m_soundFileNames[i] + ".wav"))
			exit(EXIT_FAILURE);

		m_Sound[i].setBuffer(m_soundBuffer[i]);
		m_Sound[i].setVolume(5);
	}

	readLevel();
}

ResourcesManager& ResourcesManager::instance()
{
	static ResourcesManager inst;
	return inst;
}

const sf::Texture* ResourcesManager::getIcon(Elements obj) const
{
	return &(m_textures[int(obj)]);
}

sf::Texture* ResourcesManager::getBackground(Backgrounds index)
{
	return &m_backgroundTextures[int(index)];
}

const sf::Font* ResourcesManager::getFont() const
{
	return &m_font;
}

void ResourcesManager::playSound(Sounds index)
{
	m_Sound[int(index)].play();
}

const sf::SoundBuffer* ResourcesManager::getGameSoundBuffer() const
{
	return &(m_soundBuffer[int(Sounds::gameSound)]);
}

void ResourcesManager::readLevel()
{
	auto levels = std::ifstream("LevelsNames.txt");
	if (!levels.is_open())
		exit(EXIT_FAILURE);

	std::string levelName;
	std::getline(levels, levelName);

	while (!levelName.empty())
	{
		m_levels.push_back(levelName);
		std::getline(levels, levelName);
	}

	levels.close();
}

std::string ResourcesManager::getLevelName(int index)
{
	return m_levels[((static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(index)) -1 )];
}

int ResourcesManager::numOfLevels()
{
	return m_levels.size();
}