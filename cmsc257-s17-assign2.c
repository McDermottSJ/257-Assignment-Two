////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s17-assign2.c
//  Description    : This is the driver file which tests the functions in cmsc257-s17-assign2-support.c and prints out the nodes after
//						most operations for clarity
//
//   Author        : Sean McDermott
//   Last Modified : 3/22/2017
//

#include <stdio.h>

#include "cmsc257-s17-assign2-support.h"


int main(int argc, char *argv[]){
	int *ptrOne, *ptrTwo, *ptrThree, *ptrFour, *ptrFive, *ptrSix, *ptrSeven, *ptrEight, *ptrNine, *ptrTen;

	//mallocs
	ptrOne = myMalloc(sizeof(int));//malloc 4 bytes -- rounds up to 8
	ptrTwo = myMalloc(1);//malloc 1 byte -- rounds up to 8
	ptrThree = myMalloc(sizeof(int)*100);//malloc 400 bytes
	ptrFour = myMalloc(0);//NULL
	ptrFive = myMalloc(16);//16 bytes
	ptrSix = myMalloc(32);
	ptrSeven = myMalloc(8);
	printf("After 5 mallocs:");
	printList();


	//frees
	myFree(ptrOne);
	ptrOne = NULL;
	myFree(ptrTwo);
	ptrTwo = NULL;
	myFree(ptrThree);
	ptrTwo = NULL;
	myFree(ptrFive);
	ptrFive=NULL;
	myFree(ptrSix);
	ptrSix = NULL;
	myFree(ptrSeven);
	ptrSeven = NULL;
	printf("After freeing all 6 blocks:");
	printList();


	//mallocs
	ptrOne = myMalloc(8);
	printf("malloc for 8");
	printList();

	ptrTwo = myMalloc(8);
	printf("malloc for 8");
	printList();

	ptrThree = myMalloc(16);
	printf("malloc for 16");
	printList();

	ptrFour = myMalloc(32);
	printf("malloc for 32");
	printList();

	ptrFive = myMalloc(60);
	printf("malloc for 60");
	printList();


	//reallocs
	ptrTwo = myRealloc(ptrTwo, 72);//bigger than original
	printf("realloc on node 2 for 72 bytes");
	printList();

	ptrFive = myRealloc(ptrFive, 40);//smaller than original
	printf("realloc on node 3 for 40 bytes");
	printList();

	ptrThree = myRealloc(ptrThree, 16);//same size
	printf("realloc on node 5 for 16 bytes");
	printList();

	ptrFour = myRealloc(ptrFour, 16);//split will be too small to fit meta
	printf("realloc on node 6 for 16 bytes");
	printList();

	ptrSix = myMalloc(240);
	printf("malloc 240 bytes");
	printList();

	ptrSix = myRealloc(ptrSix, 224);
	printf("realloc on node 4 for 224 bytes");
	printList();

	ptrOne = myRealloc(ptrOne, 2);//too small
	printf("realloc on node 8 for 2 bytes");
	printList();

	ptrSeven = myMalloc(80);
	printf("malloc 80");
	printList();

	ptrSeven = myRealloc(ptrSeven, 72);
	printf("realloc on node 5 for 72 bytes");
	printList();

	ptrFive = myRealloc(ptrFive, 0);
	printf("realloc on node 3 for 0 bytes");
	printList();

	ptrSeven = myRealloc(ptrSeven, 16);
	printf("realloc on node 5 for 16 bytes");
	printList();

	ptrSix = myRealloc(ptrSix, 64);
	printf("realloc on node 4 for 64 bytes");
	printList();


	//callocs
	ptrOne = myCalloc(4, sizeof(int));//callocs 16 bytes
	ptrTwo = myCalloc(5, sizeof(int));//callocs 24 bytes
	ptrThree = myCalloc(8, 1);//callocs 8 bytes
	ptrFour = myCalloc(20, 8);
	ptrFive = myCalloc(0, 8);//NULL
	ptrSix = myCalloc(10, 0);//NULL
	ptrSeven = myCalloc(6, 8);
	ptrEight = myCalloc(0,0); //NULL
	ptrNine = myCalloc(10 ,7);
	ptrTen = myCalloc(1,1);
	printf("after seven successful callocs and three nulls: ");
	printList();


	//setup for merges
	myFree(ptrOne);
	myFree(ptrTwo);
	myFree(ptrThree);
	myFree(ptrFour);
	myFree(ptrFive);
	myFree(ptrSix);
	myFree(ptrSeven);
	myFree(ptrEight);
	myFree(ptrNine);
	myFree(ptrTen);
	printf("after freeing several: ");
	printList();

	//merges
	myMerge();
	printf("after merge: ");
	printList();


	printf("%d bytes were leaked due to %d metaBlocks\n", leakedMeta(), leakedMeta()/24);

	return 0;
}

