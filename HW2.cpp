// Date: 2019.01.30
// DYNAMIC ARRAY

/* WHAT THIS PROGRAM DOES
	Utilizes a doubling dynamic array to store all the numbers in numbers.txt

*/ /* HOW TO COMPILE
	Type the following into the command prompt:
	g++ -std=c++11 DynamicArray.cpp
	./a numbers.txt

*/ /* EXAMPLE

  Assume we created an array of capacity 3.

  Also assume that numbers.txt contains the following numbers:
  1,2,3,4,5,6,7,8,9

  The program will do this:

  1...
  2...
  3...
  Resizing from 3 to 6
  4...
  5...
  6...
  Resizing from 6 to 12
  7...
  8...
  9...

*/


#include <iostream>	  // allows input and output
#include <fstream>	  // allows file manipulation
using namespace std;  // using standard namespace




// dynamically resize array function
// parameters: resize( &arrayPtr, &capacity )
void resize ( int **arrayPtr, int *capacity ) {

  // initialize variables
  int newCapacity = 0;  // initialize new capacity of array

	// double the array capacity
	newCapacity = (*capacity) * 2;
	cout << "Resizing from " << *capacity << " to " << newCapacity << "\n";

	// dynamically allocate an array of size newCapacity
	int *newArray = new int[newCapacity];

	// copy all data from oldArray to newArray
	for (int i=0; i<(*capacity); i++) {
		newArray[i] = (*arrayPtr)[i];
	}

	// free the memory associated with oldArray
	delete [] *arrayPtr;
	*arrayPtr = newArray;
	*capacity = newCapacity;
}






// main function
// take in 1 command line argument:
// 1. numbers.txt
int main ( int argc, char* argv[] ) {

	// return -1 if number of arguments is incorrect
	if ( argc != 2 ) {
		return -1;
	}

  // initialize variables
  string filename = argv[1];  // string filename is "numbers.txt"
  ifstream file;              // initialize read from file
  string line;                // string for each line of file
  int capacity = 10;          // initialize max capacity of integer array
  int *arrayPtr;              // initialize dynamic array pointer
  arrayPtr = new int[10];     // for array pointer, create new int array
  int numOfElement = 0;       // counts number of elements in array so far
  int toBeInsert = 0;         // string-to-integer conversion of each file line

	// open numbers.txt
	file.open(filename.c_str());

  // read from "numbers.txt" file
	if ( file.is_open() ) {            // if file is open

		while ( getline(file,line) ) {  // read each line of file

			if ( numOfElement == capacity ) {  // if array capacity limit is met
				resize ( &arrayPtr, &capacity ); // resize the array
			}

      toBeInsert = stoi(line);      // string-to-integer each line of file
			arrayPtr[numOfElement] = toBeInsert; // insert file line in array
			numOfElement++;               // number of array elements ++
		}

		file.close();     // close file "numbers.txt"
	}

	// print out all elements of the array
	for ( int i=0; i<numOfElement; i++) {
		cout << arrayPtr[i] << "...\n";
	}
	return 0;
}

// end of program
