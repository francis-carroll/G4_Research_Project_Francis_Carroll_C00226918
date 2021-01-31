#include "LevelLoader.h"

void operator >> (const YAML::Node& t_bspNode, shared_ptr<BSP> t_bsp)
{
	t_bsp->m_roomPadding = t_bspNode["room_size_padding"].as<float>();

	t_bsp->m_roomPositionPadding = t_bspNode["room_position_padding"].as<float>();

	t_bsp->m_maxRoomSize.x = t_bspNode["max_room_size"]["x"].as<float>();
	t_bsp->m_maxRoomSize.y = t_bspNode["max_room_size"]["y"].as<float>();

	t_bsp->m_minRoomSize.x = t_bspNode["min_room_size"]["x"].as<float>();
	t_bsp->m_minRoomSize.y = t_bspNode["min_room_size"]["y"].as<float>();

	t_bsp->m_bspStartingPosition.x = t_bspNode["bsp_starting_position"]["x"].as<float>();
	t_bsp->m_bspStartingPosition.y = t_bspNode["bsp_starting_position"]["y"].as<float>();

	t_bsp->m_roomConnectionOffset = t_bspNode["room_connection_offset"].as<float>();

	t_bsp->m_roomConnectionOffsetHW = t_bspNode["room_connection_offset_hw"].as<float>();

	t_bsp->m_roomConnectionDistance = t_bspNode["room_connection_distance"].as<float>();

	t_bsp->m_bspAreaSize.x = t_bspNode["bsp_area_size"]["x"].as<float>();
	t_bsp->m_bspAreaSize.y = t_bspNode["bsp_area_size"]["y"].as<float>();

	t_bsp->m_bspDepth = t_bspNode["bsp_depth"].as<float>();
}

void operator >> (const YAML::Node& levelNode, shared_ptr<BSPData> level)
{
	levelNode["bsp"] >> level->m_bsp;
}

void LevelLoader::load(string t_filename, shared_ptr<BSPData> t_data)
{
	std::stringstream ss;
	ss << ".\\resources\\yaml\\";
	ss << t_filename;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("File: " + ss.str() + " not found");
			Error::logError(message);
			throw std::exception(message.c_str());
		}
		baseNode >> t_data;
	}
	catch (YAML::ParserException& e)
	{
		std::string message(e.what());
		message = "YAML Parser Error: " + message;
		Error::logError(message);
		throw std::exception(message.c_str());
	}
	catch (std::exception& e)
	{
		std::string message(e.what());
		message = "Unexpected Error: " + message;
		Error::logError(message);
		throw std::exception(message.c_str());
	}
}