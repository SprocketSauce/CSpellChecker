#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "checkWord.h"
#include "check.h"
#include "linkedList.h"

int main( int argc, char* argv[] )
{
	ActionFunc func = &checkDif;
	char* testCheck[] = { "spefling", "checl" };
	char** dict;
	int dictLen;
	readDictionary( &dict, &dictLen );

	check( testCheck, 2, dict, dictLen, 3, func );

	return 0;
}


int checkDif( char* word, char* suggestion )
{
	printf( "\nWord: " );
	printf( word );
	printf( "\nSuggestion: " );
	printf( suggestion );

	return 0;
}


void readDictionary( char*** dict, int* dictLen )
{
	FILE* file;
	int i, lineLen;
	char* inWord, *end;
	char line[47]; /* Longest word in the dictionary is 45 characters */
	LinkedList* list;

	file = fopen( "words", "r" );
	if ( file == NULL )
	{
		perror("Error opening dictionary");
	}
	else
	{
		list = createList();
		*dictLen = 0;

		end = fgets( line, 47, file );
		while ( end != NULL )
		{
			*dictLen = *dictLen + 1;
			strtok( line, "\n" );
			lineLen = strlen( line );
			inWord = (char*)malloc( lineLen * sizeof(char) );
			strncpy( inWord, line, lineLen );
			insertLast( list, inWord );
			end = fgets( line, 47, file );
		}

		*dict = (char**)malloc( *dictLen * sizeof(char*) );

		for ( i = 0; i < *dictLen; i++ )
		{
			(*dict)[i] = removeFirst( list );
		}

		freeList( list );

		if ( ferror( file ) )
		{
			perror( "Error reading file" );
		}

		fclose( file );
	}
}

int getNumLines( FILE* file )
{
	char ch;
	int lines = 1;
	
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
