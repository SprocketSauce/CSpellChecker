#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "checkWord.h"
#include "check.h"
#include "config.h"

int main( int argc, char* argv[] )
{
	Config* config;
	ActionFunc func = &checkDif;
	char** dict, **words;
	int dictLen, numWords;

	if ( argc == 2 )
	{
		config = getConfig();

		readText( config -> dict, &dict, &dictLen );
		printf( "DICTIONARY READ\n" );

		readText( argv[1], &words, &numWords );
		check( words, numWords, dict, dictLen, config -> maxDif, func );

		makeCorrections( argv[1], words, numWords );

		freeArray( words, numWords );
		freeArray( dict, dictLen );
		free( config );
	}

	return 0;
}


int checkDif( char* word, char* suggestion )
{
	int commit;
	Config* config;
	
	config = getConfig();

	if ( suggestion != NULL )
	{
		if ( config -> autoCorrect == 1 )
		{
			commit = 1;
		}
		else
		{
			printf( "\nPossible spelling error detected\n" );
			printf( "Original word: %s\n", word );
			printf( "Suggested word: %s \n", suggestion );

			commit = inputYN( "Accept changes? (y/n): " );
		}
	}
	else
	{
		commit = 0;
	}

	return commit;
}


void readText( char* filename, char*** words, int* numWords )
{
	FILE* file;
	int i, end;
	char word[46]; /* Longest word in the dictionary is 45 characters */
	LinkedList* list;

	file = fopen( filename, "r" );
	if ( file == NULL )
	{
		perror("Error opening dictionary");
	}
	else
	{
		list = createList();
		*numWords = 0;

		end = fscanf( file, "%s%*c", word );

		while ( end != EOF )
		{
			(*numWords)++;
			wordToList( word, list );
			end = fscanf( file, "%s%*c", word );
		}

		*words = (char**)malloc( *numWords * sizeof(char*) );

		for ( i = 0; i < *numWords; i++ )
		{
			(*words)[i] = removeFirst( list );
		}

		freeList( list );

		if ( ferror( file ) )
		{
			perror( "Error reading file" );
		}

		fclose( file );
	}
}

void wordToList( char word[], LinkedList* list )
{
	int wordLen;
	char* inWord;

	wordLen = strlen( word ) + 1;
	inWord = (char*)malloc( wordLen * sizeof(char) );
	strcpy( inWord, word );
	insertLast( list, inWord );
}

void makeCorrections( char* filename, char** words, int numWords )
{
	int i;
	FILE* file = fopen( filename, "w" );

	for ( i = 0; i < numWords; i++ )
	{
		fprintf( file, "%s ", words[i] );
	}

	fclose( file );
}

void freeArray( char** array, int numEntries )
{
	int i;

	for ( i = 0; i < numEntries; i++ )
	{
		free( array[i] );
	}

	free( array );
}

int inputYN( char* prompt )
{
	char sel;
	char result;
	
	printf( prompt );
	scanf( " %c", &sel );

	while ( sel != 'y' && sel != 'Y' && sel != 'n' && sel != 'N' )
	{
		printf( "Invalid input\n" );
		printf( prompt );
		scanf( " %c", &sel );
	}

	if ( sel == 'y' || sel == 'Y' )
	{
		result = 1;
	}
	else
	{
		result = 0;
	}

	return result;
}
