#include "LevelLoader.h"

void operator >> (const YAML::Node& t_playerNode, shared_ptr<PlayerData> t_player)
{
	t_player->m_playerSpriteFile = t_playerNode["filename"].as<std::string>();
}

void operator >> (const YAML::Node& levelNode, shared_ptr<LevelData> level)
{
	//levelNode["player"] >> level->m_player;
}

void LevelLoader::load(int nr, shared_ptr<LevelData> level)
{
	std::stringstream ss;
	ss << ".\\resources\\yaml\\level";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("File: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		throw std::exception(message.c_str());
	}
}