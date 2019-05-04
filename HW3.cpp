#include <iostream>
using namespace std;



struct Country {
  string name;
  string message;
  int numberMessages=0;
  Country *next;
};




class CountryNetwork {

private:
  Country* head = NULL;

public:

// check if linked list is empty
bool isEmpty(){
  if ( this->head == NULL ) return true;
  return false;
}





Country* searchNetwork ( string countryName ) {
  // return NULL if empty
  Country* target = this->head;
  // traverse the linked list to find countryName
  while ( target != NULL ) {
    if( target->name == countryName ) return target;
    target = target->next;
  }
  return NULL;
}




// find the target object "previous", insert new country "countryName" after it
void insertCountry ( Country* previous, string countryName ) {
  // construct a new country named <countryName>
  Country* newCountry = new Country;
  newCountry->name = countryName;
  // if the target object is the head, insert new country at head
  if ( previous == NULL ) {
    newCountry->next = this->head;  // let new point to null
    this->head = newCountry;        // let head point to new
    cout << "adding: " << countryName << " (HEAD)\n";
  }
  else {
    newCountry->next = previous->next;
    previous->next = newCountry;
    cout << "adding: " << countryName << " (prev: " << previous->name << ")\n";
  }
  return;
}






void deleteCountry ( string countryName ) {

  // create target pointer which becomes head
  Country* target = this->head;
  Country* pre = this->head;
  // traverse the linked list to find countryName
  while ( target->name != countryName ) {
    pre = target;
    if (target == NULL) {
      cout << "Country does not exist.\n";
      return;
    }
    target = target->next;
  }
  // if target is the first node
  if ( target == pre ) this->head = target->next;
  else pre->next = target->next;
  // delete found country
  delete target;
  return;

}

bool prevCountryExists(string prevCountry) {
  Country*target = this->head;
  // if user wants country to be First, return countryExists==true
  if(prevCountry=="First") return true;
  // if list is empty, return countryExists==false
  if (this->head ==NULL) return false;
  // traverse list to find country
  while(target->name != prevCountry) {
    target = target->next;
    // if country is not found, return countryExists==false
    if (target->next==NULL && target->name !=prevCountry) return false;
  }
  // if country is found, return countryExists==true
  return true;
}



void deleteEntireNetwork(){
  if (this->head == NULL) {
    return;
  }
  Country* current = this->head;
  Country* next;
  while(current!=NULL) {
    next = current->next;
    cout << "deleting: " << current->name << "\n";
    delete current;
    current = next;
  }
  this->head = NULL;
  cout << "Deleted network\n";
}


void loadDefaultSetup(){
  string UnitedStates = "United States";
  string Canada = "Canada";
  string Brazil = "Brazil";
  string India = "India";
  string China = "China";
  string Australia = "Australia";
  deleteEntireNetwork();
  insertCountry( NULL, UnitedStates );
  insertCountry( searchNetwork(UnitedStates), Canada );
  insertCountry( searchNetwork(Canada), Brazil );
  insertCountry( searchNetwork(Brazil), India );
  insertCountry( searchNetwork(India), China );
  insertCountry( searchNetwork(China), Australia );
}



// reverse country network
void reverseEntireNetwork(){
  // initialize current, prev and next pointers
  Country *prev = NULL;
  Country *current = head;
  Country *next = NULL;
  while(current!=NULL) {
    next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  head = prev;
}


void transmitMsg(string receiver, string msg) {
  if (this->head == NULL) {
    cout << "Empty list\n";
    return;
  }
  Country* current = this->head;
  while(current->name != receiver){
    current->message = msg;
    current->numberMessages++;
    cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << "\n";
    current=current->next;
  }
  current->message = msg;
  current->numberMessages++;
  cout << current->name << " [# messages received: " << current->numberMessages << "] received: " << current->message << "\n\n";
}

void printPath(){
  cout << "== CURRENT PATH ==\n";
  if (this->head == NULL) {
    cout << "nothing in path\n";
    cout << "===\n";
    return;
  }
  Country *current = this->head;
  while(current != NULL) {
    cout << current->name << " -> ";
    current = current->next;
  }
  cout << "NULL\n";
  cout << "===\n";
}


};

void displayMenu ( ) {
    cout << "Select a numerical option:\n";
    cout << "+=====Main Menu=========+\n";
    cout << " 1. Build Network \n";
    cout << " 2. Print Network Path \n";
    cout << " 3. Transmit Message \n";
    cout << " 4. Add Country \n";
    cout << " 5. Delete Country \n";
    cout << " 6. Reverse Network\n";
    cout << " 7. Clear Network \n";
    cout << " 8. Quit \n";
    cout << "+-----------------------+\n";
    cout << "#> ";
}


int main ( int argc, char *argv[] ){

  CountryNetwork world;
  string choice;
  string receiver;
  string msg;
  string newCountry;
  string prevCountry;

  while( choice != "8" ) {
    displayMenu();
    getline(cin,choice);
    switch ( stoi(choice) ) {

      case 1:
      world.loadDefaultSetup();
      world.printPath();
      cout << "\n";
      break;


      case 2:
      world.printPath();
      cout << "\n";
      break;

      case 3:
      cout << "Enter name of the country to receive the message: \n";
      getline(cin,receiver);
      cout << "Enter the message to send: \n\n";
      getline(cin, msg);
      world.transmitMsg(receiver,msg);
      break;

      case 4:
      cout << "Enter a new country name: \n";
      getline(cin,newCountry);
      cout << "Enter the previous country name (or First): \n";
      getline(cin,prevCountry);
      if(prevCountry=="First") {  //insert at head if user types first
        cout << "\n";
        world.insertCountry( NULL, newCountry );
      }
      // check if prevCountry exists or not
      while(world.prevCountryExists(prevCountry)==false){
        cout << "INVALID country...Please enter a VALID previous country name:\n";
        getline(cin,prevCountry);
        if(prevCountry=="First") {
          cout << "\n";
          world.insertCountry( NULL, newCountry );
        }
      }
      if(prevCountry!="First") {
        cout << "\n";
        world.insertCountry( world.searchNetwork(prevCountry),newCountry );
      }
      world.printPath();
      cout<< "\n";
      break;

      case 5:
      cout << "Enter a country name: \n";
      getline(cin,newCountry);
      if(world.prevCountryExists(newCountry)==false){
        cout << "Country does not exist.\n";
      }
      if(world.prevCountryExists(newCountry)==true) world.deleteCountry(newCountry);
      world.printPath();
      cout << "\n";
      break;

      case 6:
      world.reverseEntireNetwork();
      world.printPath();
      cout << "\n";
      break;

      case 7:
      world.deleteEntireNetwork();
      break;

      case 8:
      cout << "Quitting... cleaning up path: \n";
      world.printPath();
      world.deleteEntireNetwork();
      if ( world.isEmpty() == true ) cout << "Path cleaned\n";
      else cout << "Error: Path NOT cleaned\n";
      cout << "Goodbye!\n";
      break;

      default:
      cout << "invalid input\n";
      break;
    }

  }


  return 0;
}
