#include "HW4producerConsumer.hpp"
#include <iostream>
using namespace std;

bool q_empty = true;
int q_head = -1;
int q_tail = -1;

ProducerConsumer::ProducerConsumer(){
  queueFront = -1;
  queueEnd = -1;
}


int ProducerConsumer::queueSize(){
  if ( q_head == q_tail ) { // if head and tail pointers meet
    if (q_empty==true) return 0;  // if queue is empty, return size=0
    return SIZE;  // if queue is full, return size=SIZE
  }
  if ( q_head < q_tail ) {
    return q_tail-q_head;
  }
  else{
    return (q_tail) + (SIZE-q_head);
  }
}

bool ProducerConsumer::isEmpty(){
  return q_empty;
}

bool ProducerConsumer::isFull(){
  if ( queueSize() == SIZE ) {
    return true;
  }
  else{
    return false;
  }
}

void ProducerConsumer::enqueue(string item){
  if( isFull()==true ){
    cout << "Queue full, cannot add new item";
    if(q_tail==-1) queueEnd = q_tail;
    else queueEnd = q_tail - 1;
    queueFront = q_head;
    return;
  }
  if(q_head==-1 && q_tail==-1){
    q_head = 0;
    q_tail = 1;
    queue[0]=item;
    q_empty = false;
    if(q_tail==-1) queueEnd = q_tail;
    else queueEnd = q_tail - 1;
    queueFront = q_head;
    return;
  }
  if(q_tail==SIZE-1){
    q_tail=0;
    queue[q_tail]=item;
    if(q_tail==-1) queueEnd = q_tail;
    else queueEnd = q_tail - 1;
    queueFront = q_head;
    return;
    }
  queue[q_tail]=item;
  q_tail++;
  if(q_tail==-1) queueEnd = q_tail;
  else queueEnd = q_tail - 1;
  queueFront = q_head;
  return;
}

void ProducerConsumer::dequeue(){
  if( isEmpty()==true ){
    cout << "Queue empty, cannot dequeue an item";
    return;
  }
  queue[q_head]=""; // delete head item
  // move head pointer
  q_head = ( q_head + 1 ) % SIZE;

  if ( q_head == q_tail ) { // if head and tail pointers meet
    q_empty = true; // queue is empty
    q_head = -1;
    q_tail = -1;
  }

  // changed
  if(q_tail==-1) queueEnd = q_tail;
  else queueEnd = q_tail - 1;
  queueFront = q_head;
}


string ProducerConsumer::peek(){
  if(q_head==-1 && q_tail==-1){
    cout << "Queue empty, cannot peek";
    return "";
  }
  return queue[q_head];
}


void menu(){
  cout << "*----------------------------------------*\n";
  cout << "Choose an option:\n";
  cout << "1. Producer (Produce items into the queue)\n";
  cout << "2. Consumer (Consume items from the queue)\n";
  cout << "3. Return the queue size and exit\n";
  cout << "*----------------------------------------*\n";
}

int main(int argc, char const* argv[]){

  ProducerConsumer market;
  string choice;
  string numPro;
  string numCon;
  string itemPro;
  string itemCon;

  while ( choice != "3" ) {

    menu();
    getline(cin, choice);

    switch( stoi(choice) ){

      case 1:
      cout << "Enter the number of items to be produced:\n";
      getline(cin,numPro);
      for(int i=0; i<stoi(numPro); i++){
        cout << "Item" << i+1 << ":\n";
        getline(cin,itemPro);
        market.enqueue(itemPro);
      }
      break;

      case 2:
      cout << "Enter the number of items to be consumed:\n";
      getline(cin,numCon);
      for(int i=0; i<stoi(numCon); i++) {
        if(market.isEmpty()==false) {
            cout << "Consumed: " << market.peek() << "\n";
            market.dequeue();
        }
        else cout << "No more items to consume from queue\n";
      }
      break;

      case 3:
      break;

      default:
      break;
    }
  }

  cout << "Number of items in the queue:" << market.queueSize();
  return 0;
}
