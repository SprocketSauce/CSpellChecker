/*
 * FILE: config.c
 * AUTHOR: Jack McNair 18927430
 * LAST MOD: 18/10/2017
 *
 * Contains functionality for creating Config structs and reading .spellconf files.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

/* STATIC METHOD DECLARATIONS */
static void readConfig( Config* );

/*
 * getConfig
 *
 * Creates and returns a struct containing the contents of a configuration file. The first time this
 * function is called, the .spellconf file is read and saved to static memory. Every subsequent call
 * simply returns the config struct that was saved to static memory. If the .spellconf file cannot
 * be read, or is missing fields, the default configuration is using "words" as the dictionary, 3 as
 * the maximum difference and autocorrect off.
 *
 * RETURNS:
 * 	A Config struct containing the contents of a settings file
 */
Config* getConfig( void )
{
	static Config* config = NULL; /* static, so the file is only read once */
	
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

/*
 * readConfig
 *
 * Reads a configuration file, assigning the read information to the input Config struct.
 *
 * INPUTS:
 * 	config - The struct to assign the read information to
 */
static void readConfig( Config* config )
{
	int read;
	char setting[14], value[41];
	FILE* file = fopen( ".spellconf", "r" );

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

		if ( ferror( file ) )
		{
			perror( "Error reading .spellconf" );
		}
		else
		{
			printf( "CONFIG FILE READ\n" );
		}

		fclose( file );
	}
}

