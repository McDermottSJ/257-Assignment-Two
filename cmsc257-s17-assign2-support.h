////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s17-assign2-support.h
//  Description    : This is the header file that allows dll
//
//   Author        : Sean McDermott
//   Last Modified : 3/22/2017
//

#ifndef SUPPORT_H_
#define SUPPORT_H_

struct blockMeta;

void *myMalloc(size_t size);

void myFree(void *ptr);

void *myRealloc(void *ptr, size_t size);

void *myCalloc(size_t numElem, size_t elSize);

void myMerge ();

void printList();

int leakedMeta();

#endif /* SUPPORT_H_ */
