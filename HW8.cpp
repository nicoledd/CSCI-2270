#include <iostream>
#include <fstream>
#include "HW8priorityQueue.hpp"
using namespace std;

// utility function to swap two elements ///////////////////////////////////////
void swap(GroupNode *x, GroupNode *y){
  // let temp equal x
  GroupNode temp = *x;
  // let x equal y
  *x = *y;
  // let y equal x
  *y = temp;
}


PriorityQueue::PriorityQueue(int queueSize){
  // maxQueueSize is input queueSize
  this->maxQueueSize = queueSize;
  // currentQueueSize is zero
  this->currentQueueSize = 0;
  // allocate memory for priorityQueue array
  this->priorityQueue = new GroupNode[queueSize];
  // initialize values for GroupNodes in priorityQueue
  for(int idx = 0; idx < queueSize; idx++){
    this->priorityQueue[idx].groupName = "";
    this->priorityQueue[idx].groupSize = 0;
    this->priorityQueue[idx].cookingTime = 0;
  }
}


bool PriorityQueue::isFull(){
  // if currentQueueSize equals maxQueueSize, return true
  if(this->currentQueueSize == this->maxQueueSize){
    return true;
  }
  // else, return false
  return false;
}


bool PriorityQueue::isEmpty(){
  // if currentQueueSize is zero, return true
  if(this->currentQueueSize == 0){
    return true;
  }
  // else return false
  return false;
}


PriorityQueue::~PriorityQueue(){
  // delete priorityQueue
  delete[] this->priorityQueue;
}

// helper functions ////////////////////////////////////////////////////////////
int parent(int i){
  return (i-1)/2;
}
int leftChild(int i){
  return 2*i + 1;
}
int rightChild(int i){
  return 2*i + 2;
}

// get node value
int getNodeVal(GroupNode node){
  return (node.groupSize * 100) + node.cookingTime;
}


void PriorityQueue::enqueue(string groupName, int groupSize, int cookingTime){

  // index of new GroupNode
  int nodeIndex = 0;

  // if priorityQueue is full, return
  if( isFull() == true ){
    cout << "Heap full, cannot enqueue\n";
    return;
  }

  // increment currentQueueSize
  this->currentQueueSize++;

  // insert new GroupNode at end of priorityQueue
  nodeIndex = this->currentQueueSize - 1;
  this->priorityQueue[nodeIndex].groupName = groupName;
  this->priorityQueue[nodeIndex].groupSize = groupSize;
  this->priorityQueue[nodeIndex].cookingTime = cookingTime;

  // if enqueue first item, return
  if(this->currentQueueSize == 1){
    return;
  }

  // use repairUpward(int nodeIndex) to repair groupSize
  repairUpward(nodeIndex);

}


void PriorityQueue::dequeue(){

  // if priorityQueue is empty, return
  if(isEmpty() == true){
    cout << "Heap empty, cannot dequeue\n";
    return;
  }

  // if priorityQueue only contains one item, delete that and return
  if(this->currentQueueSize == 1){
    this->priorityQueue[0].groupName = "";
    this->priorityQueue[0].groupSize = 0;
    this->priorityQueue[0].cookingTime = 0;
    this->currentQueueSize = 0;
    return;
  }

  // else, replace root with last in queue, and delete last in queue
  this->priorityQueue[0] = this->priorityQueue[this->currentQueueSize - 1];
  this->priorityQueue[this->currentQueueSize - 1].groupName = "";
  this->priorityQueue[this->currentQueueSize - 1].groupSize = 0;
  this->priorityQueue[this->currentQueueSize - 1].cookingTime = 0;

  // decrement currentQueueSize
  this->currentQueueSize--;

  // call repairDownward(int nodeIndex)
  repairDownward(0);

}


GroupNode PriorityQueue::peek(){
  // return root GroupNode
  return this->priorityQueue[0];
}


void PriorityQueue::repairUpward(int nodeIndex){

  // base case
  if(nodeIndex == 0){
    return;
  }

  for(int i = 0; i < this->currentQueueSize-1; i++){
    for(int j = 0; j < this->currentQueueSize-i-1; j++){
      if( getNodeVal(this->priorityQueue[j]) > getNodeVal(this->priorityQueue[j+1]) ){
        swap(&this->priorityQueue[j], &this->priorityQueue[j+1]);
      }
    }
  }

}


void PriorityQueue::repairDownward(int nodeIndex){

  for(int i = 0; i < this->currentQueueSize-1; i++){
    for(int j = 0; j < this->currentQueueSize-i-1; j++){
      if( getNodeVal(this->priorityQueue[j]) > getNodeVal(this->priorityQueue[j+1]) ){
        swap(&this->priorityQueue[j], &this->priorityQueue[j+1]);
      }
    }
  }

}


 // display menu ///////////////////////////////////////////////////////////////
 void displayMenu(){
   cout << "============Main Menu============\n";
   cout << "1. Get group information from file\n";
  cout << "2. Add a group to Priority Queue\n";
  cout << "3. Show next group in the queue\n";
  cout << "4. Serve Next group\n";
  cout << "5. Serve Entire Queue\n";
  cout << "6. Quit\n";
}

// read RestaurantData.txt /////////////////////////////////////////////////////
void readRestaurantData(string restaurantDataTxt, PriorityQueue &myQueue){

  // initialize variables: [groupName] [groupSize] [cookingTime]
  ifstream file;
  string line;
  string groupName;
  string groupSize;
  string cookingTime;
  int idxGroupSize = 0;
  int idxCookingTime = 0;

  // open RestaurantData.txt
  file.open(restaurantDataTxt);

  // read RestaurantData.txt and store in queue
  while( getline(file,line) ){

    // read the groupName
    for(int ch = 0; line[ch] != ' '; ch++){
      groupName += line[ch];
      idxGroupSize++;
    }

    // read the groupSize
    idxCookingTime = idxGroupSize;
    for(int ch = idxGroupSize + 1; line[ch] != ' '; ch++){
      groupSize += line[ch];
      idxCookingTime++;
    }

    // read the cooking time
    for(int ch = idxCookingTime + 2; line[ch] != '\0'; ch++){
      cookingTime += line[ch];
    }

    // if maxQueueSize exceeded, print error and return
    if(myQueue.isFull() == true){
      cout << "Heap full, cannot enqueue\n";
      return;
    }

    // else store in queue
    myQueue.enqueue(groupName, stoi(groupSize), stoi(cookingTime));

    // re-initialize variables
    groupName = "";
    groupSize = "";
    cookingTime = "";
    idxGroupSize = 0;
    idxCookingTime = 0;
  }

  // close file and return
  file.close();
  return;
}

// driver function /////////////////////////////////////////////////////////////
/*
Your program will take exactly one command line argument
- a number that represents the maximum queue size.
*/
int main(int argc, char *argv[]){

  // initialize variables
  string choice;
  string restaurantDataTxt;
  string groupName;
  string groupSize;
  string cookingTime;
  int maxQueueSize = stoi(argv[1]);
  int totalCookTime = 0;

  // instantiate a PriorityQueue
  PriorityQueue myQueue(maxQueueSize);

  // while user does not input "6"
  while( choice != "6" ){

    // display menu and get user's choice
    displayMenu();
    getline(cin, choice);

    switch( stoi(choice) ){

      // 1. Get group information from file
      case 1:
      cout << "Enter filename:\n";
      getline(cin, restaurantDataTxt);
      readRestaurantData(restaurantDataTxt, myQueue);
      break;

      // 2. Add a group to Priority Queue
      case 2:
      if(myQueue.isFull() == true){
        cout << "Heap full, cannot enqueue\n";
        break;
      }
      cout << "Enter Group Name:\n";
      getline(cin, groupName);
      cout << "Enter Group Size:\n";
      getline(cin, groupSize);
      cout << "Enter Estimated Cooking Time:\n";
      getline(cin, cookingTime);
      myQueue.enqueue(groupName, stoi(groupSize), stoi(cookingTime));
      break;

      // 3. Show next group in the queue
      case 3:
      if(myQueue.isEmpty() == true){
        cout << "Heap empty, nothing to peek\n";
        break;
      }
      cout << "Group Name: " << myQueue.peek().groupName << "\n";
      cout << "Group Size: " << myQueue.peek().groupSize << "\n";
      cout << "Group Time: "<< myQueue.peek().cookingTime << "\n";
      break;

      // 4. Serve Next group
      case 4:
      if(myQueue.isEmpty() == true){
        cout << "Heap empty, cannot dequeue\n";
        break;
      }
      totalCookTime += myQueue.peek().cookingTime;
      cout << "Group Name: " << myQueue.peek().groupName;
      cout << " - Total Cook Time for the Group: ";
      cout << totalCookTime << "\n";
      myQueue.dequeue();
      break;

      // 5. Serve Entire Queue
      case 5:
      while(myQueue.isEmpty() == false){
        totalCookTime += myQueue.peek().cookingTime;
        cout << "Group Name: " << myQueue.peek().groupName;
        cout << " - Total Cook Time for the Group: ";
        cout << totalCookTime << "\n";
        myQueue.dequeue();
      }
      break;

      // 6. Quit
      case 6:
      cout << "Goodbye!\n";
      break;

      default:
      break;
    }
  }

  return 0;
}
// end of program
