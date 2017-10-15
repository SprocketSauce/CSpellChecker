#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "checkWord.h"
#include "check.h"

int main( int argc, char* argv[] )
{
	char** dict;
	int dictLen;
	readDictionary( &dict, &dictLen );
	return 0;
}

/*
int checkDif( char* word, char* suggestion )
{

}
*/

void readDictionary( char*** dict, int* dictLen )
{
	FILE* file;
	int i, lineLen;
	char line[46]; /* Longest word in the dictionary is 45 characters */

	file = fopen( "words", "r" );
	if ( file == NULL )
	{
		perror("Error opening dictionary");
	}
	else
	{
		*dictLen = getNumLines( file );
		fseek( file, 0, SEEK_SET );
		
		*dict = (char**)malloc( *dictLen * sizeof(char*) );

		for ( i = 0; i < *dictLen; i++ )
		{
			fgets( line, 46, file );
			lineLen = strlen( line );
			(*dict)[i] = (char*)malloc( lineLen * sizeof(char) );
			strncpy( (*dict)[i], line, lineLen );
			printf( "Printing line: " );
			printf( (*dict)[i] );
			lineLen = strlen( (*dict)[i] );
			printf( "Line length: %d\n", lineLen );
		}

		printf( *dict[0] );
	}
}

int getNumLines( FILE* file )
{
	char ch;
	int lines = 0;
	
	do
	{
		ch = fgetc( file );
		if ( ch == '\n' )
		{
			lines++;
		}
	} while ( ch != EOF );

	return lines;
}
