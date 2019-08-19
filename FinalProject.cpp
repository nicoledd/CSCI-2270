// 2019.04.20
// FINAL PROJECT FOR DATA STRUCTURES

/* README
  - Another file associated with this program is Sequences.txt
  - What does this program do?
    - Sequences.txt consists a list of imaginary species & their genome
      sequences in the following format: [name] [sequence]
    - The program will ask you what your favorite species is
    - The program will output the following:
      1) The name of the species that shares the longest-common-substring
        with your favorite species
      2) The longest-common-substring that is shared between your favorite
        species, and the most similar species in the database
  - How to compile:
    g++ -std=c++11 FinalProject.cpp
    ./a Sequences.txt
*/


// include libraries ///////////////////////////////////////////////////////////
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
using namespace std;


// struct suffix ///////////////////////////////////////////////////////////////
// - structure to store information of each suffix
// - stores original index, ASCII ranks of the first and second suffix char,
//   and identity
struct suffix{

  // int originalIndex: the original index of a suffix
  // - for instance, the original index for the suffix "nana" which came from
  //   the string "banana", equals 2
  int originalIndex;

  // int rank[2]: stores the rank of the first and second suffix char
  // - rank is merely the ASCII value of the character
  int rank[2];

  // string identity: stores the hash-value identity of the suffix
  // - each suffix may come from a different sequence
  // - thus, we assign each suffix an 'identity' to keep track of which
  //   sequence this particular suffix originates from
  string identity;

  // suffix(): default constructor
  suffix();

  // suffix(int originalIndex, string identity): parametrized constructor
  suffix(int originalIndex, string identity);
};


// suffix::suffix() ////////////////////////////////////////////////////////////
// - default constructor for 'struct suffix'
// - let the values of originalIndex, rank[0], and rank[1] all become -1
suffix::suffix(){
  this->originalIndex = -1;
  this->rank[0] = -1;
  this->rank[1] = -1;
}


// suffix(int originalIndex, string identity) //////////////////////////////////
// - parametrized constructor for 'struct suffix'
// - assign the suffix an original index, and an identity
suffix::suffix(int originalIndex, string identity){
  this->originalIndex = originalIndex;
  this->identity = identity;
}


// bool compare(suffix a, suffix b) ////////////////////////////////////////////
// - this function compares 2 suffixes; returns 'true' if suffix a is smaller
// - used by the sort() function when building a suffix array
bool compare(suffix a, suffix b){

  // for the 2 suffixes, if the ASCII ranks for the first suffix char are equal
  //  - then compare the ASCII ranks for the second suffix char
  //  - otherwise, just compare the ASCII ranks for the first suffix char
  return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? true: false):
                                    (a.rank[0] < b.rank[0] ? true: false);
}




// vector<suffix> buildSuffixArray(string txt) /////////////////////////////////
// - given a string, builds and returns suffix array for that string
// - the suffix array will be an array of 'struct suffixes'
// - each element will contain both the original index of the suffix AND
//   the identity of the suffix
vector<suffix> buildSuffixArray(string txt){

  // initialize variables //////////////////////////////////////////////////////

  // initialize the suffix array that we are going to return
  // - the size of this array is the length of the string, because the number
  //   of suffixes that any string contains, is equal to the number of chars
  //   in that string
  vector<suffix> suffixArr;

  // an array of type 'struct suffix'
  // - we will use this suffixInfoArr[] to sort the suffixes alphabetically,
  //   before we push these into the vector suffixArr that we will return
  suffix suffixInfoArr[txt.length()];

  // originalIdxArr[originalIndex] = suffixInfoArrIdx
  // - this mapping is needed to get the next suffix
  int originalIdxArr[txt.length()];

  // the 'string txt' that we are building a suffix array for is actually
  // composed of 2 concatenated sequences
  //  - we want to keep track of which sequence each suffix is originally from
  //  - since there are 2 sequences, we assign 2 identities - 'blue' or 'green'
  //    to each suffix
  //  - 'blue' means that this suffix belongs to the first sequence, while
  //    'green' means that this sequence belongs to the second sequence
  string identityArr[2] = {"blue", "green"};
  int identityArrIdx = 0;

  // construct and sort suffixInfoArr[] ////////////////////////////////////////

  // for each suffix that exists in the 'string txt', compute its
  // original index, rank[0], rank[1], and identity
  for(int txtIdx = 0; txtIdx < txt.length(); txtIdx++){

    // store the original index of the suffix in 'int originalIndex'
    suffixInfoArr[txtIdx].originalIndex = txtIdx;

    // store the ASCII value of the first suffix character in rank[0]
    suffixInfoArr[txtIdx].rank[0] = txt[txtIdx] - 'a';

    // store the ASCII value of the second suffix character in rank[1]
    // - if the suffix is only one character long, meaning that the second
    //   suffix character doesn't exist, store rank[1] as -1
    suffixInfoArr[txtIdx].rank[1] = ((txtIdx + 1) < txt.length())?
                                      (txt[txtIdx + 1] - 'a'): -1;

    // store the identity of the suffix in 'string identity'
    //  - the suffixes from the first sequence will all be assigned 'blue'
    suffixInfoArr[txtIdx].identity = identityArr[identityArrIdx];

    // when a non-alphabetical letter is reached, this means we have reached
    // the second sequence
    //  - the suffixes from the second sequence will all be assigned 'green'
    if(isalpha(txt[txtIdx]) == false){
      identityArrIdx++;
    }
  }

  // sort the suffixes alphabetically according to their first two characters
  sort(suffixInfoArr, suffixInfoArr + txt.length(), compare);

  // sort suffixInfoArr[], continued ///////////////////////////////////////////

  // currently all suffixes are sorted by first 2 characters
  // - next, sort according to first 4 characters, then 8, and so on
  for(int k = 4; k < 2 * txt.length(); k = k*2){

    // initialize rank and prevRank
    int rank = 0;
    int prevRank = suffixInfoArr[0].rank[0];

    // assign 0 as new rank[0] to first suffix
    suffixInfoArr[0].rank[0] = rank;
    originalIdxArr[suffixInfoArr[0].originalIndex] = 0;

    // assign rank[0] for remaining suffixes
    for(int suffixInfoArrIdx = 1;
      suffixInfoArrIdx < txt.length();suffixInfoArrIdx++){

      // if rank[0] and rank[1] are same for curr suffix and its previous suffix,
      if(suffixInfoArr[suffixInfoArrIdx].rank[0] == prevRank
        && suffixInfoArr[suffixInfoArrIdx].rank[1] ==
        suffixInfoArr[suffixInfoArrIdx - 1].rank[1]){

        // then assign the same new rank to this curr suffix
        prevRank = suffixInfoArr[suffixInfoArrIdx].rank[0];
        suffixInfoArr[suffixInfoArrIdx].rank[0] = rank;
      }

      // else if rank[0] and rank[1] are NOT the same for curr suffix and
      // its previous suffix
      else{
        // then increment the new rank for this curr suffix
        prevRank = suffixInfoArr[suffixInfoArrIdx].rank[0];
        suffixInfoArr[suffixInfoArrIdx].rank[0] = ++rank;
      }

      // store in originalIdxArr[original index of the suffix], suffixInfoArrIdx
      originalIdxArr[suffixInfoArr[suffixInfoArrIdx].originalIndex] =
      suffixInfoArrIdx;
    }

    // for each curr suffix, also assign rank[1]
    for(int suffixInfoArrIdx = 0;
      suffixInfoArrIdx < txt.length(); suffixInfoArrIdx++){

      int nextIndex = suffixInfoArr[suffixInfoArrIdx].originalIndex + k / 2;

      suffixInfoArr[suffixInfoArrIdx].rank[1] = (nextIndex < txt.length()) ?
                      suffixInfoArr[originalIdxArr[nextIndex]].rank[0] : -1;
    }

    // sort suffixes according to first k characters
    sort(suffixInfoArr, suffixInfoArr + txt.length(), compare);
  }

  // construct and return final suffixArr vector ///////////////////////////////

  // now that the suffixInfoArr[] is sorted alphabetically, push all of these
  // sorted suffixes into the vector suffixArr, which we will return
  for(int suffixArrIdx = 0; suffixArrIdx < txt.length(); suffixArrIdx++){
    suffixArr.push_back(suffix(suffixInfoArr[suffixArrIdx].originalIndex,
                               suffixInfoArr[suffixArrIdx].identity));
  }

  // return the final constructed suffix array
  return suffixArr;
}





// vector<int> buildLCP(string txt, vector<int> suffixArr) /////////////////////
// - given a string and its suffix array, builds and returns its lcp array
// - lcp stands for 'longest common prefix'
vector<int> buildLCP(string txt, vector<suffix> suffixArr){

  // initialize the lcp array, which is of type 'int'
  // - the size of this array is the length of the string, because the number
  //   of suffixes that any string contains, is equal to the number of chars
  //   in that string
  vector<int> lcpArr(txt.length(), 0);

  // array to store the inverse of suffix array elements
  // - if suffixArr[0] = 5, then inverseSuffixArr[5] = 0
  // - this is used to get next suffix string from suffix array
  vector<int> inverseSuffixArr(txt.length(), 0);

  // place values in inverse suffix array
  for(int suffixArrIdx = 0; suffixArrIdx < txt.length(); suffixArrIdx++){
    inverseSuffixArr[suffixArr[suffixArrIdx].originalIndex] = suffixArrIdx;
  }

  // initialize length of lcp array
  int lcpValue = 0;

  // process all suffixes one by one starting from first suffix
  for(int inverseSuffixArrIdx = 0;
    inverseSuffixArrIdx < txt.length(); inverseSuffixArrIdx++){

    // if the current suffix is at n - 1, we don't have next substring to
    // compare with, which means the lcp value is simply zero (undefined)
    if(inverseSuffixArr[inverseSuffixArrIdx] == txt.length() - 1){
      lcpValue = 0;
      continue;
    }

    // nextIdx is the original index of the next suffixArr substring,
    // to be compared with curr suffixArr substring
    int nextIdx =
    suffixArr[inverseSuffixArr[inverseSuffixArrIdx] + 1].originalIndex;

    // start matching from k'th index, since at least k - 1 characters will match
    while(inverseSuffixArrIdx + lcpValue < txt.length()
          && nextIdx + lcpValue < txt.length()
          && txt[inverseSuffixArrIdx + lcpValue] == txt[nextIdx + lcpValue]){

      lcpValue++;
    }

    // place the lcp value for the curr suffix into the lcp array
    lcpArr[inverseSuffixArr[inverseSuffixArrIdx]] = lcpValue;

    // delete the starting character from the string
    if(lcpValue > 0){
      lcpValue--;
    }
  }

  // shift all array elements to right
  for(int lcpIdx = txt.length() - 1; lcpIdx > 0; lcpIdx--){
    lcpArr[lcpIdx] = lcpArr[lcpIdx - 1];
  }

  // return the complete lcp array
  return lcpArr;
}



// vector<string> readSpecies(string sequencesTxt) /////////////////////////////
// - reads all species names in Sequences.txt
// - stores them all into a speciesArr vector, and returns this vector
vector<string> readSpecies(string sequencesTxt){

  // initialize file
  ifstream file;
  string line;
  string word;

  // initialize speciesArr vector
  vector<string> speciesArr;

  // open Sequences.txt
  file.open(sequencesTxt);

  // store specie names in speciesArr vector
  while(getline(file, line)){
    for(int ch = 0; line[ch] != ' '; ch++){
      word += line[ch];
    }
    speciesArr.push_back(word);
    word = "";
  }
  file.close();

  // return complete speciesArr vector
  return speciesArr;
}



// vecotr<string> readSequences(string sequencesTxt) ///////////////////////////
// - reads all sequences in Sequences.txt
// - stores them all into a seqiemcesArr vector, and returns this vector
vector<string> readSequences(string sequencesTxt){

  // initialize file
  ifstream file;
  string line;
  string word;
  int idxSequence = 0;

  // open Sequences.txt
  file.open(sequencesTxt);

  // initialize sequencesArr vector
  vector<string> sequencesArr;

  // read species in Sequences.txt and store in sequencesArr[]
  while(getline(file, line)){
    for(int ch = 0; line[ch] != ' '; ch++){
      idxSequence++;
    }
    for(int ch = idxSequence + 1; line[ch] != '\0'; ch++){
      word += line[ch];
    }
    sequencesArr.push_back(word);
    word = "";
    idxSequence = 0;
  }
  file.close();

  // return complete sequencesArr vector
  return sequencesArr;
}



// string concatenateStrings(string a, string b) ///////////////////////////////
// - given two strings, concatenates them (while separating them using
//   special characters)
// - returns the resulting concatenated string
string concatenateStrings(string a, string b){
  return a + "#" + b + "$";
}


// void printArrays(vector<int> lcpArr, vector<suffix> suffixArr, string txt) //
// - for a given string, prints its lcp array, suffixes, identity, and index
// - I only used this when I was debugging
void printArrays(vector<int> lcpArr, vector<suffix> suffixArr, string txt){
  cout << "LCP value - suffix - identity - index\n";
  for(int arrIdx = 0; arrIdx < txt.length(); arrIdx++){
    cout << lcpArr[arrIdx] << " - ";
    for(int txtIdx = suffixArr[arrIdx].originalIndex;
      txt[txtIdx] != '\0'; txtIdx++){

      cout << txt[txtIdx];
    }
    cout << " - " << suffixArr[arrIdx].identity << " - " << arrIdx << "\n";
  }
  cout << "\n";
}

// struct node /////////////////////////////////////////////////////////////////
// - struct for a linked list node, to be used in hash table
struct node{
  // identity of node; either 'blue' or 'green'
  string identity;
  // number of times that identity appears within a sliding window
  int count = 0;
  // pointer to next node
  node* next;
};

// class HashTable /////////////////////////////////////////////////////////////
class HashTable{

private:
  // size of hash table, num of buckets
  int tableSize;
  // pointer to an array containing buckets (the hash table)
  node **hashTable;
  // creates new node, returns pointer to new node
  node* createNode(string key);

public:
  // parametrized constructor: sets size of hash table
  HashTable(int bsize);

  // hashes key into an index, returns index
  unsigned int hashFunction(string key);

  // inserts node into table, returns false if key already exists
  bool insertItem(string key);
  // search for key, return node if found, else return null
  node* searchItem(string key);

  // increments count of input key
  void incrementCount(string key);
  // set counts of all words in hash table to zero
  void initializeCount();
  // returns false if the count is zero for any node
  bool allIdentitiesInWindow();

  // displays hash table
  void printTable();
  // destructor: destroys hashtable
  ~HashTable();
};

// HashTable parametrized constructor //////////////////////////////////////////
// - allocates memory for new hash table
// - lets all elements point to null
// - inserts two nodes - 'green' and 'blue', to keep track of the suffixes
HashTable::HashTable(int bsize){
  // initialize table size
  this->tableSize = bsize;
  // allocate new memory for hash table array of nodes
  this->hashTable = new node*[bsize];
  // set all head pointers to null
  for(int idx = 0; idx < bsize; idx++){
    hashTable[idx] = NULL;
  }
  // insert 'green' and 'blue'
  insertItem("green");
  insertItem("blue");
}

// node* createNode(string key) ////////////////////////////////////////////////
// - creates new node, returns pointer to new node
node* HashTable::createNode(string key){
  // allocate new node
  node* newNode = new node;
  // put data in node
  newNode->identity = key;
  newNode->next = NULL;
  // return newNode
  return newNode;
}

// unisgned int hashFunction(string key) ///////////////////////////////////////
// - hashes key into an index, returns index
// - the identity 'blue' has an index of 0 in the table
// - the identity 'green' has an index of 1 in the table
unsigned int HashTable::hashFunction(string key){
  if(key == "blue"){
    return 0;
  }
  if(key == "green"){
    return 1;
  }
}

// bool insertItem(string key) /////////////////////////////////////////////////
// - inserts node into table, returns false if key already exists
bool HashTable::insertItem(string key){
  // allocate new node
  node* newNode = new node;
  newNode = createNode(key);
  // get key's hashValue
  int hashValue = hashFunction(key);
  // if there is a collision,
  if(this->hashTable[hashValue] != NULL){
    // let new node point to head node
    newNode->next = this->hashTable[hashValue];
    // let head point to new node
    this->hashTable[hashValue] = newNode;
    return false;
  }
  // if there is no collision,
  if(this->hashTable[hashValue] == NULL){
    // let head point to new node
    this->hashTable[hashValue] = newNode;
    return true;
  }
}

// void incrementCount(string key) /////////////////////////////////////////////
// - given a key, either 'green' or 'blue', increments the 'count' of that key
void HashTable::incrementCount(string key){
  // call searchTable to search for key
  node* temp = searchItem(key);
  // if that word does not exist, return
  if(temp == NULL){
    return;
  }
  // if word exists, increment its count field
  if(temp != NULL){
    temp->count++;
    return;
  }
}

// node* searchItem(string key) ////////////////////////////////////////////////
// - search for key, return node if found, else return null
node* HashTable::searchItem(string key){
  // allocate temp node for searching linked list
  node* temp = new node;
  // get hash value of key
  int hashValue = hashFunction(key);
  // if head pointer at hashValue does not point to null, iterate through list
  if(this->hashTable[hashValue] != NULL){
    // let temp point to head
    temp = this->hashTable[hashValue];
    // while temp is not null, iterate through list
    while(temp != NULL){
      // if key is found, return temp
      if(temp->identity == key){
        return temp;
      }
      // else traverse the list
      temp = temp->next;
    }
  }
  // return null if key not found
  return NULL;
}

// void initializeCount() //////////////////////////////////////////////////////
// - set the count of all words in hash table to zero
// - is called at the start of the allIdentitiesInWindow() function
void HashTable::initializeCount(){
  // allocate temp node for searching linked list
  struct node* temp = new node;
  // iterate through each idx of hash table array
  for(int idx = 0; idx < this->tableSize; idx++){

    // if idx head pointer does not point to null, set count to zero
    if(this->hashTable[idx] != NULL){
      // let temp point to head
      temp = this->hashTable[idx];
      // while temp is not null, iterate through list
      while(temp != NULL){
        // set count to zero
        temp->count = 0;
        temp = temp->next;
      }
    }
  }
}

// bool allIdentitiesInWindow() ////////////////////////////////////////////////
// - returns false if the count is zero for any identity
// - this is because a count of zero means that the identity has not appeared
//   within that window slide yet
bool HashTable::allIdentitiesInWindow(){
  // allocate temp node for searching linked list
  struct node* temp = new node;
  // iterate through each idx of hash table array
  for(int idx = 0; idx < this->tableSize; idx++){
    // if idx head pointer does not point to null, set count to zero
    if(this->hashTable[idx] != NULL){
      // let temp point to head
      temp = this->hashTable[idx];
      // while temp is not null, iterate through list
      while(temp != NULL){
        // set count to zero
        if(temp->count == 0){
          return false;
        }
        temp = temp->next;
      }
    }
  }
  return true;
}

// void printTable() ///////////////////////////////////////////////////////////
// - displays hash table
// - I only used this for debugging
void HashTable::printTable(){
  // allocate temp node for searching linked list
  struct node* temp = new node;
  // iterate through each idx of hash table array
  for(int idx = 0; idx < this->tableSize; idx++){
    // if idx head pointer does not point to null, print linked list
    if(this->hashTable[idx] != NULL){
      // let temp point to head
      temp = this->hashTable[idx];
      // while temp is not null, iterate through list
      while(temp != NULL){
        // print temp
        cout << temp->identity << " " << temp->count << endl;
        temp = temp->next;
      }
    }
  }
}

// HashTable destructor ////////////////////////////////////////////////////////
// - frees all memory associated with the hash table
HashTable::~HashTable(){
  // allocate temp node for searching linked list
  node* temp = new node;
  // allocate future node for deleting linked list
  node* future = new node;
  // iterate through each index of hash table
  for(int idx = 0; idx < this->tableSize; idx++){
    // if head pointer at index doesn't point to null, delete linked list
    if(this->hashTable[idx] != NULL){
      // let temp point to head
      temp = this->hashTable[idx];
      // while temp is not null, iterate through list
      while(temp != NULL){
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

// bool allIdentitiesInWindow() ////////////////////////////////////////////////
// - if all identities are within this particular window slide, return true
// - else if NOT all identites within this window slide, return false
bool allIdentitiesInWindow(vector<suffix> suffixArr, int windowStartIdx,
                            int windowEndIdx, HashTable &identityTable){

  // before analyzing this particular window slide, initialize all identity
  // "counts" in hash table to zero
  identityTable.initializeCount();

  // iterate through every index within this particular window slide
  // - evaluate the identity of each element, and keep track of the 'count'
  //   of each identity using the hash table
  for(int arrIdx = windowStartIdx; arrIdx <= windowEndIdx; arrIdx++){
    identityTable.incrementCount(suffixArr[arrIdx].identity);
  }

  // if NOT all identities are within this window, return false
  if(identityTable.allIdentitiesInWindow() == false){
    return false;
  }
  // if all identites are within this window, return true
  else if(identityTable.allIdentitiesInWindow() == true){
    return true;
  }
}

// int smallestIdx(int windowStartIdx, int windowEndIdx, vector<int> lcpArr) ///
// - given a window range for an lcpArr, finds and returns the index
//   of the smallest non-zero lcp value within that window slide
int smallestIdx(int windowStartIdx, int windowEndIdx, vector<int> lcpArr){
  // initialize min value in window slide
  int min = 100000;
  // initialize the index of the min value in window slide
  int minIdx = windowStartIdx;
  // iterate through the window slide to find smallest min value
  for(int idx = windowStartIdx + 1; idx <= windowEndIdx; idx++){
    if(lcpArr[idx] < min && lcpArr[idx] != 0){
      min = lcpArr[idx];
      minIdx = idx;
    }
  }
  // return the index of the min value in this particular window slide
  return minIdx;
}

// string windowSlide() ////////////////////////////////////////////////////////
// - given a concatenated string, its suffix array, its lcp array,
//   and a hash table
// - finds the largest lcp (longest common prefix) value between
//   the 2 sequences
// - uses the largest lcp value to find and return the 'longest
//   common substring'
string windowSlide(vector<int> lcpArr, vector<suffix> suffixArr,
                  string txt, HashTable &identityTable){

  // in order to implement a 'sliding window', we need to know the start
  // index and the end index of that window
  // - the start index is 2, because index 0 and 1 both start with special
  //   characters (remember that the suffix array is sorted alphabetically,
  //   and that special characters come before letters)
  // - the end index is 3, because our sliding window starts small
  int windowStartIdx = 2;
  int windowEndIdx = 3;

  // the temp 'index of the smallest non-zero lcp value' within each given
  // window slide
  int currFoundIdx = 0;

  // the 'index of the smallest non-zero lcp value' in the entire lcp array
  int foundIdx = 0;

  // the longest common substring that this function will return at the end
  // - how do we know which one is the longest common substring?
  // - we need to use the 'index of the smallest non-zero lcp value'
  string longestCommonSubstring;

  // let the window slide down the lcp array
  // - end while loop when the end of the lcp array is reached
  while(windowEndIdx < lcpArr.size() - 1){

    // increment windowEndIdx, until all identities are in this window
    while(allIdentitiesInWindow(suffixArr, windowStartIdx,
          windowEndIdx, identityTable) == false
          && windowEndIdx < lcpArr.size() - 1){

      windowEndIdx++;
    }

    // increment windowStartIdx, until NOT all identities are in this window
    windowStartIdx--;
    while(allIdentitiesInWindow(suffixArr, windowStartIdx,
          windowEndIdx, identityTable) == true){

      windowStartIdx++;
    }

    // we now know the start index AND the end index of our sliding window
    // - so, we can now evaluate all the elements within this window
    // - first, find the 'index of the smallest non-zero lcp value' THAT
    //  IS WITHIN THIS WINDOW SLIDE
    currFoundIdx = smallestIdx(windowStartIdx - 2, windowEndIdx, lcpArr);
    if(foundIdx == 0){
      foundIdx = currFoundIdx;
    }

    // now, compare this 'temp value' with our 'final value'
    // - this is to evaluate the 'index of the smallest non-zero lcp value'
    //   for the ENTIRE lcp array, not JUST within this particular window
    if(lcpArr[currFoundIdx] > lcpArr[foundIdx]){
      foundIdx = currFoundIdx;
    }
  }

  // read the 'longest common substring' from the given string
  // - START READING FROM: start at the string index of the longest
  //   common substring. How do we find this?
  // - We know the LCP INDEX of the 'smallest non-zero lcp value',
  //   which we can use to find its SUFFIX ARRAY INDEX,
  //   which we can use to find its ORIGINAL INDEX within the original string
  // - STOP READING AT: the number of characters we read in the string is equal
  //   to the VALUE at the LCP INDEX of the 'smallest non-zero lcp value'
  int numCharsRead = 0;
  for(int txtIdx = suffixArr[foundIdx].originalIndex;
      numCharsRead < lcpArr[foundIdx]; txtIdx++){

    if(isalpha(txt[txtIdx])){
      longestCommonSubstring += txt[txtIdx];
    }
    numCharsRead++;
  }

  // return the longest common substring
  return longestCommonSubstring;
}

// void displayMenu() //////////////////////////////////////////////////////////
// - displays a menu of choices for the user
void displayMenu(){
  cout << "========== Imaginary Species Database Menu ======================\n";
  cout << "1. Print all species\n";
  cout << "2. Find the species that is most similar to your favorite species\n";
  cout << "3. Quit\n";
}


// void printSpecies(vecotr<string> speciesArr, int speciesArrSize) ////////////
// - prints all species
void printSpecies(vector<string> speciesArr, int speciesArrSize){
  cout << "\nList of all species:\n";
  for(int arrIdx = 0; arrIdx < speciesArrSize; arrIdx++){
    cout << speciesArr[arrIdx] << "\n";
  }
  cout << "\n";
}

// bool getSpeciesIndex(vector<string> speciesArr, string favSpecies) /////////
// - iterates through species array to find the index of the user's
//   favorite species
// - return array index if user's species is found
// - return -1 if user's species is NOT found
int getSpeciesIndex(vector<string> speciesArr, string favSpecies){
  for(int arrIdx = 0; arrIdx < speciesArr.size(); arrIdx++){
    if(speciesArr[arrIdx] == favSpecies){
      return arrIdx;
    }
  }
  return -1;
}

// void displayIntro() /////////////////////////////////////////////////////////
// - background information for user
void displayIntro(){
  cout << "\n================= Hello user! =================================\n";
  cout << "You were recently stranded on an imaginary desert island.\n\n";

  cout << "You quickly realize that the species on this island are unlike\n";
  cout << "any you have seen before. They are called Imaginary Species.\n\n";

  cout << "Thankfully, you find an Imaginary Species database in your raft,\n";
  cout << "which you can use to analyze the creatures here. This database\n";
  cout << "conveniently contains a list of Imaginary Species, and their\n";
  cout << "corresponding genome sequences.\n\n";
}


// driver program //////////////////////////////////////////////////////////////
// takes in 1 command line argument: Sequences.txt
int main(int argc, char *argv[]){

  // initialize variables

  // user's choice
  string choice;

  // user's favorite species
  string favSpecies;
  int favSpeciesIdx = 0;
  int compareSpeciesIdx = 0;
  // index of species with dna most similar to user's input species
  int foundIdx = 0;

  // initialize "Sequences.txt"
  string sequencesTxt = argv[1];

  // store the temp longest-common-substring
  string tempLongestCommonSubstring;

  // store the final longest-common-substring
  string longestCommonSubstring;

  // stores the result when we concatenate 2 sequences
  string txt;

  // construct speciesArr vector and sequencesArr vector for Sequences.txt
  vector<string> speciesArr = readSpecies(sequencesTxt);
  vector<string> sequencesArr = readSequences(sequencesTxt);

  // construct hash table to keep track of suffix identities
  // - consists only of elements 'blue' and 'green'
  HashTable identityTable(2);

  // background information
  displayIntro();

  // while loop for getting user's choice
  while(choice != "3"){

    // if user does not quit, repeatedly display menu and get user's choice
    displayMenu();
    getline(cin, choice);

    // based on user's choice, switch between 3 cases:
    switch(stoi(choice)){

      // 1. Print all species
      // - print a list of all the species from Sequences.txt
      case 1:
      printSpecies(speciesArr, speciesArr.size());
      break;

      // 2. Find the species that is most similar to your favorite
      case 2:

      // get name of user's favorite species
      cout << "\nEnter your favorite species: ";
      getline(cin, favSpecies);

      // get index of user's favorite species
      favSpeciesIdx = getSpeciesIndex(speciesArr, favSpecies);

      // if favorite species doesn't exist in the database, break
      if(favSpeciesIdx == -1){
        cout << "Invalid input, please try again\n\n";
        break;
      }

      // else, find the species that shares the longest-common-substring
      // with the user's input species
      // - analyze the temp longest common substring for ALL firstStrIdx and
      //   incremented secondStrIdx
      // - store the longest-common-substring out of all of them, and keep the
      //   index for that one too
      while(compareSpeciesIdx < sequencesArr.size()){
        // don't compare the species with itself
        if(favSpeciesIdx != compareSpeciesIdx){

          // concatenate 2 adjacent sequences
          txt = concatenateStrings(sequencesArr[favSpeciesIdx],
                sequencesArr[compareSpeciesIdx]);

          // build suffix array and lcp array for txt
          vector<suffix> suffixArr = buildSuffixArray(txt);
          vector<int> lcpArr = buildLCP(txt, suffixArr);

          // find temp longest common substring
          tempLongestCommonSubstring = windowSlide(lcpArr, suffixArr,
                                      txt, identityTable);

          // find actual longest common substring
          if(compareSpeciesIdx == 1
            || tempLongestCommonSubstring.length()
            > longestCommonSubstring.length()){

            longestCommonSubstring = tempLongestCommonSubstring;
            foundIdx = compareSpeciesIdx;
          }
        }
        // increment this idx, to compare with next species in file
        compareSpeciesIdx++;
      }

      // print results
      cout << "The species that is most similar is: " << speciesArr[foundIdx];
      cout << "\n";
      cout << "The longest common substring is: " << longestCommonSubstring;
      cout << "\n\n";

      // re-initialize variables
      favSpecies = "";
      favSpeciesIdx = 0;
      compareSpeciesIdx = 0;
      foundIdx = 0;
      txt = "";
      tempLongestCommonSubstring = "";
      longestCommonSubstring = "";

      break;

      // 3. Quit
      // - if the user wants to quit, print "Goodbye" and end the program
      case 3:
      cout << "\nGoodbye!\n";
      break;

      // if the user enters anything other than '1', '2', or '3', it is an
      // invalid input
      default:
      cout << "\nInvalid input. Please try again.\n";
      break;
    }
  }

  // return main function
  return 0;
}
// end of program
