#include<stdio.h>

////////////////////////////////////////////////////////////////////////////////
//
// Function     : float_display_array
// Description  : prints all elements of an array of floats
//
// Inputs       : an array of floats, int representing the size of the array
// Outputs      : 0 if successful test, -1 if failure
int float_display_array(float array[], int size){//DONE
	int i;
	printf("Floats: ");
	for(i = 0; i < size-1; i++){
		printf("%f, ", array[i]);		
	}
	printf("%f\n", array[size-1]);
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : integer_display_array
// Description  : prints all elements of an array of integers
//
// Inputs       : an array of integers, int representing the size of the array
// Outputs      : 0 if successful test, -1 if failure
int integer_display_array(int array[], int size){//DONE
	int i;
	printf("Ints: ");
	for(i = 0; i < size-1; i++){
		printf("%d, ", array[i]);
	}
	printf("%d\n", array[size-1]);
	return 0;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : float_evens
// Description  : counts the number of even numbers in an array of floats
//
// Inputs       : an array of floats, int representing the size of the array
// Outputs      : the amount of even numbers as an int
int float_evens(float array[], int size){//DONE
	int i;
	int evens = 0;
	for(i = 0; i < size; i++){
		if(!((int)array[i] & 1)){
			evens++;
		}
	}
	return evens;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : integer_evens
// Description  : counts the number of even numbers in an array of integers
//
// Inputs       : an array of integers, int representing the size of the array
// Outputs      : the amount of even numbers as an int
int integers_evens(int array[], int size){//DONE
	int i;
	int evens = 0;
	for(i = 0; i < size; i++){
		if(!(array[i] & 1)){
			evens++;
		}
	}

	return evens;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : countBits
// Description  : counts the number of bits with the value of '1' in the binary rep of an integer
//
// Inputs       : an integer to calculate
// Outputs      : the number of bits with the vaule of 1 as an int
int countBits(int target){//DONE
	int bitCount = 0;
	while(target){
		bitCount += target & 1;
		target >>= 1;
	}
	return bitCount;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : most_values
// Description  : Print out the values with the most occurences in array
//
// Inputs       : an array of integers, int representing the size of the array
// Outputs      : the integer which appears most often
int most_values(int array[], int size){//CHECK PARM
	int maxValue =0, maxCount =0, i, j, count;
	for(i = 0; i < size; i++){
		count = 0;

		for(j = 0; j < size; j++){
			if(array[j] == array[i])
			count++;
		}

		if(count > maxCount){
			maxCount = count;
			maxValue = array[i];
		}
	}

	return maxValue;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : reverseBits
// Description  : Reverse the binary bit string
//
// Inputs       : a short int which will be reversed
// Outputs      : the integer that is represented by the flipped binary
unsigned short reverseBits(short target){//DONE
	int count = (sizeof(short)*8) - 1;
	int reversed = target;

	target >>= 1;
	while(target){
		reversed <<=1;
		reversed |= target & 1;
		target >>= 1;
		count--;
	}
	reversed <<= count;
	return reversed;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : bitwiseSwap
// Description  : swaps integers without a temporary variable
//
// Inputs       : two pointers to integer variables to be swapped
// Outputs      : N/A
void bitwiseSwap(int *a, int *b){
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : binaryString
// Description  : Print the binary equivalent of the number passed
//
// Inputs       : The int to represent, the length of the string, and a reference to a string to deposit the binary
// Outputs      : N/A
void binaryString(int target, int length, char *string){	
	int charPos = length - 1;	
	while(charPos + 1){
		if (target & 1)
			string[charPos] = '1';
		else
			string[charPos] = '0';
		target >>= 1;
		charPos--;
	}

}


////////////////////////////////////////////////////////////////////////////////
//
// Function     : integerQuickSort
// Description  : Sort the integer array using QuickSort algorithm
//
// Inputs       : an array of integers, the start and stop indexs for swapping
// Outputs      : N/A
void integerQuickSort(int array[], int l, int r){
	int j;

	if( l < r ){
        	j = partition( array, l, r);
	        integerQuickSort( array, l, j-1);
	        integerQuickSort( array, j+1, r);
	}
}


int partition( int array[], int l, int r) {
	int pivot, i = l, j = r+1, t;
	pivot = array[l];
		
        while(1){
   		do ++i; while( array[i] <= pivot && i <= r );
   		do --j; while( array[j] > pivot );
   		if( i >= j ) 
			break;
   		t = array[i];
		array[i] = array[j];
		array[j] = t;
   	}
	t = array[l];
	array[l] = array[j];
	array[j] = t;
   return j;
}
