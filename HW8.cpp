/* Assignment 8 - Heaps/Priority Queues

OBJECTIVES
1. Implement a priority queue using an array
2. Add and remove elements to/from the priority queue */





#include "HW8.hpp"





/* swap two given customer nodes */
void swap(GroupNode *x, GroupNode *y){
  GroupNode temp = *x;
  *x = *y;
  *y = temp;
}






/* parametrized constructor for the priority queue */
PriorityQueue::PriorityQueue(int maxQueueSize){
  /* initialize the max queue size as the input integer, and set the current
    queue size to 0 */
  this->maxQueueSize = maxQueueSize;
  this->currentQueueSize = 0;

  /* allocate memory for the priority queue, and initialize values for each
    customer node in the queue */
  this->priorityQueue = new GroupNode[maxQueueSize];
  for(int idx = 0; idx < maxQueueSize; idx++){
    this->priorityQueue[idx].groupName = "";
    this->priorityQueue[idx].groupSize = 0;
    this->priorityQueue[idx].cookingTime = 0;
  }
}







/* return true if the queue is full, else return false */
bool PriorityQueue::isFull(){
  if(this->currentQueueSize == this->maxQueueSize){
    return true;
  }
  return false;
}






/* return true if the queue is empty, else return false */
bool PriorityQueue::isEmpty(){
  if(this->currentQueueSize == 0){
    return true;
  }
  return false;
}






/* destructor */
PriorityQueue::~PriorityQueue(){
  delete[] this->priorityQueue;
}






/* functions to return the parent index, left child index, and right child
  index of the given index */
int parent(int i){
  return (i-1)/2;
}
int leftChild(int i){
  return 2*i + 1;
}
int rightChild(int i){
  return 2*i + 2;
}






/* adds and returns the size of the customer's group and the customer's
  cooking time */
int getNodeVal(GroupNode customer){
  return (customer.groupSize * 100) + customer.cookingTime;
}






/* enqueue a new customer at the end of the queue, then call repair upward to
  swap this node with its parent if necessary */
void PriorityQueue::enqueue(std::string groupName, int groupSize, int cookingTime){

  /* if the queue is already full, return */
  if(isFull() == true){
    std::cout << "Heap full, cannot enqueue\n";
    return;
  }

  /* insert the new customer at the end of the queue */
  this->priorityQueue[this->currentQueueSize].groupName = groupName;
  this->priorityQueue[this->currentQueueSize].groupSize = groupSize;
  this->priorityQueue[this->currentQueueSize].cookingTime = cookingTime;

  /* increment the current queue size */
  currentQueueSize++;

  /* if this is the first element that is being enqueued, return */
  if(this->currentQueueSize == 1){
    return;
  }

  /* otherwise, call repair upward to swap this node with its parent
    if necessary */
  repairUpward(this->currentQueueSize - 1);
}





/* dequeue a customer by replacing the front of the queue with the last in the
  queue, then delete the last element. Then, call repair downward on the front
  of the queue, to swap with its child if necessary */
void PriorityQueue::dequeue(){

  /* if the queue is already empty, return */
  if(isEmpty() == true){
    std::cout << "Heap empty, cannot dequeue\n";
    return;
  }

  /* if the queue only contains one item, delete that and return */
  if(this->currentQueueSize == 1){
    this->priorityQueue[0].groupName = "";
    this->priorityQueue[0].groupSize = 0;
    this->priorityQueue[0].cookingTime = 0;
    this->currentQueueSize = 0;
    return;
  }

  /* otherwise, replace the front of the queue with the element that is
    last in queue, and delete that last element */
  this->priorityQueue[0] = this->priorityQueue[this->currentQueueSize - 1];
  this->priorityQueue[this->currentQueueSize - 1].groupName = "";
  this->priorityQueue[this->currentQueueSize - 1].groupSize = 0;
  this->priorityQueue[this->currentQueueSize - 1].cookingTime = 0;

  /* decrement the current queue size */
  this->currentQueueSize--;

  /* call repair downward, on the front of the queue */
  repairDownward(0);
}






/* return the customer at the front of the queue */
GroupNode PriorityQueue::peek(){
  return this->priorityQueue[0];
}






/* swaps given node with its parent if necessary */
void PriorityQueue::repairUpward(int index){

  /* if the value of the node is less than its parent, swap them, and call
    repair upward on the parent node (which has now been swapped) */
  if(getNodeVal(this->priorityQueue[index]) < getNodeVal(this->priorityQueue[parent(index)])){
    swap(&this->priorityQueue[index], &this->priorityQueue[parent(index)]);
    repairUpward(parent(index));
  }

}





/* swaps given node with its child if necessary */
void PriorityQueue::repairDownward(int index){

  /* variable for finding the smallest index */
  int smallestIndex = 0;

  /* if the left child of the node is smaller than itself, the smallest index
    becomes the left child index */
  if(leftChild(index) < this->currentQueueSize && getNodeVal(this->priorityQueue[leftChild(index)]) < getNodeVal(this->priorityQueue[index])){
      smallestIndex = leftChild(index);
  }

  /* if the right child of the node is smaller than its 'smallest' value
    (whether it be itself, or its left child), the smallest index becomes
    the right child index */
  if(rightChild(index) < this->currentQueueSize && getNodeVal(this->priorityQueue[rightChild(index)]) < getNodeVal(this->priorityQueue[smallestIndex])){
      smallestIndex = rightChild(index);
  }

  /* if the right child or left child is smaller than the node, swap them,
    and call repair downward on the swapped node */
  if(smallestIndex != index){
    swap(&this->priorityQueue[index], &this->priorityQueue[smallestIndex]);
    repairDownward(smallestIndex);
  }

}









/* as long as the customer does not choose to quit, repeatedly display this
  menu and read the customer's choice */
void displayMenu(){
  std::cout << "============Main Menu============\n";
  std::cout << "1. Get group information from file\n";
  std::cout << "2. Add a group to Priority Queue\n";
  std::cout << "3. Show next group in the queue\n";
  std::cout << "4. Serve Next group\n";
  std::cout << "5. Serve Entire Queue\n";
  std::cout << "6. Quit\n";
}







/* read the customer information from HW8.txt, and store the customers as nodes
  in the priority queue */
void readRestaurantData(std::string txtFile, PriorityQueue &myQueue){

  std::ifstream file;
  std::string line;
  std::string groupName, groupSize, cookingTime;
  int idxGroupSize = 0;
  int idxCookingTime = 0;

  /* open and read HW8.txt */
  file.open(txtFile);
  while(getline(file, line)){

    /* read the groupName and store it in a string variable */
    for(int ch = 0; line[ch] != ' '; ch++){
      groupName += line[ch];
      idxGroupSize++;
    }

    /* read the groupSize and store it in a string variable */
    idxCookingTime = idxGroupSize;
    for(int ch = idxGroupSize + 1; line[ch] != ' '; ch++){
      groupSize += line[ch];
      idxCookingTime++;
    }

    /* read the cooking time and store it in a string variable */
    for(int ch = idxCookingTime + 2; line[ch] != '\0'; ch++){
      cookingTime += line[ch];
    }

    /* if the queue is already full, close the file and return */
    if(myQueue.isFull() == true){
      std::cout << "Heap full, cannot enqueue\n";
      file.close();
      return;
    }

    /* otherwise, store the customer information in the priority queue */
    myQueue.enqueue(groupName, stoi(groupSize), stoi(cookingTime));

    /* re-initialize the relevant variables */
    groupName = "";
    groupSize = "";
    cookingTime = "";
    idxGroupSize = 0;
    idxCookingTime = 0;
  }

  /* close the file */
  file.close();
}







/* driver function takes exactly one command line argument: an integer num that
  represents the max queue size */
int main(int argc, char *argv[]){

  /* initialize variables */
  std::string choice;
  std::string txtFile;
  std::string groupName, groupSize, cookingTime;
  int totalCookTime = 0;

  /* instantiate a PriorityQueue, with max queue size given by
    the command line argument */
  PriorityQueue myQueue(std::stoi(argv[1]));

  /* while user does not choose to quit, repeat this while-loop */
  while( choice != "6" ){

    /* repeatedly display menu and read user's choice */
    displayMenu();
    getline(std::cin, choice);

    /* switch cases based on user's choice */
    switch(stoi(choice)){

      /* case 1: read HW8.txt, which contains information regarding all of the
        customers, and enqueue all the information into the queue */
      case 1:
        std::cout << "Enter filename:\n";
        getline(std::cin, txtFile);
        readRestaurantData(txtFile, myQueue);
        break;

      /* case 2: enqueue */
      case 2:
        /* if the queue is already full, exit */
        if(myQueue.isFull() == true){
          std::cout << "Heap full, cannot enqueue\n";
          break;
        }
        /* otherwise, get the name, size, and cooking time of the customer, and
          enqueue this info into the priority queue */
        std::cout << "Enter Group Name:\n";
        getline(std::cin, groupName);
        std::cout << "Enter Group Size:\n";
        getline(std::cin, groupSize);
        std::cout << "Enter Estimated Cooking Time:\n";
        getline(std::cin, cookingTime);
        myQueue.enqueue(groupName, stoi(groupSize), stoi(cookingTime));
        break;

      /* case 3: prints the info of the customator at the front of the queue */
      case 3:
      /* if the queue is empty, exit */
        if(myQueue.isEmpty() == true){
          std::cout << "Heap empty, nothing to peek\n";
          break;
        }
        /* otherwise, print the customer's information */
        std::cout << "Group Name: " << myQueue.peek().groupName << "\n";
        std::cout << "Group Size: " << myQueue.peek().groupSize << "\n";
        std::cout << "Group Time: "<< myQueue.peek().cookingTime << "\n";
        break;

      /* case 4: dequeue */
      case 4:
      /* if the queue is already empty, exit */
        if(myQueue.isEmpty() == true){
          std::cout << "Heap empty, cannot dequeue\n";
          break;
        }
        /* otherwise, print the total time that has elapsed from cooking for
          the customers, and dequeue the customers at the front of the queue */
        totalCookTime += myQueue.peek().cookingTime;
        std::cout << "Group Name: " << myQueue.peek().groupName;
        std::cout << " - Total Cook Time for the Group: ";
        std::cout << totalCookTime << "\n";
        myQueue.dequeue();
        break;

      /* case 5: dequeue everyone */
      case 5:
      /* dequeue every customer from the queue, printing their information,
        including the total time that has elapsed from cooking for them */
      while(myQueue.isEmpty() == false){
        totalCookTime += myQueue.peek().cookingTime;
        std::cout << "Group Name: " << myQueue.peek().groupName;
        std::cout << " - Total Cook Time for the Group: ";
        std::cout << totalCookTime << "\n";
        myQueue.dequeue();
      }
      break;

      /* case 6: print goodbye and quit */
      case 6:
        std::cout << "Goodbye!\n";
        break;

      /* default case: quit */
      default:
        break;
    }
  }

  return 0;
}
