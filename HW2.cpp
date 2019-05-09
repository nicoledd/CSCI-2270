/* Assignment 2 - Circular Queue

OBJECTIVES
1. Create, add to, delete from, and work with a queue implemented as an array */



#include "HW2.hpp"



/* generally I dislike using global variables, but I still used them because
  for this homework, the way the teacher's moved the queueFront and queueEnd
  indices was different from how I did it

  So the obvious solution is to create my own variables 'qHead' and 'qTail'
  and set the teacher's variables 'queueFront' and 'queueEnd' to equal
  my variables to save time and energy :P  */
bool qEmpty = true;
int qHead = -1;
int qTail = -1;




/* default constructor for the circular queue
- let both queueFront and queueEnd indices equal -1 */
ProducerConsumer::ProducerConsumer(){
  queueFront = -1;
  queueEnd = -1;
}




/* returns current size of the queue */
int ProducerConsumer::queueSize(){

  /* if the front and end indices are equal, then either the queue is empty,
    or it is full */
  if(qHead == qTail){
    if(qEmpty == true){
      return 0;
    }
    return SIZE;
  }

  /* otherwise, calculate and return the size */
  if(qHead < qTail){
    return qTail - qHead;
  }
  else{
    return (qTail) + (SIZE - qHead);
  }
}





/* return true if queue is empty, else return false */
bool ProducerConsumer::isEmpty(){
  return qEmpty;
}


/* return true if queue is full, else return false */
bool ProducerConsumer::isFull(){
  if(queueSize() == SIZE){
    return true;
  }
  else{
    return false;
  }
}





/* enqueues a new item */
void ProducerConsumer::enqueue(std::string item){

  /* if queue is already full and cannot add more items, simply return */
  if(isFull() == true){
    std::cout << "Queue full, cannot add new item";

    /* manipulating my variables vs. teacher's variables */
    if(qTail == -1){
      queueEnd = qTail;
    }
    else{
      queueEnd = qTail - 1;
    }
    queueFront = qHead;
    return;
  }

  /* if queue is initially empty, go into this for-loop to add the new item.
    also set qEmpty to false */
  if(qHead == -1 && qTail == -1){
    qHead = 0;
    qTail = 1;
    queue[0] = item;
    qEmpty = false;

    /* manipulating my variables vs. teacher's variables */
    if(qTail == -1){
      queueEnd = qTail;
    }
    else{
      queueEnd = qTail - 1;
    }
    queueFront = qHead;
    return;
  }

  /* if queue is NOT initially empty, go into this for-loop to add new item */
  if(qTail == SIZE - 1){
    qTail = 0;
    queue[qTail] = item;

    /* manipulating my variables vs. teacher's variables */
    if(qTail == -1){
      queueEnd = qTail;
    }
    else{
      queueEnd = qTail - 1;
    }
    queueFront = qHead;
    return;
  }


  /* add item, and increment queue tail index */
  queue[qTail] = item;
  qTail++;

  /* manipulating my variables vs. teacher's variables */
  if(qTail == -1){
    queueEnd = qTail;
  }
  else{
    queueEnd = qTail - 1;
  }
  queueFront = qHead;
  return;
}




/* dequeue */
void ProducerConsumer::dequeue(){

  /* if queue is empty, you cannot dequeue anything, so return */
  if(isEmpty() == true){
    std::cout << "Queue empty, cannot dequeue an item";
    return;
  }

  /* delete the front of queue */
  queue[qHead] = "";

  /* move head pointer to new correct place */
  qHead = (qHead + 1) % SIZE;

  /* if head and tail pointers meet, this means the queue has been emptied,
    so set qHead and qTail to -1 */
  if(qHead == qTail){
    qEmpty = true;
    qHead = -1;
    qTail = -1;
  }

  /* manipulation of my variables vs teacher's variables */
  if(qTail == -1){
    queueEnd = qTail;
  }
  else{
    queueEnd = qTail - 1;
  }
  queueFront = qHead;
}




/* returns the string at the front of the queue */
std::string ProducerConsumer::peek(){
  /* if queue is empty, return an empty string */
  if(qHead == -1 && qTail == -1){
    std::cout << "Queue empty, cannot peek";
    return "";
  }
  /* otherwise, return the string at the front */
  return queue[qHead];
}







/* menu that is to be repeatedly displayed until user chooses to quit */
void displayMenu(){
  std::cout << "*----------------------------------------*\n";
  std::cout << "Choose an option:\n";
  std::cout << "1. Producer (Produce items into the queue)\n";
  std::cout << "2. Consumer (Consume items from the queue)\n";
  std::cout << "3. Return the queue size and exit\n";
  std::cout << "*----------------------------------------*\n";
}






/* driver function */
int main(int argc, char const* argv[]){

  /* initialize string variables */
  std::string choice, numPro, numCon, itemPro, itemCon;

  /* instantiate the queue */
  ProducerConsumer myQueue;

  /* while user does not choose to quit, repeat this while-loop */
  while(choice != "3"){

    /* repeatedly display the menu and read user's choice */
    displayMenu();
    getline(std::cin, choice);

    /* switch cases based on user's choice */
    switch(stoi(choice)){

      /* case 1: enqueue */
      case 1:
        /* read the num of items the user wishes to enqueue */
        std::cout << "Enter the number of items to be produced:\n";
        getline(std::cin, numPro);

        /* read and enqueue the items */
        for(int i = 0; i < stoi(numPro); i++){
          std::cout << "Item" << i + 1 << ":\n";
          getline(std::cin, itemPro);
          myQueue.enqueue(itemPro);
        }
        break;

      /* case 2: dequeue */
      case 2:
        /* read the num of items the user wishes to dequeue */
        std::cout << "Enter the number of items to be consumed:\n";
        getline(std::cin, numCon);

        /* dequeue the items */
        for(int i = 0; i < stoi(numCon); i++){
          if(myQueue.isEmpty() == false) {
              std::cout << "Consumed: " << myQueue.peek() << "\n";
              myQueue.dequeue();
          }
          else{
            std::cout << "No more items to consume from queue\n";
          }
        }
        break;

      /* for both case 3 and the default case, break */
      case 3:
        break;

      default:
        break;
    }
  }

  /* print the num of items in the queue and exit */
  std::cout << "Number of items in the queue:" << myQueue.queueSize();
  return 0;
}
