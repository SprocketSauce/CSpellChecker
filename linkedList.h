typedef struct LinkedListNode
{
	char* word;
	struct LinkedListNode* next;
} LinkedListNode;

typedef struct
{
	LinkedListNode* head;
	LinkedListNode* tail;
} LinkedList;

LinkedList* createList( void );

void insertFirst( LinkedList*, char* );

void insertLast( LinkedList*, char* );

char* getElement( LinkedList*, int );

char* removeFirst( LinkedList* );

void freeList( LinkedList* );
