#include <stdlib.h>
#include "linkedList.h"

LinkedList* createList( void )
{
	LinkedList* list;
	list = (LinkedList*)malloc( sizeof(LinkedList) );
	list -> head = NULL;
	list -> tail = NULL;

	return list;
}

void insertFirst( LinkedList* list, char* inWord )
{
	LinkedListNode* newNode;

	newNode = (LinkedListNode*)malloc( sizeof(LinkedListNode) );
	newNode -> word = inWord;
	newNode -> next = list -> head;

	if ( list -> tail == NULL )
	{
		list -> tail = newNode;
	}

	list -> head = newNode;
}

void insertLast( LinkedList* list, char* inWord )
{
	LinkedListNode* newNode;

	if ( list -> head == NULL )
	{
		insertFirst( list, inWord );
	}
	else
	{
		newNode = (LinkedListNode*)malloc( sizeof(LinkedListNode) );
		newNode -> word = inWord;
		newNode -> next = NULL;
		list -> tail -> next = newNode;
		list -> tail = newNode;
	}
}

char* getElement( LinkedList* list, int index )
{
	int i;
	LinkedListNode* node = list -> head;

	for ( i = 0; i < index; i++ )
	{
		node = node -> next;		
	}
	
	return node -> word;
}

char* removeFirst( LinkedList* list )
{
	char* returnWord = NULL;
	LinkedListNode* node = NULL;

	if ( list -> head != NULL )
	{
		node = list -> head;
		if ( node -> next == NULL )
		{
			list -> tail = NULL;
		}
		list -> head = node -> next;
		returnWord = node -> word;
		free( node );
	}

	return returnWord;
}

void freeList( LinkedList* list )
{
	char* word;
	
	do
	{
		word = removeFirst( list );
	} while ( word != NULL );

	free( list );
}
