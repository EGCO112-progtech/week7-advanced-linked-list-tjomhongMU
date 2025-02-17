
/*
// self-referential structure
struct Node {
   int data; // each listNode contains a character
   struct Node *nextPtr; // pointer to next node
}; // end structure listNode
*/

struct Node
{
	int	data;
	char	name[100];
	struct Node *nextPtr; // pointer to next node
	struct Node *prevPtr; // pointer to prev node
};
typedef struct Node LLnode; // synonym for struct listNode
typedef LLnode *LLPtr; // synonym for ListNode*

// prototypes

int deletes( LLPtr *sPtr, int value );
int isEmpty( LLPtr sPtr );
void insert( LLPtr *sPtr, int value, char *str);
void printList( LLPtr currentPtr );
void printList_r( LLPtr currentPtr );
void instructions( void );


// display program instructions to user
void instructions( void )
{
   puts( "Enter your choice:\n"
      "   1 to insert an element into the list.\n"
      "   2 to delete an element from the list.\n"
      "   3 to end." );
} // end function instructions

// insert a new value into the list in sorted order
void insert(LLPtr *sPtr, int value, char *str)
{
   LLPtr newPtr; // pointer to new node
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list

   newPtr = (LLPtr)malloc(sizeof(LLnode)); // create node
   if (newPtr != NULL) 
   { // is space available
      newPtr->data = value; // place value in node
      strcpy(newPtr->name, str);
      newPtr->nextPtr = NULL; // node does not link to another node
      newPtr->prevPtr = NULL; // node does not link to another node
      previousPtr = NULL;
      currentPtr = *sPtr;
      // loop to find the correct location in the list
      while (currentPtr != NULL && value > currentPtr->data) 
      {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while
      // insert new node at beginning of list
      if (previousPtr == NULL)
      {
         newPtr->nextPtr = *sPtr;
	 newPtr->prevPtr = NULL;
	 if (*sPtr)
	 	(*sPtr)->prevPtr = newPtr;
         *sPtr = newPtr;
      } // end if
      else
      { // insert new node between previousPtr and currentPtr
         previousPtr->nextPtr = newPtr;
	 newPtr->prevPtr = previousPtr;

         newPtr->nextPtr = currentPtr;
	 if (currentPtr)
	 	currentPtr->prevPtr = newPtr;
      } // end else
   } // end if
   else 
   {
      printf( "%d not inserted. No memory available.\n", value );
   } // end else
} // end function insert

// delete a list element
int deletes(LLPtr *sPtr, int value)
{
   LLPtr previousPtr; // pointer to previous node in list
   LLPtr currentPtr; // pointer to current node in list
   LLPtr tempPtr; // temporary node pointer

   // delete first node
   if (value == (*sPtr)->data) 
   {
      tempPtr = *sPtr; // hold onto node being removed
      *sPtr = (*sPtr)->nextPtr; // de-thread the node
      if (*sPtr)
  	(*sPtr)->prevPtr = NULL;
      free( tempPtr ); // free the de-threaded node
      return value;
   } // end if
   else {
      previousPtr = *sPtr;
      currentPtr = (*sPtr)->nextPtr;
      // loop to find the correct location in the list
      while ( currentPtr != NULL && currentPtr->data != value ) {
         previousPtr = currentPtr; // walk to ...
         currentPtr = currentPtr->nextPtr; // ... next node
      } // end while
      // delete node at currentPtr
      if ( currentPtr != NULL )
      {
         tempPtr = currentPtr;
         previousPtr->nextPtr = currentPtr->nextPtr;
	 currentPtr->nextPtr->prevPtr = previousPtr;
         free(tempPtr);
         return (value);
      } // end if
   } // end else
   return (0);
} // end function delete

int	deletes_all(LLPtr *sPtr)
{
	printf("Clear all nodes\n");
	while (*sPtr)
	{
		printf("%d deleted.\n", (*sPtr)->data);
		deletes(sPtr, (*sPtr)->data);
	}
}
// return 1 if the list is empty, 0 otherwise
int isEmpty(LLPtr sPtr)
{
   return (sPtr == NULL);
} // end function isEmpty

// print from the last list
void printList_r(LLPtr currentPtr)
{
      //move currentPtr to the end of the list. 
     if (!isEmpty(currentPtr))
	{ 
      while (currentPtr->nextPtr!= NULL)
         currentPtr = currentPtr->nextPtr;
      //while not the start of the list.
      while (currentPtr->prevPtr != NULL)
      {
      		printf( "%d %s --> ", currentPtr->data, currentPtr->name);
	      currentPtr = currentPtr->prevPtr;
      }
      printf("%d %s --> NULL\n", currentPtr->data, currentPtr->name);
	}
} // end function printList
// print the list
void printList( LLPtr currentPtr )
{
   // if list is empty
   if ( isEmpty( currentPtr ) ) {
      puts( "List is empty." );
   } // end if
   else {
      puts( "The list is:" );

      // while not the end of the list
      while ( currentPtr->nextPtr!= NULL ) {
         printf( "%d %s --> ", currentPtr->data, currentPtr->name);
         currentPtr = currentPtr->nextPtr;
      } // end while
      printf( "%d %s --> NULL\n",currentPtr->data, currentPtr->name);
   } // end else
} // end function printList
