#pragma once
#include <iostream>



/* struct for each node in the linked list */
struct Operand{
  /* int value stored in node */
  float number;
  /* pointer to next node in stack */
  Operand* next;
};



/* RPN calculator linked-list class */
class RPNCalculator{
  private:
    /* pointer to the top of the stack */
    Operand* stackHead;
  public:
    /* constructor and destructor */
    RPNCalculator();
    ~RPNCalculator();
    /* return true if stack is empty */
    bool isEmpty();
    /* push and pop stack */
    void push(float);
    void pop();
    /* returns a pointer to top node of stack */
    Operand* peek();
    Operand* getStackHead(){return this->stackHead;}
    /* when the user inputs '+' or '*', computes the result */
    bool compute(std::string);
};
