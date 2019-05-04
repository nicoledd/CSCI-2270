#include "RPNCalculator.hpp"
using namespace std;

RPNCalculator::RPNCalculator(){ // RPNCalculator() constructor function
  this->stackHead = NULL;   // creates an empty linked list, head points to NULL
}

bool RPNCalculator::isEmpty(){                     // bool isEmpty()
  bool empty = true;                // is the stack empty?
  if ( this->stackHead == NULL ) {  // if the head points to NULL
    return true;                    // list is empty, return true
  }                                 // otherwise
  if ( this->stackHead != NULL ) {  // if the head does NOT point to NULL
    return false;                   // list is NOT empty, return false
  }
}

void RPNCalculator::push( float num ){  // void push(float num)
  Operand* newOperand = new Operand;  // create new node
  newOperand->number = num;           // set data for new node
  newOperand->next = this->stackHead; // new node points to head node
  this->stackHead = newOperand;       // head pointer points to new node
  return;
}

void RPNCalculator::pop(){     // void pop()
  if(this->stackHead == NULL){  // if stack is empty
    cout << "Stack empty, cannot pop an item.";// cout stack is empty
    return;                     // and return
  }                             // if stack is not empty
  Operand* temp = new Operand;  // create temp node
  temp = this->stackHead;       // let temp node point to head node
  this->stackHead = temp->next; // let head point to node after head node
  delete temp;                  // delete head node
}

RPNCalculator::~RPNCalculator(){       // ~RPNCalculator()
  while(!isEmpty()) {   // while the stack is not empty
    pop();              // pop items from the stack
  }
}

Operand* RPNCalculator::peek(){                // Operand* peek()
  if(this->stackHead == NULL){  // if stack is empty
    cout << "Stack empty, cannot peek.\n";  // cout stack is empty
    return NULL;                // and return NULL
  }
  return this->stackHead;       // else return next of stackHead pointer
}

// COMPUTE
bool RPNCalculator::compute(string symbol){ //bool computer(string symbol)

  if ( symbol!="*" && symbol!="+" ) { // if symbol isn't * or +
    cout << "err: invalid operation\n";
    return false;                     // return false
  }

  if ( this->stackHead == NULL ) {        // if stack is empty
    cout << "err: not enough operands\n"; // cout stack is empty
    return false;                         // and return false
  }

  if ( this->stackHead->next == NULL) {   // if stack has only one item
    cout << "err: not enough operands\n"; // cout stack doesn't have enough
    return false;                         // return false
  }

  float result=0.0;     // initialize float variable
  float number1 = 0.0;  // initialize float variable number1
  float number2 = 0.0;  // initialize float variable number2

  number1 = this->stackHead->number;       // number1 equals top of stack number
  number2 = this->stackHead->next->number; // number2 equals next stack item num

  if( symbol == "*" ){          // if symbol is multiplication
    result = number1 * number2; // multiply number1 and number2
  }
  if( symbol == "+" ){          // if symbol is addition
    result = number1 + number2; // add number1 and number2
  }
  pop();        // pop number1
  pop();        // pop number2
  push(result); // and push the result into stack
  return true;  // return true
}



bool isNumber(string s){   // check if input is a number
  if(s.size() == 1 && s == "-") { //
    return false;
  }
  if(s.size() > 1 && s[0] == '-') {
    s = s.substr(1);
  }
  bool point = false;
  for(int i=0; i<s.size(); i++){
    if( !isdigit(s[i]) && s[i]!='.' ) {
      return false;
    }
    if( s[i]=='.' && !point) {
      point = true;
    }
    if( s[i]=='.' && point) {
      return false;
    }
  }
  return true;
}

bool isNumber(string s){          // check if input is a number
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


int main(){

  RPNCalculator calculator; // declare stack to hold operands
  string input;
  string valid;

  cout << "Enter the operators and operands ('+', '*') in a postfix format\n";
  while(1){
    cout << "#> ";
    cin >> input;
    // end function
    if ( input == "=" ) {
      break;
    }
    // if input is a number
    if ( isNumber(input) == true ){
      calculator.push( stof(input) );
    }
    // if input is an operator
    else if (input == "+" || input == "*" ) {
        calculator.compute(input);
    }
    valid = input;
  }

  float output = 0.0;
  if ( calculator.isEmpty() == true ){
    cout << "No operands: Nothing to evaluate";
  }

  else if (valid != "*" && valid != "+") {
      cout << "Invalid expression";
  }

  else {
    output = calculator.getStackHead() -> number;
    cout << output << endl;
  }

  return 0;
}

// end of program
