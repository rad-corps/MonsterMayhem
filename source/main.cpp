//////////////////////////////////////////////////////////////////////////
//\ Monster Mayhem
/////////////////////////////////////////////////////////////////////////
#include "AIE.h"
#include "OuterLoop.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

int main( int argc, char* argv[] )
{		
	srand (time(NULL));
	OuterLoop monsterMayhem;
	monsterMayhem.Go();	
	Shutdown();
	return 0;
}
