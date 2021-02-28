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

	t_bsp->m_bspDepth = t_bspNode["bsp_depth"].as<int>();

	t_bsp->m_renderBSP = t_bspNode["render_bsp"].as<bool>();

	t_bsp->m_renderCorridor = t_bspNode["render_corridors"].as<bool>();

	t_bsp->m_renderRooms = t_bspNode["render_rooms"].as<bool>();

	t_bsp->m_heightConstraint.x = t_bspNode["height_width_maximum"]["hm"].as<float>();
	t_bsp->m_heightConstraint.y = t_bspNode["height_width_maximum"]["hw"].as<float>();
	t_bsp->m_widthConstraint.x = t_bspNode["height_width_maximum"]["wm"].as<float>();
	t_bsp->m_widthConstraint.y = t_bspNode["height_width_maximum"]["ww"].as<float>();
}

void operator >> (const YAML::Node& t_caNode, shared_ptr<CAS> t_ca)
{
	t_ca->m_chanceToBecomeWall = t_caNode["chance_to_become_wall"].as<float>();

	t_ca->m_caStartingPosition.x = t_caNode["ca_starting_position"]["x"].as<float>();
	t_ca->m_caStartingPosition.y = t_caNode["ca_starting_position"]["y"].as<float>();

	t_ca->m_caGridSize.x = t_caNode["ca_grid_size"]["x"].as<float>();
	t_ca->m_caGridSize.y = t_caNode["ca_grid_size"]["y"].as<float>();

	t_ca->m_cellCount.x = t_caNode["ca_cell_count"]["row"].as<float>();
	t_ca->m_cellCount.y = t_caNode["ca_cell_count"]["col"].as<float>();

	t_ca->m_floorToWallConversion = t_caNode["floor_to_wall_conversion"].as<int>();

	t_ca->m_wallToFloorConversion = t_caNode["wall_to_floor_conversion"].as<int>();

	t_ca->m_iterations = t_caNode["iterations"].as<int>();

	t_ca->m_maxCaveSize = t_caNode["max_cave_size"].as<int>();

	t_ca->m_recursiveDepth = t_caNode["recursive_depth"].as<int>();
}

void operator >> (const YAML::Node& levelNode, shared_ptr<BSPData> level)
{
	levelNode["bsp"] >> level->m_bsp;
}

void operator >> (const YAML::Node& levelNode, shared_ptr<CAData> level)
{
	levelNode["ca"] >> level->m_ca;
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

void LevelLoader::load(string t_filename, shared_ptr<CAData> t_data)
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