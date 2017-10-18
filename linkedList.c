/*
 * FILE: linkedList.c
 * AUTHOR: Jack McNair 18927430
 * LAST MOD: 18/10/2017
 *
 * Contains functionality for manipulating double-ended, singly-linked lists containing dynamically
 * allocated strings. Functions contained allow for list creation, insertion at the front and back,
 * removal from the front, retrieval from a specified index and memory deallocation.
 */

#include <stdlib.h>
#include "linkedList.h"

/*
 * createList
 *
 * Allocates memory for a linked list. Sets the head and tail of that list to null.
 *
 * RETURNS:
 * 	A pointer to an empty linked list
 */
LinkedList* createList( void )
{
	LinkedList* list;
	list = (LinkedList*)malloc( sizeof(LinkedList) );
	list -> head = NULL;
	list -> tail = NULL;

	return list;
}

/*
 * insertFirst
 *
 * Inserts an element into the front of a linked list.
 *
 * INPUTS:
 * 	list - The list into which the element is inserted
 * 	inWord - The string to be inserted into the list
 */
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

/*
 * insertLast
 *
 * Inserts and element into the back of a linked list.
 *
 * INPUTS:
 * 	list - The list into which the element is inserted
 * 	inWord - The string to be inserted into the list
 */
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

/*
 * getElement
 *
 * Retrieves the element at the specified position in the linked list.
 *
 * INPUTS:
 * 	list - The list to retrieve the element from
 * 	index - The position of the element to be retrieved
 *
 * RETURNS:
 * 	The string at the specified position
 */
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

/*
 * removeFirst
 *
 * Removes the element at the front of a linked list and deallocates its memory.
 *
 * INPUTS:
 * 	list - The list to remove the element from
 *
 * RETURNS:
 * 	The removed string
 */
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

/*
 * freeList
 *
 * Deallocates all memory associated with a specified linked list.
 *
 * INPUTS:
 * 	list - The list to be deallocated
 */
void freeList( LinkedList* list )
{
	char* word;
	
	do
	{
		word = removeFirst( list );
	} while ( word != NULL );

	free( list );
}
