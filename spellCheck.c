/*
 * FILE: spellCheck.c
 * AUTHOR: Jack McNair 18927430
 * LAST MOD: 18/10/2017
 *
 * Contains the main method, as well as methods for reading and writing to files, taking user input,
 * deciding whether to commit a spelling change, and converting linked lists to arrays.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "check.h"
#include "config.h"
#include "linkedList.h"

/* STATIC METHOD DECLARATIONS */
static int commitChange( char*, char* );
static void readText( char*, char***, int* );
static void wordToList( char*, LinkedList* );
static void makeCorrections( char*, char**, int );
static void freeArray( char**, int );
static int inputYN( char* prompt );

/*
 * ===== MAIN =====
 * Runs the spellchecker on the file specified by the input argument.
 */
int main( int argc, char* argv[] )
{
	Config* config;
	ActionFunc func = &commitChange;
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
	else
	{
		printf( "Invalid number of input arguments" );
	}

	return 0;
}

/*
 * commitChange
 *
 * Decides whether or not to commit a suggested spelling correction. If autocorrect is on, the
 * correction is always made, otherwise the user is prompted. If no suggested word is provided,
 * no alteration is made.
 *
 * INPUTS:
 * 	word - The original word
 * 	suggested - The suggested spelling
 *
 * RETURNS:
 * 	1 if the change should be made, 0 otherwise.
 */
static int commitChange( char* word, char* suggestion )
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
			printf( "Suggested word: %s\n", suggestion );

			commit = inputYN( "Accept changes? (y/n): " );
		}
	}
	else
	{
		commit = 0;
	}

	return commit;
}

/*
 * readText
 *
 * Reads a text file, adding all the words of that text file to a string array. The number of words
 * in the file is written to the memory location specified by the input int pointer. The maximum length
 * of a word is 45 characters, words longer than this will be split up.
 *
 * Words are added to a linked list, then moved from that linked list to the array.
 *
 * INPUTS:
 * 	filename - The name of the file to be read
 * 	words - The string array to write to
 * 	numWords - Set to be equal to the number of words in the file
 */
static void readText( char* filename, char*** words, int* numWords )
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

		end = fscanf( file, "%45s%*c", word );

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

/*
 * wordToList
 *
 * Allocates memory equal to the length of a string, then adds that string to a linked list.
 *
 * INPUTS:
 *	word - The string to be added
 *	list - The linked list to be added to
 */
static void wordToList( char word[], LinkedList* list )
{
	int wordLen;
	char* inWord;

	wordLen = strlen( word ) + 1;
	inWord = (char*)malloc( wordLen * sizeof(char) );
	strcpy( inWord, word );
	insertLast( list, inWord );
}

/*
 * makeCorrections
 *
 * Writes an array of strings to a file, with whitespace between each entry.
 *
 * INPUTS
 * 	filename - The name of the file to be written to
 * 	words - The array of strings to write
 * 	numWords - The number of entries in the array
 */
static void makeCorrections( char* filename, char** words, int numWords )
{
	int i;
	FILE* file = fopen( filename, "w" );
	
	if ( file == NULL )
	{
		perror( "Error opening file" );
	}
	else
	{
		for ( i = 0; i < numWords; i++ )
		{
			fprintf( file, "%s ", words[i] );
		}

		if ( ferror( file ) )
		{
			perror( "Error writing to file" );
		}

		fclose( file );
	}
}

/*
 * freeArray
 *
 * Deallocates memory from every entry in a string array, then deallocates the array itself
 * 
 * INPUTS:
 * 	array - The string array to be freed
 * 	numEntries - The number of entries in that array
 */
static void freeArray( char** array, int numEntries )
{
	int i;

	for ( i = 0; i < numEntries; i++ )
	{
		free( array[i] );
	}

	free( array );
}

/*
 * inputYN
 *
 * Prompts the user to input 'Y' or 'N'. Returns true if the user inputs 'Y', false if the user
 * inputs 'N'. Loops if the user inputs anything else.
 *
 * INPUTS:
 * 	prompt - The prompt to be displayed to the user.
 *
 * RETURNS:
 * 	1 if y, 0 if n
 */
static int inputYN( char* prompt )
{
	char sel;
	char result;
	
	printf( prompt );
	scanf( " %c", &sel );
	while ( getchar() != '\n' );

	while ( sel != 'y' && sel != 'Y' && sel != 'n' && sel != 'N' )
	{
		printf( "Invalid input\n" );
		printf( prompt );
		scanf( " %c", &sel );
		while ( getchar() != '\n' );
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
