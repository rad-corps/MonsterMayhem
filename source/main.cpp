//////////////////////////////////////////////////////////////////////////
//\ Monster Mayhem
/////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "OuterLoop.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "FileSettings.h"
#include <fstream>
#include <sstream>
#include <string>
#include "sound.h"
#include <windows.h>
#include <Lmcons.h>



string CreateTimeString()
{
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
	stringstream ss;
	ss << (now->tm_year + 1900) << '-' 
         << (now->tm_mon + 1) << '-'
         <<  now->tm_mday << '-'
		 << now->tm_hour << '-'
		 << now->tm_min;

	return ss.str();
}

int main( int argc, char* argv[] )
{	

	{
		srand (time(NULL));
		FileSettings::LoadIniFile();
		Sound::Initialise();

		//get username
		char username[UNLEN+1];
		DWORD username_len = UNLEN+1;
		GetUserName(username, &username_len);

		std::ofstream out;
		if ( FileSettings::GetBool("REDIRECT_OUT") )
		{		
			//create output file name
			string outputFileName = "log\\";
			outputFileName += username;		
			outputFileName += CreateTimeString();
			outputFileName += ".log";
			FileSettings::AddStringValue("OUT_LOG", outputFileName);

			//redirect console output to file
			out = std::ofstream(FileSettings::GetString("OUT_LOG"));	
			std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
			std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out.txt!
			cout << "Output redirected to: " << FileSettings::GetString("OUT_LOG") << endl;
			cout << "Username: " << username << endl;
		}

		OuterLoop monsterMayhem;
		monsterMayhem.Go();	
	} //let the out stream go out of scope

	//if ( FileSettings::GetBool("UPLOAD_USAGE") ) 
	//{
	//	//upload the file
	//	string curlCommand;
	//	curlCommand += "log\\curl -u \"mmplaytest@adamhportfolio.com:o9HV&vCwArHL\" -v -T ";
	//	curlCommand += FileSettings::GetString("OUT_LOG");
	//	curlCommand += " ftp://209.236.127.138";
	//	system(curlCommand.c_str());
	//}
	Shutdown();
	return 0;
}