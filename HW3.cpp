/* Assignment 3 - Linked Lists
Communication Between Towers

OBJECTIVES
1. Create, traverse, add, reverse and delete from a linked list
2. Get practice implementing classes */

#include "HW3.hpp"




/* CountryNetwork default constructor
- generates an empty linked-list */
CountryNetwork::CountryNetwork(){
  this->head = NULL;
}




/* check if linked-list is empty
- return true if empty
- return false if not empty */
bool CountryNetwork::isEmpty(){
  /* if head points to null, list is empty */
  if(this->head == NULL){
    return true;
  }
  /* if head is NOT pointing to null, list is NOT empty */
  if(this->head != NULL){
    return false;
  }
}





/* search network for node with name 'countryName'
- returns a pointer to found node
- if not found, return null */
Country* CountryNetwork::searchNetwork(std::string countryName){

  /* temp pointer for traversing the list */
  Country* temp = this->head;

  /* before reaching the end, continue to traverse the linked list to find
    countryName */
  while(temp != NULL){
    /* if target Country is found, return pointer to found Country */
    if(temp->name == countryName){
      return temp;
    }
    /* else, continue to traverse the list */
    temp = temp->next;
  }

  /* if target not found, return null */
  return NULL;
}





/* insert new country to the network
- between the Country *previous and the Country after it
- if Country *previous is null, insert new country as the head */
void CountryNetwork::insertCountry(Country* previous, std::string countryName){

  /* allocate new Country named 'countryName' */
  Country* newCountry = new Country;
  newCountry->name = countryName;

  /* if Country* previous is NULL, let newCountry become the head */
  if(previous == NULL){
    /* let newCountry point to what the head pointer points to */
    newCountry->next = this->head;
    /* let head pointer point to newCountry */
    this->head = newCountry;
    std::cout << "adding: " << countryName << " (HEAD)\n";
    return;
  }

  /* otherwise, let newCountry point to what previous points to */
  newCountry->next = previous->next;
  /* let previous Country point to newCountry */
  previous->next = newCountry;
  std::cout << "adding: " << countryName << " (prev: " << previous->name << ")\n";
}







/* delete the Country with the specified name
- if this Country does not exist, print "Country does not exist." and return */
void CountryNetwork::deleteCountry(std::string countryName){

  /* allocate temp and prev Country pointers, and let them point to head */
  Country* temp = this->head;
  Country* prev = this->head;

  /* traverse the linked list to find countryName */
  while(temp->name != countryName){
    /* let prev become temp */
    prev = temp;

    /* if end of list is reached, countryName does not exist, so return */
    if(temp == NULL){
      std::cout << "Country does not exist.\n";
      return;
    }

    /* continue to traverse the list using temp */
    temp = temp->next;
  }

  /* if countryName is the head node, let head point to next node */
  if(temp == prev){
    this->head = temp->next;
  }
  /* otherwise, let prev point to temp->next */
  else{
    prev->next = temp->next;
  }

  /* delete countryName node */
  delete temp;
}






/* checks if valid input for prev country
- if valid input, return true
- else return false */
bool CountryNetwork::validCountry(std::string countryName) {

  /* pointer for searching linked list */
  Country* temp = this->head;

  // "First" is a valid input, so return true
  if(countryName == "First"){
    return true;
  }

  /* if list is empty, return false */
  if(isEmpty() == true){
    return false;
  }

  /* otherwise, traverse the list to find the prevCountry */
  while(temp->name != countryName){
    temp = temp->next;
    /* if end of list is reached and prevCountry has not been found,
      return false */
    if(temp->next == NULL && temp->name != countryName){
      return false;
    }
  }

  /* break out of while-loop when country is found; return true */
  return true;
}





/* deletes all Country nodes in the network, starting at the head Country */
void CountryNetwork::deleteEntireNetwork(){

  /* if linked-list is empty, return */
  if(this->head == NULL){
    return;
  }

  /* create current and next pointers for deleting list */
  Country* current = this->head;
  Country* next;

  /* while current has not reached the end of the list, continue to
    traverse the list */
  while(current != NULL){
    /* let next equal current->next */
    next = current->next;
    std::cout << "deleting: " << current->name << "\n";
    /* delete current node */
    delete current;
    /* let current become next */
    current = next;
  }

  /* let head point to null */
  this->head = NULL;
  std::cout << "Deleted network\n";
}




/* default setup for network */
void CountryNetwork::loadDefaultSetup(){
  /* first delete anything that the network currently contains */
  deleteEntireNetwork();
  /* then add the following countries to the network */
  insertCountry(NULL, "United States");
  insertCountry(searchNetwork("United States"), "Canada");
  insertCountry(searchNetwork("Canada"), "Brazil");
  insertCountry(searchNetwork("Brazil"), "India");
  insertCountry(searchNetwork("India"), "China");
  insertCountry(searchNetwork("China"), "Australia");
}







/* reverse the linked-list */
void CountryNetwork::reverseEntireNetwork(){

  /* initialize current, prev and next pointers */
  Country* prev = NULL;
  Country* next = NULL;
  Country* current = this->head;

  /* before reaching the end, continue to traverse the list */
  while(current!=NULL) {
    /* let next point to current->next */
    next = current->next;
    /* let current->next point to prev */
    current->next = prev;
    /* let prev equal current node */
    prev = current;
    /* let current equal next node */
    current = next;
  }

  /* let head pointer point to prev */
  this->head = prev;
}






/* transmitMsg
- traverse the linked-list from the head to the node with name 'receiver'.
- for each node, set its 'message' field to 'msg', increment its
  'numberMessages' field, and print its information */
void CountryNetwork::transmitMsg(std::string receiver, std::string msg) {

  /* if network is empty, print "Empty list" and return */
  if(this->head == NULL){
    std::cout << "Empty list\n";
    return;
  }

  /* else if network is not empty, create a temp Country pointer, and let it
    point to the network head */
  Country* temp = this->head;

  /* while temp pointer has not reached the receiver country, print information
    of the current country, and continue to traverse the linked-list network */
  while(temp->name != receiver){
    temp->message = msg;
    temp->numberMessages++;
    std::cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << "\n";
    temp = temp->next;
  }

  /* once the receiver country has been reached, print the same information
    for this receiver country */
  temp->message = msg;
  temp->numberMessages++;
  std::cout << temp->name << " [# messages received: " << temp->numberMessages << "] received: " << temp->message << "\n\n";
}





/* printPath
- If the list is empty, print "nothing in path" and return
- Else print the names of each node in the linked-list */
void CountryNetwork::printPath(){

  /* printing current country network */
  std::cout << "== CURRENT PATH ==\n";

  /* if network is empty, print "nothing in path" and return */
  if (this->head == NULL) {
    std::cout << "nothing in path\n";
    std::cout << "===\n";
    return;
  }

  /* else if network is not empty, create a temp Country pointer, and let it
    point to network head */
  Country *temp = this->head;

  /* while temp pointer has not reached NULL (end of linked-list), print the
    name of current country, and continue to traverse the list */
  while(temp != NULL){
    std::cout << temp->name << " -> ";
    temp = temp->next;
  }
  std::cout << "NULL\n";
  std::cout << "===\n";
}





/* display this menu before getting user input */
void displayMenu(){
    std::cout << "Select a numerical option:\n";
    std::cout << "+=====Main Menu=========+\n";
    std::cout << " 1. Build Network \n";
    std::cout << " 2. Print Network Path \n";
    std::cout << " 3. Transmit Message \n";
    std::cout << " 4. Add Country \n";
    std::cout << " 5. Delete Country \n";
    std::cout << " 6. Reverse Network\n";
    std::cout << " 7. Clear Network \n";
    std::cout << " 8. Quit \n";
    std::cout << "+-----------------------+\n";
    std::cout << "#> ";
}






/* driver function */
int main(int argc, char *argv[]){

  /* initialize variables and instantiate objects */
  CountryNetwork myNetwork;
  std::string choice, receiver, message, newCountry, prevCountry, delCountry;

  /* while user does not type "8", continue to read user input */
  while(choice != "8"){

    /* display menu and get user input */
    displayMenu();
    std::getline(std::cin, choice);

    /* switch cases based on user input */
    switch(stoi(choice)){

      /* load and print default country network */
      case 1:
        myNetwork.loadDefaultSetup();
        myNetwork.printPath();
        std::cout << "\n";
        break;

      /* print current country network */
      case 2:
        myNetwork.printPath();
        std::cout << "\n";
        break;

      /* send a message (input by user) to a country (chosen by user) */
      case 3:
        /* read name of country to send message to */
        std::cout << "Enter name of the country to receive the message: \n";
        std::getline(std::cin, receiver);
        /* read message to be sent */
        std::cout << "Enter the message to send: \n\n";
        std::getline(std::cin, message);
        /* transmit message */
        myNetwork.transmitMsg(receiver, message);
        break;

      /* create and insert a new country (input by user) into network */
      case 4:
        /* read name of new country */
        std::cout << "Enter a new country name: \n";
        std::getline(std::cin, newCountry);
        /* read name of country that the newCountry is to be inserted after */
        std::cout << "Enter the previous country name (or First): \n";
        std::getline(std::cin, prevCountry);

        /* if user types "First" then insert new country at head */
        if(prevCountry == "First"){
          std::cout << "\n";
          myNetwork.insertCountry(NULL, newCountry);
        }

        /* if prevCountry input is invalid, repeatedly ask user for a valid input */
        while(myNetwork.validCountry(prevCountry) == false){
          std::cout << "INVALID country...Please enter a VALID previous country name:\n";
          std::getline(std::cin, prevCountry);

          /* if user input is valid and is "First", insert new Country */
          if(prevCountry == "First") {
            std::cout << "\n";
            myNetwork.insertCountry(NULL, newCountry);
          }
        }

        /* once user input is valid, insert newCountry after prevCountry */
        if(prevCountry != "First"){
          std::cout << "\n";
          myNetwork.insertCountry(myNetwork.searchNetwork(prevCountry), newCountry);
        }

        /* print country network after newCountry has been inserted */
        myNetwork.printPath();
        std::cout<< "\n";
        break;

      /* delete a country from network */
      case 5:
        /* read name of the country that user wants to delete */
        std::cout << "Enter a country name: \n";
        std::getline(std::cin, delCountry);

        /* if this country does not exist, print "Country does not exist." */
        if(myNetwork.searchNetwork(delCountry) == NULL){
          std::cout << "Country does not exist.\n";
        }
        /* else if this country does exist, delete this country */
        if(myNetwork.searchNetwork(delCountry) != NULL){
          myNetwork.deleteCountry(delCountry);
        }

        /* print the current country network, regardless of whether deletion
          was successful or not */
        myNetwork.printPath();
        std::cout << "\n";
        break;

      /* 6. Reverse Network
        reverse the linked-list country network, and print the reversed result */
      case 6:
        myNetwork.reverseEntireNetwork();
        myNetwork.printPath();
        std::cout << "\n";
        break;

      /* 7. Clear Network
        delete the country network */
      case 7:
        myNetwork.deleteEntireNetwork();
        break;

      /* 8. Quit
        if user decides to quit, print the network, delete it, and exit */
      case 8:

        /* delete network */
        std::cout << "Quitting... cleaning up path: \n";
        myNetwork.printPath();
        myNetwork.deleteEntireNetwork();

        /* if network is successfully deleted, print "Path cleaned" */
        if(myNetwork.isEmpty() == true){
          std::cout << "Path cleaned\n";
        }
        /* if network not successfully deleted, print "Error: Path NOT cleaned" */
        else{
          std::cout << "Error: Path NOT cleaned\n";
        }
        std::cout << "Goodbye!\n";
        break;

      /* if user types an invalid input, print 'invalid input' */
      default:
        std::cout << "invalid input\n";
        break;
    }
  }

  return 0;
}
