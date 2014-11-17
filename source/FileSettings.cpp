#include "FileSettings.h"
#include "IniFile.h"
#include <vector>
//#include "Consts.h"
//#include <Windows.h>

std::map<std::string, std::string> FileSettings::settingsMap;

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