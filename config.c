#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

static void readConfig( Config* );

Config* getConfig( void )
{
	static Config* config = NULL;
	
	if ( config == NULL )
	{
		config = (Config*)malloc( sizeof(Config) );

		strcpy( config -> dict, "words" );
		config -> maxDif = 3;
		config -> autoCorrect = 0;

		readConfig( config );
	}

	return config;
}

static void readConfig( Config* config )
{
	int read;
	char setting[14], value[41];
	FILE* file = fopen( ".spellconf", "r" );

	printf( "READING CONFIG FILE\n" );

	if ( file == NULL )
	{
		perror( "Error opening .spellconf" );
	}
	else
	{
		read = fscanf( file, "%s = %s\n", setting, value );
		
		while ( read != EOF )
		{
			if ( strcmp( setting, "dictfile" ) == 0 )
			{
				strcpy( config -> dict, value );
			}
			else if ( strcmp( setting, "maxdifference" ) == 0 )
			{
				config -> maxDif = atoi( value );
			}
			else if ( strcmp( setting, "autocorrect" ) == 0 )
			{
				if ( strcmp( value, "yes" ) == 0 )
				{
					config -> autoCorrect = 1;
				}
				else if ( strcmp( value, "no" ) == 0 )
				{
					config -> autoCorrect = 0;
				}
			}
			
			read = fscanf( file, "%s = %s\n", setting, value );
		}

		fclose( file );
	}
}

