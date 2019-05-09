#pragma once
#include <iostream>


/* max queue size */
const int SIZE = 20;


/* queue class */
class ProducerConsumer{
  private:
    /* the index in queue[] that will be dequeued next */
    int queueFront;
    /* the index in queue[] that was most recently enqueued */
    int queueEnd;
    /* circular queue */
    std::string queue[SIZE];
  public:
    /* default constructor */
    ProducerConsumer();
    /* return true if queue is empty */
    bool isEmpty();
    /* return true if queue is full */
    bool isFull();
    /* enqueue and dequeue */
    void enqueue(std::string);
    void dequeue();
    /* return size of queue */
    int queueSize();
    /* returns queue front and queue end indices */
    int getQueueFront(){return queueFront;}
    int getQueueEnd(){return queueEnd;}
    /* returns a pointer to the string value at front of queue */
    std::string* getQueue(){return queue;}
    /* returns the string value at front of queue */
    std::string peek();
};
