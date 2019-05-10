/* Assignment 1 - Dynamic Array */


#include <iostream>
#include <fstream>
using namespace std;






/* dynamically resize the given array, by doubling its capacity */
void resize(int **oldArray, int *capacity){

	/* double the array capacity */
	std::cout << "Resizing from " << *capacity << " to " << (*capacity) * 2 << "\n";

	/* dynamically allocate an array of size newCapacity */
	int *newArray = new int[(*capacity) * 2];

	/* copy all data from oldArray to newArray */
	for(int idx = 0; idx < (*capacity); idx++){
		newArray[idx] = (*oldArray)[idx];
	}

	/* free the memory associated with oldArray */
	delete [] *oldArray;
	*oldArray = newArray;
	*capacity *= 2;
}











/* driver function takes in one command line argument: HW1.txt */
int main(int argc, char* argv[]){

	/* return -1 if the number of arguments is incorrect */
	if(argc != 2){
		return -1;
	}

  /* initialize variables for reading from file */
  std::ifstream file;
  std::string line;

  /* initialize variables for dynamic array */
  int currCapacity = 0;
  int maxCapacity = 10;
  int *dynamicArray;
  dynamicArray = new int[maxCapacity];

	/* open and read from the file HW1.txt */
	file.open(argv[1]);
	if(file.is_open()){
		while(getline(file,line)){

      /* if the maximum capacity of the array is met, resize the array */
			if(currCapacity == maxCapacity){
				resize(&dynamicArray, &maxCapacity);
			}

      /* insert new element into the array, and increment the curr capacity */
			dynamicArray[currCapacity] = stoi(line);
			currCapacity++;
		}
	}

  /* print all the elements of the array */
	for(int idx = 0; idx < currCapacity; idx++){
		std::cout << dynamicArray[idx] << "...\n";
	}

  /* close file and return */
  file.close();
	return 0;
}
