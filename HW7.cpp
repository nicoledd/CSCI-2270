// include libraries ///////////////////////////////////////////////////////////
#include <iostream>     // allows input and output
#include <fstream>      // allows file manipulation
#include <iomanip>
using namespace std;    // standard namespace

#include "HW7hashTable.hpp"

// hash table parametrized constructor /////////////////////////////////////////
HashTable::HashTable( int hashTableSize ){

  // initialize hash table size
  this->hashTableSize = hashTableSize;

  // initialize other variables
  this->numItems = 0;
  this->numCollisions = 0;

  // allocate new memory for hash table array of wordItem head pointers
  this->hashTable = new wordItem*[hashTableSize];

  // set all head pointers to null
  for( int idx = 0; idx < hashTableSize; idx++ ){
    hashTable[idx] = NULL;
  }

}

// hash table destructor ///////////////////////////////////////////////////////
HashTable::~HashTable(){
  // allocate temp node for searching linked list
  struct wordItem* temp = new wordItem;
  // allocate future node for deleting linked list
  struct wordItem* future = new wordItem;

  // iterate through each idx of hash table array
  for( int idx = 0; idx < this->hashTableSize; idx++ ){

    // if idx head pointer does not point to null, delete linked list
    if( this->hashTable[idx] != NULL ){

      // let temp point to head
      temp = this->hashTable[idx];

      // while temp is not null, iterate through list
      while( temp != NULL ){
        // let future point to temp->next
        future = temp->next;
        // delete temp
        delete temp;
        // let temp equal future
        temp = future;
      }

      // let head point to null
      this->hashTable[idx] = NULL;
    }
  }

}


// return hash value of input word /////////////////////////////////////////////
unsigned int HashTable::getHash( string word ){

  unsigned int hashValue = 5381;
  int length = word.length();

  for ( int i = 0; i < length; i++ ){
    hashValue = ( (hashValue<<5) + hashValue ) + word[i];
  }

  hashValue %= this->hashTableSize;
  return hashValue;

}

// search for input word ///////////////////////////////////////////////////////
wordItem* HashTable::searchTable( string word ){
    // allocate temp wordItem node for searching linked list
  struct wordItem* temp = new wordItem;

  // get hash value of word
  int hash_value = getHash(word);

  // if head pointer at hash_value does not point to null, iterate through list
  if( this->hashTable[hash_value] != NULL ){

    // let temp point to head
    temp = this->hashTable[hash_value];

    // while temp is not null, iterate through list
    while( temp != NULL ){

      // if word is found in list, return temp
      if( temp->word == word ) {
        return temp;
      }

      // traverse the list
      temp = temp->next;
    }
  }

  return NULL;
}


// check if word is already in hash table //////////////////////////////////////
bool HashTable::isInTable( string word ){
      // call searchTable function
  wordItem* temp = searchTable(word);

  // if search does not return null
  if( temp != NULL ) return true;
    // word is already in table
    // return true

  // if search return NULL
  else if( temp == NULL ) return false;
    // word is not already in table
    // return false

    return false;


}


// increment count of word item ////////////////////////////////////////////////
void HashTable::incrementCount( string word ){

  // call searchTable to search for word
  wordItem* temp = searchTable(word);

  // if word does not exist, return
  if( temp == NULL ) return;

  // if word exists, increment its count field
  if( temp != NULL ){
    temp->count++;
    return;
  }
}


// insert word into hash table /////////////////////////////////////////////////
void HashTable::addWord( string word ){

  // call isInTable
  int hash_value = 0;

  // increment numItems variable
  this->numItems++;

  // allocate new node
  wordItem* node = new wordItem;

  // initialize new node info
  node->word = word;
  node->count = 1;
  node->next = NULL;

  // call getHash to get its hashvalue, aka hash table index
  hash_value = getHash(word);


  // if there is a collision (head not pointing to null)
  if( this->hashTable[hash_value] != NULL ){
    // increment numCollisions variable
    this->numCollisions++;
    // let new node point to head node
    node->next = this->hashTable[hash_value];
    // let head point to new node
    this->hashTable[hash_value] = node;
  }

  // if there is no collision,
  if( this->hashTable[hash_value] == NULL ){
    // let head point to new node
    this->hashTable[hash_value] = node;
  }
}


// return num collisions ///////////////////////////////////////////////////////
int HashTable::getNumCollisions(){
  // return numCollisions
  return this->numCollisions;
}

int HashTable::getNumItems(){
  // return numItems;
  return this->numItems;
}

// return total num words //////////////////////////////////////////////////////
int HashTable::getTotalNumWords(){
      // allocate temp wordItem node for searching linked list
  struct wordItem* temp = new wordItem;
  int total_num_words = 0;

  // iterate through each idx of hash table
  for( int idx = 0; idx < this->hashTableSize; idx++ ){

    // if idx head pointer does not point to null
    // iterate through linked list, and add up every word->count
    if( this->hashTable[idx] != NULL ){

      // let temp point to head
      temp = this->hashTable[idx];

      // while temp is not null, iterate through list
      while( temp != NULL ){
        // add word->count
        total_num_words += temp->count;
        // and traverse the list
        temp = temp->next;
      }
    }
  }

  // return total num words
  return total_num_words;

}

// bubble sorts the wordItem array from the word that occurs most often to least
void sortArray( wordItem array[], int size ){
  int temp1 = 0;
  string temp;
  for( int i=0; i<size-1; i++ ){
    temp1 = array[i].count;
    for( int j=i+1; j<size; j++ ){
      if( temp1 < array[j].count ){
        temp = array[j].word;
        temp1 = array[j].count;
        array[j].word = array[i].word;
        array[j].count = array[i]. count;
        array[i].word = temp;
        array[i].count = temp1;
      }
    }
  }
}

// print top most frequent non-stop words //////////////////////////////////////
void HashTable::printTopN( int num_to_print ){
  // find n words with greatest count

  // create wordItems array
  wordItem array[this->numItems];
  int idx_arr = 0;

  // allocate temp wordItem node for searching linked list
  struct wordItem* temp = new wordItem;

  // iterate through each idx of hash table
  for( int idx = 0; idx < this->hashTableSize; idx++ ){

    // if idx head pointer does not point to null
    // iterate through linked list, and add each wordItem to array
    if( this->hashTable[idx] != NULL ){

      // let temp point to head
      temp = this->hashTable[idx];

      // while temp is not null, iterate through list
      while( temp != NULL ){
        // add wordItem to array
        array[idx_arr] = *temp;
        idx_arr++;
        // and traverse the list
        temp = temp->next;
      }
    }
  }

  // sort word item array by count
  sortArray( array, this->numItems );

  // probability of occurrence = word->count / total num of non-stopwords
  float prob = 0.0;
  float total_num_words = getTotalNumWords();

  // for int = 0 to int = num
  for( int idx = 0; idx < num_to_print; idx++ ){

    // cout word, and its probability of occurrence
    prob = (float)array[idx].count / total_num_words;

    cout << setprecision(4) << fixed << prob << " - " << array[idx].word << "\n";

    // re-initialize probability of occurrence to 0
    prob = 0;
  }
}



// load stopwords into the stopwords hash table ////////////////////////////////
void getStopWords( char *ignore_words_txt, HashTable &stopwords_table ){
  // initialize variables
  ifstream file;
  string word;

  // open ignoreWords.txt
  file.open( ignore_words_txt );

  // read ignoreWords.txt
  while( file >> word ){

    // call addWord function
    stopwords_table.addWord(word);

  }
  file.close();
}


// check table to see if a word is a stopword or not ///////////////////////////
bool isStopWord( string word, HashTable &stopwords_table){
    return stopwords_table.isInTable(word);
}


int main ( int argc, char *argv[] ) {

    // initialize command line arguments
  int num_words_to_print = stoi( argv[1] );
  string harry_potter_txt = argv[2];
  char* ignore_words_txt = argv[3];
  int hash_table_size = stoi( argv[4] );

  // create stopwords hash table
  HashTable stopwords_table(STOPWORD_TABLE_SIZE);

  // create non-stopwords hash table
  HashTable non_stopwords_table( hash_table_size );

  // store stopwords in a stopwords hash table
  // call getStopWords
  getStopWords( ignore_words_txt, stopwords_table );

  // store non-stopwords in non-stopwords hash table
  // read HarryPotter.txt
  ifstream file;
  string word;

  file.open( harry_potter_txt );

  while( file >> word ){

    if( isStopWord(word,stopwords_table) == false ){
        if( non_stopwords_table.isInTable(word) == true )
            non_stopwords_table.incrementCount(word);
        else
        non_stopwords_table.addWord(word);
    }

  }

    non_stopwords_table.printTopN(num_words_to_print);

  // print numCollisions
  cout << "#\n";
  cout << "Number of collisions: " << non_stopwords_table.getNumCollisions() << "\n";

  // print numItems in non-stopwords table, call getNumItems
  cout << "#\n";
  cout << "Unique non-stop words: " << non_stopwords_table.getNumItems() << "\n";

  // print total num words in stopwords table, call getTotalNumWords
  cout << "#\n";
  cout << "Total non-stop words: " << non_stopwords_table.getTotalNumWords() << "\n";

  file.close();
  return 0;
}
