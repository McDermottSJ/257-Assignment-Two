////////////////////////////////////////////////////////////////////////////////
//
//  File           : cmsc257-s17-assign1.c
//  Description    : This is the main source code for for the first assignment
//                   of CMSC257.  See the related
//                   assignment page for details.
//
//   Author        : Sean McDermott
//   Last Modified : 3/3/2017
//

// Include Files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Project Includes
#include <cmsc257-s17-assign1-support.h>

//
// Functions

////////////////////////////////////////////////////////////////////////////////
//
// Function     : main
// Description  : The main function for the CMSC257 assignment #1
//
// Inputs       : argc - the number of command line parameters
//                argv - the parameters
// Outputs      : 0 if successful test, -1 if failure

int main(int argc, char *argv[]) {

	// Local variables
	// NOTE: this is where you will want to add some new variables
	float f_array[20];
	int i, m_array[25], i_array[25];
	
	
	printf("float inputs: ");
	// Step #1 - read in the float numbers to process
	for (i=0; i<20; i++) {
		scanf("%f", &f_array[i]); 
		printf("%f, ", f_array[i]);
	}
	printf("\n");

    // Step #2 - convert the floating point values to integers
	printf("convert: ");
	for(i = 0; i<20; i++){
		i_array[i] = (int)f_array[i];//convert to int
		printf("%d, ", i_array[i]);
	}
	printf("\n");
	
	
	int mask;
	//bit abs
	printf("bit abs: "); 
	for(i = 0; i<20; i++){
		mask = i_array[i] >> 31;
		i_array[i] = ((mask ^ i_array[i]) - mask);
		printf("%d, ", i_array[i]);
	}
	printf("\n");

	//bit mod
	printf("bit mod: ");
	for(i = 0; i<20; i++){
		m_array[i] = i_array[i] & 15;//bitwise mod
		printf("%d, ", m_array[i]);
	}
	printf("\n");



    // Step #3 - print out the integer and floating point arrays
	float_display_array(f_array, 20);
	integer_display_array(m_array, 20);
	
	
	char string[17] = {[0 ... 15] = '0', '\0'};	
	string[15] = '1';
	binaryString(4587, 16, &string);	
	printf("4587 in bianary is: %s\n", string);

	
    	

	// Step #4 print out the number of '1's in each integer
	printf("bits in each int: ");
	for(i = 0; i<20; i++){
		printf("%d, ", countBits(m_array[1]));
	}
	printf("\n");
    	
	// Step #5 - Sort the integer array using QuickSort and print the sorted 			array
	printf("Sorted ");    	
	integerQuickSort(m_array, 0, 19);
	integer_display_array(m_array, 20);

    	
	// Step #6 - figure out number of evens in each array (float and sorted 		integer arrays)
 	printf("Number of evens in floats: %d \n", float_evens(f_array, 20));
	printf("Number of evens in Ints: %d \n", integers_evens(m_array, 20));

    
	// Step #7 - print the most frequent values from the sorted integer array
	printf("Mode of int array: %d\n", most_values(m_array, 20));


    	// Step #8 - print the integers corresponding to the reverse bit string 		from integer array
	printf("reversed bits: ");
	for(i = 0; i<20; i++){
		printf("%d, ", reverseBits((short)i_array[i]));
	}

	// Return successfully
	return(0);
}
