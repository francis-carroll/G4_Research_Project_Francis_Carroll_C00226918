#ifndef LEVELLOADER
#define LEVELLOADER

#ifdef _DEBUG 
#include "include/yaml-cpp-d/yaml.h"
#else 
#include "include/yaml-cpp-r/yaml.h"
#endif 

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#include "LevelLoaderStructs.h"
#include "ErrorLogging.h"

using namespace std;

class LevelLoader
{
public:
	LevelLoader() = default;

	static void load(string t_filename, shared_ptr<BSPData> t_data);
	static void load(string t_filename, shared_ptr<CAData> t_data);
};

#endif