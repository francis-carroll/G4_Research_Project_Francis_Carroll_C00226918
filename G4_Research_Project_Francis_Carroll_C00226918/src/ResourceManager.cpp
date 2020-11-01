#include "ResourceManager.h"

shared_ptr <thor::ResourceHolder<sf::Texture, std::string>> ResourceManager::m_textureHolder;
shared_ptr <thor::ResourceHolder<sf::Font, std::string>> ResourceManager::m_fontHolder;
shared_ptr <thor::ResourceHolder<sf::SoundBuffer, std::string>> ResourceManager::m_audioHolder;

void ResourceManager::loadResources(shared_ptr<LevelData> t_data)
{
	try
	{
		loadTextures(t_data);
		loadAudio(t_data);
		loadFonts(t_data);
	}
	catch (thor::ResourceLoadingException& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}
}

void ResourceManager::loadTextures(shared_ptr<LevelData> t_data)
{
	//sample loading
	//m_textureHolder->acquire(t_data->fileID, thor::Resources::fromFile<sf::Texture>(t_data->filename));
}

void ResourceManager::loadAudio(shared_ptr<LevelData> t_data)
{
}

void ResourceManager::loadFonts(shared_ptr<LevelData> t_data)
{
}
