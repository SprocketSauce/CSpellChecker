/*
 * FILE: linkedList.h
 * AUTHOR: Jack McNair 18927430
 * LAST MOD: 18/10/2017
 *
 * Defines a double-ended, singly-linked list for storing void pointers.
 */

/*
 * LinkedListNode
 *
 * A node in a singly-linked list that stores a void pointer.
 *
 * FIELDS:
 *  word - Pointer to the string stored by the list node
 *  next - Pointer to the next node in the list
 */
typedef struct LinkedListNode
{
	void* value;
	struct LinkedListNode* next;
} LinkedListNode;

/*
 * LinkedList
 *
 * Stores the head and tail of a double-ended linked list.
 *
 * FIELDS:
 *  word - Pointer to the first node in the list
 *  tail - Pointer to the last node in the list
 */
typedef struct
{
	LinkedListNode* head;
	LinkedListNode* tail;
} LinkedList;

LinkedList* createList( void );

void insertFirst( LinkedList*, void* );

void insertLast( LinkedList*, void* );

void* getElement( LinkedList*, int );

void* removeFirst( LinkedList* );

void freeList( LinkedList* );
