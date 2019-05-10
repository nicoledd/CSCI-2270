#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

#include <iostream>
#include <fstream>





/* a struct to store customer information */
struct GroupNode{
  /* name of customer's group */
  std::string groupName;
  /* size of customer's group */
  int groupSize;
  /* time needed to finish cooking for this customer */
  int cookingTime;
};





/* class for priority queue */
class PriorityQueue{

  private:
    /* purpose is to maintain heap properties, by swapping given node with its
      parent if neccessary */
    void repairUpward(int);
    /* purpose is to maintain heap properties, by swapping given node with its
      child if necessary */
    void repairDownward(int);
    /* the array used to implement the priority queue */
    GroupNode* priorityQueue;
    /* the current size of the queue */
    int currentQueueSize;
    /* the max capacity of the queue */
    int maxQueueSize;

  public:
    /* parametrized constructor and destructor */
    PriorityQueue(int queueSize);
    ~PriorityQueue();
    /* enqueue and dequeue */
    void enqueue(std::string, int, int);
    void dequeue();
    /* return the name of the group at the front of queue */
    GroupNode peek();
    /* checks if queue is full or empty */
    bool isFull();
    bool isEmpty();
};

#endif
