//////////////////////////////////////////////////////////////////////////
//\ Monster Mayhem
/////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "OuterLoop.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "FileSettings.h"

int main( int argc, char* argv[] )
{		
	srand (time(NULL));
	FileSettings::LoadIniFile();
	OuterLoop monsterMayhem;
	monsterMayhem.Go();	
	Shutdown();
	return 0;
}
