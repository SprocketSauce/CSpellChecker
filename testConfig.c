#include <stdio.h>
#include "config.h"

int main( int argc, char* argv[] )
{
	Config* config;

	config = getConfig();
	
	printf( "dict = %s\n", config -> dict );
	printf( "maxDif = %d\n", config -> maxDif );
	printf( "autoCorrect = %d\n", config -> autoCorrect );

	config = getConfig();

	return 0;
}
