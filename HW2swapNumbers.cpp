// Date: 2019.01.29
// SWAP NUMBERS

/* WHAT THIS PROGRAM DOES
    There is an array {1,2,3,4,5}. This program swaps whichever two numbers you
    wish to swap in this array.

*/ /* HOW TO COMPILE
    Type the following into the command prompt:
    g++ -std=c++11 SwapNumbers.cpp
    ./a out

*/ /* EXAMPLE

    In this program, we have an array {1,2,3,4,5}

    1. The program outputs the addresses of array elements:
        Addresses of elements
        :0x7fffa87ece10
        0x7fffa87ece140x7fffa87ece18
        0x7fffa87ece1c
        0x7fffa87ece20

    2. The program outputs the array elements:
        Elements:
        1
        2
        3
        4
        5

    3. Enter the indices of the elements you want to swap in the array
        First index: 0
        Second index: 1

    4. Enter 0 for pass-by-value, 1 for pass-by-pointer
        1
        Before swapping: 1 2 3 4 5
        After swapping: 2 1 3 4 5

    5. Press 1 to continue, else press 0
        0
        Reversing the array
        After reversing:
        5 4 3 1 2
*/

#include <iostream>     // allows input and output
using namespace std;    // standard namespace





// pass by value
void swap ( int n1, int n2 ) {
  int temp;
  temp = n1;
  n1 = n2;
  n2 = temp;
}





// pass by pointer
void swap_by_pointers ( int *n1, int *n2 ) {
  int temp;
  temp = *n1;
  *n1 = *n2;
  *n2 = temp;
}





// Function to reverse the array through pointers
void reverse ( int array[], int array_size ) {

    int *pointer1 = array;  // points to start of array

    int *pointer2 = array + array_size-1; // points to end of array

    // swap by pointers
    while ( pointer1 < pointer2 ) {
      swap_by_pointers ( pointer1, pointer2 );
      pointer1++;
      pointer2--;
    }
}







// main function
int main ( int argc, char const *argv[] ) {

  // initialize variables
  int flag = 1;     // int flag
  int idx_one = 0;  // index one of what you want to swap
  int idx_two = 0;  // index two of what you want to swap
  int pass_by_value_or_pointer = 0;// 0 for pass by value, 1 for pass by pointer
  int arr[5] = {1, 2, 3, 4, 5}; // initialize integer array

  // print out addresses of array elements
  cout << "Addresses of elements\n:";
  for ( int i=0; i<5; i++ ) {
    cout << arr+i << "\n";
  }
  cout << "\n";

  // print out array elements using pointers
  cout << "Elements:\n";
  for ( int i=0; i<5; i++ ) {
    cout << *(arr+i) << "\n";
  }
  cout << "\n";

  // while loop
  while ( flag == 1 ) {

    // enter the numbers you want to swap
    cout << "Enter indices of elements you want to swap?\n";
    cout << "First index\n";
    cin >> idx_one;
    cout << "Second index\n";
    cin >> idx_two;
    cout << "Enter 0 for pass-by-value, 1 for pass-by-pointer\n";
    cin >> pass_by_value_or_pointer;

    // swap array elements
    switch ( pass_by_value_or_pointer ) {

      // pass by value,  not supposed to work
      case 0:

        // cout values before swapping using for loop
        cout << "Before swapping\n";
        for ( int i=0; i<5; i++ ) {
          cout << arr[i]<<" ";
        }
        cout << "\n";

        // swap values
        swap ( arr[idx_one], arr[idx_two] );

        // cout values after swapping using for loop
        cout << "\nAfter swapping\n";
        for ( int i=0; i<5; i++ ) {
          cout << arr[i] << " ";
        }
        cout << "\n";
        break;

      // pass by pointer, supposed to work
      case 1:

        // cout values before swapping
        cout << "Before swapping\n";
        for ( int i=0; i<5; i++ ) {
          cout << arr[i] << " ";
        }
        cout << "\n";

        // swap values
        swap_by_pointers ( &arr[idx_one], &arr[idx_two] );

        // cout values after swapping
        cout << "\nAfter swapping\n";
        for ( int i=0; i<5; i++ ) {
          cout << arr[i] << " ";
        }
        cout << "\n";
        break;
    }

    // exit program
    cout << "\nPress 1 to continue else press 0\n";
    cin >> flag;

  }

  // reverse the array when you quit
  cout << "Reversing the array";
  reverse ( arr,5 );
  // cout reversed array
  cout << "\nAfter reversing\n";
  for ( int i=0; i<5; i++ ){
    cout << arr[i] << " ";
  }
  cout<<"\n";

  return 0;
}

// end of program
