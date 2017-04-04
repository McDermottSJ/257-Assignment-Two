#ifndef CMSC257_A1SUPPORT_INCLUDED
#define CMSC257_A1SUPPORT_INCLUDED

////////////////////////////////////////////////////////////////////////////////
//
//  File          : cmsc257-s17-assign1-support.h
//  Description   : This is a set of general-purpose utility functions we use
//                  for the 257 assignment #1.
//
//  Author   : Sean McDermott
//  Created  : 2/26/2017


int float_display_array(float array[], int size);
	// This function prints out the array of floating point values

int integer_display_array(int array[], int size);
	// This function prints out the array of integer values

int float_evens(float array[], int size);
	// Return the number of even numbers in the array (float version)

int integer_evens(int array[], int size);
	// Return the number of even numbers in the array (int version)

int countBits(int target);
	// Count the number of '1' bits in the binary representation

int most_values(int array[], int size);
	// Print out the values with the most occurences in array

unsigned short reverseBits(short target);
        // Reverse the binary bit string

void bitwiseSwap(int *a, int *b);

void binaryString(int target, int length, char *string);
        // Print the binary equivalent of the number passed

void integerQuickSort(int array[], int l, int r);
        // Sort the integer array using QuickSort algorithm
        

#endif // CMSC257_A1SUPPORT_INCLUDED
