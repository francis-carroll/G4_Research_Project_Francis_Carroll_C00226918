#ifndef ERRORLOGGING
#define ERRORLOGGING

#include <string>
#include <fstream>
#include <ctime>
#include <iostream>

using namespace std;

const string TARGET_DIR = "logs";
const string FILE_EXTENSION = ".txt";

static void logError(string t_errorMessage) 
{
	auto t = time(nullptr); tm now;
	//gets the current date and time
	localtime_s(&now, &t);

	//date
	string fileTitle = to_string(now.tm_year + 1900) + to_string(now.tm_mon + 1) + to_string(now.tm_mday);
	//time
	string fileHeader = to_string(now.tm_hour) + "H:" + to_string(now.tm_min) + "M:" + to_string(now.tm_sec) + "S";
	//filename and location
	string fileName = TARGET_DIR + "\\" + fileTitle + FILE_EXTENSION;

	fstream stream;

	stream.open(fileName, std::fstream::in | std::fstream::out | std::fstream::app);

	//if the stream isnt opened/doesnt exist
    if(!stream)
    {
		//creates the directory if it doesnt exist
        system("mkdir logs");

		//creates the file
        stream.open(fileName, fstream::in | fstream::out | fstream::trunc);
    }

	//appends the time and the error message to the file
	stream << fileHeader + ":\n		" + t_errorMessage + "\n";
	stream.close();
}

#endif