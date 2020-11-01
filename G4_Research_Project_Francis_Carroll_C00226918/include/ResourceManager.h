#ifndef RESOURCEMANAGER
#define RESOURCEMANAGER

#include <string>
#include <Thor/Resources.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "LevelLoader.h"

using namespace std;
using namespace sf;

class ResourceManager
{
public:
	static void loadResources(shared_ptr<LevelData> t_data);
	static shared_ptr<thor::ResourceHolder<Texture, string>> m_textureHolder;
	static shared_ptr < thor::ResourceHolder<Font, string>> m_fontHolder;
	static shared_ptr < thor::ResourceHolder<SoundBuffer, string>> m_audioHolder;
private:
	static void loadTextures(shared_ptr<LevelData> t_data);
	static void loadAudio(shared_ptr<LevelData> t_data);
	static void loadFonts(shared_ptr<LevelData> t_data);
};

#endif