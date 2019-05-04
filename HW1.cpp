// Date: 2019.24.01
// INSERT NUMBER INTO SORTED ARRAY

/* WHAT THIS PROGRAM DOES
    You give a function an already sorted array of integers.
    Next, give it another integer. The function puts that integer
    into its correct place in the sorted array.

*/ /* HOW TO COMPILE
    Type the following into the command prompt:
    g++ -std=c++11 SortNumbers.cpp
    ./a out

*/ /* EXAMPLE
    Let's say we give it the array [3,19,44] and a new value 1.
    The output should be [1,3,19,44]

*/

#include <iostream> // allows input and output
using namespace std;

// insert into sorted array function
int insertIntoSortedArray ( int myArray[],  // sorted array
                            int numEntries, // array size
                            int newValue ) {    // new value

    myArray[numEntries] = newValue; // add new value to tial of array

    // bubble sort
    for ( int i=0; i<=numEntries; i++ ) {
        for ( int j=i+1; j<=numEntries; j++ ) {
            if ( myArray[i] > myArray[j] ) {
                newValue = myArray[i];
                myArray[i] = myArray[j];
                myArray[j] = newValue;
            }
        }
    }

    return numEntries+1;    // return new array size
}


// main function
int main ( ) {

    int myArray[100] = {3,19,44};   // sorted array
    int numEntries = 3; // array size
    int newValue = 1;   // new value to be put into sorted array

    // insert new value into sorted array function
    insertIntoSortedArray ( myArray,
                        numEntries,
                        newValue );

    return 0;
}

// end of program
