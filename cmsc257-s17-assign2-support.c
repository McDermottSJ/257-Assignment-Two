////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s17-assign2-support.c
//  Description    : This is the main source code, it contains the functions relating to malloc
//
//   Author        : Sean McDermott
//   Last Modified : 3/22/2017
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


struct blockMeta {
	size_t size;
	struct blockMeta *next;
	int free;
	int magic;
};

#define META_SIZE sizeof(struct blockMeta)

void *globalBase = NULL;//linked list head
void *globalEnd = NULL;
int leaked = 0;


////////////////////////////////////////////////////////////////////////////////
//
// Function     : buffedSize
// Description  : reformats int to a number which is a multiple of 8
//
// Inputs       : an integer to change
// Outputs      : correctly buffered int
int buffedSize(int size){
	int i;
	if(size == 0){
		return 0;
	}
	while(size%8){
		size++;
	}

	return size;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : findFreeBlock
// Description  : looks through blocks for the best fitting free block and reports any memory leaks
//
// Inputs       : the last node, the size of the desired block
// Outputs      : either the correctly fitted node, or a null if none found
struct blockMeta *findFreeBlock(struct blockMeta **last, size_t size){
	struct blockMeta *current = globalBase;
	struct blockMeta *bestFit = NULL;

	while(current){
		if((current->free && current->size >= size)){//if the current is free AND current's size is big enough.
			if(bestFit == NULL){//for first case
				bestFit = current;
			}
			if(bestFit->size >= current-> size){//if the new one is better than the best
				bestFit = current;
			}
		}
		current = current->next;
	}
	if(bestFit && (bestFit->size - size > 0)){
		printf("best fit leaked %d bytes\n", bestFit->size - size);
	}

	return bestFit;
}

////////////////////////////////////////////////////////////////////////////////
//
// Function     : getBlockPtr
// Description  : gives the pointer to a block
//
// Inputs       : content pointer
// Outputs      : block pointer
struct blockMeta *getBlockPtr(void *ptr){
	return (struct blockMeta*)ptr - 1;//return pointer back by the size of meta
}


struct blockMeta *requestSpace(struct blockMeta *last, size_t size){
	struct blockMeta *block;
	block = sbrk(0);
	size= buffedSize(size);

	void *request = sbrk(size + META_SIZE);
	assert((void*)block == request);
	if (request == (void*)-1){ //request failed
		return NULL;
	}
	if(last) { //set the last node in list to point here
		last->next = block;
	}
	block->size = size;
	block->next = NULL;
	block->free = 0;
	block->magic = 0x12345678;
	return block;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : split
// Description  : creates a new free block with the leftover memory of another and reports any leaked memory if insufficient size
//
// Inputs       : the node to be split, the new size of that node
// Outputs      : pointer to original node
void *split(struct blockMeta *blockPtr, size_t updatedSize){
	struct blockMeta *newBlock;
	char *ptr = blockPtr;
	updatedSize = buffedSize(updatedSize);
	ptr += (updatedSize + sizeof(struct blockMeta));

	if((blockPtr->size - updatedSize) < sizeof(struct blockMeta)){//if too small to fit meta
		if(blockPtr->size - updatedSize > 0){
			printf("split leaked %d bytes\n", blockPtr->size - updatedSize);
		}
		return NULL;
	}

	newBlock = ptr;
	newBlock->size = ((blockPtr->size - updatedSize) - sizeof(struct blockMeta));
	blockPtr->size = updatedSize;

	newBlock->next = blockPtr->next;
	blockPtr->next = newBlock;
	newBlock->free = 1;
	newBlock->magic = 0x88888888;

	return newBlock + 1;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : myMerge
// Description  : merges adjacent free blocks
//
// Inputs       : N/A
// Outputs      : N/A
void myMerge (){
	struct blockMeta *current = globalBase;
	int newSize;

	while(current->next){
		if(current->free && current->next->free){
			newSize = (current->size + current->next->size) + sizeof(struct blockMeta);
			current->size = newSize;
			current->next = current->next->next;
			continue;
		}
		else{
			current = current->next;
		}
	}
}



////////////////////////////////////////////////////////////////////////////////
//
// Function     : myMalloc
// Description  : attempts to create a space on the heap for the size called for
//
// Inputs       : int of desired size
// Outputs      : null for a failure or the pointer of the space on the heap
void *myMalloc(size_t size){
	struct blockMeta *block;
	size = buffedSize(size);

	if(size == 0){
		return NULL;
	}
	if(!globalBase){ //for the first use of malloc
		block = requestSpace(NULL, size);
		if (!block){//if request fails
			return NULL;
		}
		globalBase = block;//set the head to the new first node
		globalEnd = block;
	}else{ //for every call after the first
		struct blockMeta *last = globalEnd;
		block = findFreeBlock(&last, size);
		if(!block){ //couldn't find any free space
			block = requestSpace(last, size);
			if(!block){ //request failed
				return NULL;
			}
			globalEnd = block;
		}else{ //found a free space
			block->free = 0;
			block->magic = 0x77777777;
		}
	}

	return (block + 1);
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : myFree
// Description  : sets a block to free
//
// Inputs       : N/A
// Outputs      : N/A
void myFree(void *ptr){
	if(!ptr){//check for null
		return;
	}

	struct blockMeta *blockPtr = getBlockPtr(ptr);//get the meta data

	assert(blockPtr->free == 0);
	assert(blockPtr->magic == 0x77777777 || blockPtr->magic == 0x12345678);

	blockPtr->free = 1;
	blockPtr->magic = 0x55555555;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : myRealloc
// Description  : changes the size of a block, if its smaller than the original it gets split, if it is larger a new block is made
//
// Inputs       : the block to change, the new size
// Outputs      : pointer to new or resized space on heap
void *myRealloc(void *ptr, size_t size){
	size = buffedSize(size);
	if(!ptr){ //check for null
		return myMalloc(size);
	}
	if(size == 0){
		return ptr;
	}
	struct blockMeta *blockPtr = getBlockPtr(ptr);
	if(blockPtr->size >= size){//original allocated size big enough
		split(blockPtr, size);
		return ptr;
	}

	void *newPtr;
	newPtr = myMalloc(size);
	if(!newPtr){ //if malloc failed
		return NULL;
	}
	memcpy(newPtr, ptr, blockPtr->size);
	myFree(ptr);
	return newPtr;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : myCalloc
// Description  : sets a block of memory to all zeros
//
// Inputs       : the number of elements, the size of the elements
// Outputs      : pointer to space on heap
void *myCalloc(size_t numElem, size_t elSize){
	size_t size = numElem * elSize; //Check for overflow
	void *ptr = myMalloc(size);
	memset(ptr, 0, size);
	return ptr;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : printList
// Description  : prints all nodes in linked list and details about them
//
// Inputs       : N/A
// Outputs      : N/A
void printList(){
	struct blockMeta *current = globalBase;
	int count = 1;
	void* endPtr;

	printf("\nCurrent Nodes:\n");
	while(current){
		endPtr = current+1;
		endPtr += (current->size);
		printf("%d Node at : %p ending at: %p size: %d free: %d\n", count, current, endPtr, current->size, current->free);
		current = current->next;
		count++;
	}
	printf("\n\n");
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : leakedMeta
// Description  : reports leaked memory due to meta blocks
//
// Inputs       : N/A
// Outputs      : amount of leaked memory
int leakedMeta(){
	struct blockMeta *current = globalBase;
	int leak = 0;

	while(current){
		leak += 24;
		current = current->next;
	}
	return leak;
}









