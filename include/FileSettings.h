//////////////////////////////////////////////////////////////////////////
// Monster Mayhem
// Game Code By Adam Hulbert
// For AIE Advanced Diploma - Practice Production Term 4 2014
// 22/12/2014
// FileSettings.h
/////////////////////////////////////////////////////////////////////////

#pragma once

//A little helper for using CIniFile

#include <map>
#include <string>

//singleton settings class
class FileSettings
{

public:
	~FileSettings(void);
	static bool GetBool(std::string key_);
	static float GetFloat(std::string key_);
	static int GetInt(std::string key_);
	static std::string GetString(std::string key_);
	static void AddIntValue(std::string key_, int value_);
	static void AddStringValue(std::string key_, std::string value_);
	static void LoadIniFile();
	
private:
	FileSettings(void);	

	static std::map<std::string, std::string> settingsMap;
};

