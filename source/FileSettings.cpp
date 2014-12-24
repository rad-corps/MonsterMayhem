//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// FileSettings.cpp
/////////////////////////////////////////////////////////////////////////

#include "FileSettings.h"
#include "IniFile.h"
#include <vector>
//#include "Consts.h"
//#include <Windows.h>

std::map<std::string, std::string> FileSettings::settingsMap;

void FileSettings::AddIntValue(std::string key_, int value_)
{
	settingsMap[key_] = to_string(value_);
}

void FileSettings::AddStringValue(std::string key_, std::string value_)
{
	settingsMap[key_] = value_;
}

bool FileSettings::GetBool(std::string key_)
{
	if ( settingsMap[key_] == "0" )
		return false;
	else
		return true;
}

float FileSettings::GetFloat(std::string key_)
{
	return std::stof(settingsMap[key_]);
}

int FileSettings::GetInt(std::string key_)
{
	return std::stoi(settingsMap[key_]);
}

std::string FileSettings::GetString(std::string key_)
{
	return settingsMap[key_];
}

void FileSettings::LoadIniFile()
{
	settingsMap.clear();

	const string INI_FILE_PATH = "./mm.ini";
	const string INI_SECTION = "game_globals";

	vector<CIniFile::Record> records = CIniFile::GetSection(INI_SECTION, INI_FILE_PATH);
	
	//put records in a map
	for (int i = 0; i < records.size(); ++i )
	{
		settingsMap[records[i].Key] = records[i].Value;
	}
}