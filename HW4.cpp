/* Assignment 4 - Stack

OBJECTIVES
1. Create, add to, delete from, and work with a stack implemented as
  a linked list */



#include "HW4.hpp"
using namespace std;




/* stack constructor, let head point to null */
RPNCalculator::RPNCalculator(){
  this->stackHead = NULL;
}




/* return true if stack is empty */
bool RPNCalculator::isEmpty(){
  /* if the head points to null, return true. else, return false */
  if(this->stackHead == NULL){
    return true;
  }
  return false;
}




/* function to push into stack */
void RPNCalculator::push(float num){
  /* allocate new Operand node and put info into it */
  Operand* newOperand = new Operand;
  newOperand->number = num;

  /* let the new node point to what the head points to */
  newOperand->next = this->stackHead;
  /* let the head point to this new node */
  this->stackHead = newOperand;
}






/* function to pop from stack */
void RPNCalculator::pop(){

  /* if the stack is empty, cannot pop, so return */
  if(this->stackHead == NULL){
    std::cout << "Stack empty, cannot pop an item.";
    return;
  }

  /* allocate temp node for deletion */
  Operand* temp = new Operand;
  /* let temp point to the head node */
  temp = this->stackHead;
  /* let head point to the node AFTER the head node */
  this->stackHead = temp->next;
  /* delete the head node */
  delete temp;
}





/* stack destructor; pop everything */
RPNCalculator::~RPNCalculator(){
  while(!isEmpty()){
    pop();
  }
}





/* returns head pointer */
Operand* RPNCalculator::peek(){
  if(isEmpty() == true){
    std::cout << "Stack empty, cannot peek.\n";
  }
  return this->stackHead;
}






/* perform calculations */
bool RPNCalculator::compute(string symbol){

  /* result of calculations */
  float result = 0.0;

  /* if symbol is invalid, return false */
  if(symbol != "*" && symbol != "+"){
    std::cout << "err: invalid operation\n";
    return false;
  }

  /* if stack is empty, return false */
  if(this->stackHead == NULL){
    std::cout << "err: not enough operands\n";
    return false;
  }

  /* if stack has only one item, return false */
  if(this->stackHead->next == NULL){
    std::cout << "err: not enough operands\n";
    return false;
  }

  /* multiply or add stack numbers */
  if(symbol == "*"){
    result = this->stackHead->number * this->stackHead->next->number;
  }
  if(symbol == "+"){
    result = this->stackHead->number + this->stackHead->next->number;
  }

  /* pop stack numbers, push result into stack, and return true */
  pop();
  pop();
  push(result);
  return true;
}




/* returns true if input is a number, else returns false */
bool isNumber(std::string s){

  if(s.size() == 1 && s == "-"){
    return false;
  }

  if(s.size() > 1 && s[0] == '-'){
    s = s.substr(1);
  }

  bool point = false;

  for(int i = 0; i < s.size(); i++){
    if(!isdigit(s[i]) && s[i]!='.'){
      return false;
    }
    if(s[i]=='.' && !point){
      point = true;
    }
    if(s[i]=='.' && point){
      return false;
    }
  }
  return true;
}




/* also checks if input is a number */
/*
bool isNumber(std::string s){
  int digit = s.length();
  int count = 0;
  bool decimalAppears = false;

  for(int i=0; i<digit; i++){
    if (s[i] == '.') decimalAppears=true;
  }

  for(int i=0; i<digit; i++) {
      if (s[i] == '0' || s[i] == '1' || s[i] == '2'
          || s[i] == '3' || s[i] == '4' || s[i] == '5'
          || s[i] == '6' || s[i] == '7' || s[i] == '8'
          || s[i] == '9' && s[i] != '.') count++;
  }

  if (decimalAppears==true) digit--;

  if (count == digit) return true;
  else return false;
}
*/




/* driver function */
int main(){

  /* initialize variables for calculations */
  std::string input;

  /* instantiate a stack for calculations */
  RPNCalculator myStack;

  std::cout << "Enter the operators and operands ('+', '*') in a postfix format\n";

  /* repeatedly ask user for input until user inputs "=" */
  while(1){

    /* read user input */
    std::cout << "#> ";
    std::cin >> input;

    /* break out of while-loop if user inputs "=" */
    if(input == "="){
      break;
    }


    /* if input is a number, push into stack */
    if(isNumber(input) == true ){
      myStack.push(stof(input));
    }

    /* if input is an operator, then compute */
    if (input == "+" || input == "*"){
        myStack.compute(input);
    }
  }

  /* if stack is empty, don't do anything */
  if(myStack.isEmpty() == true){
    std::cout << "No operands: Nothing to evaluate";
  }

  /* if invalid expression, also don't do anything */
  else if(input != "*" && input != "+"){
    std::cout << "Invalid expression";
  }

  /* else, compute the result and print it */
  else{
    std::cout << myStack.getStackHead()->number << "\n";
  }

  return 0;
}

// end of program
