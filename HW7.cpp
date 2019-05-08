/* Assignment 7 - Hash Tables

OBJECTIVES
1. Use a hash function
2. Store data in a chained hash table (Separate Chaining)
2. Search for data in a hash table */





#include "HW7.hpp"




/* HashTable parametrized constructor */
HashTable::HashTable(int hashTableSize){

  /* initialize hash table size */
  this->hashTableSize = hashTableSize;

  /* initialize 'numItems' and 'numCollisions' fields */
  this->numItems = 0;
  this->numCollisions = 0;

  /* allocate memory for a hashTable of wordItem head pointers */
  this->hashTable = new wordItem*[hashTableSize];

  /* set all head pointers to null */
  for(int idx = 0; idx < hashTableSize; idx++){
    hashTable[idx] = NULL;
  }
}







/* HashTable destructor */
HashTable::~HashTable(){

  /* allocate temp nodes for iterating through linked-list */
  wordItem* temp = new wordItem;
  wordItem* futur = new wordItem;

  /* iterate through the hashtable */
  for(int idx = 0; idx < this->hashTableSize; idx++){

    /* if the list exists at that hashtable index, delete it */
    if(this->hashTable[idx] != NULL){

      /* let temp point to head */
      temp = this->hashTable[idx];

      /* while temp is not null, iterate through list */
      while(temp != NULL){
        /* let futur point to temp->next, delete temp, and let temp equal futur */
        futur = temp->next;
        delete temp;
        temp = futur;
      }

      /* let head point to null */
      this->hashTable[idx] = NULL;
    }
  }
}






/* returns the hash value of input word */
unsigned int HashTable::getHash(std::string word){

  unsigned int hashValue = 5381;

  for(int i = 0; i < word.length(); i++){
    hashValue = ((hashValue << 5) + hashValue) + word[i];
  }

  hashValue %= this->hashTableSize;
  return hashValue;
}







/* search for input word */
wordItem* HashTable::searchTable(std::string word){

  // allocate temp wordItem node for searching linked list
  wordItem* temp = new wordItem;

  // if linked-list is empty, return null
  if(this->hashTable[getHash(word)] == NULL){
    return NULL;
  }

  /* let temp pointer point to head of list */
  temp = this->hashTable[getHash(word)];

  /* traverse the list */
  while(temp != NULL){
    /* if word is found, return pointer to it */
    if(temp->word == word){
      return temp;
    }
    /* else, continue to traverse the list */
    temp = temp->next;
  }
}





/* return true if given word is in hashtable, else return false */
bool HashTable::isInTable(std::string word){

  /* if search returns null, return false */
  if(searchTable(word) == NULL){
    return false;
  }
  /* else, return true */
  return true;
}





/* increment count of a given word */
void HashTable::incrementCount(std::string word){

  /* search for word in hashtable */
  wordItem* temp = searchTable(word);

  /* if the word does not exist, return */
  if(temp == NULL){
    return;
  }

  /* else if the word exists, increment its count field */
  temp->count++;
}








/* insert a word into hashtable */
void HashTable::addWord(std::string word){

  /* increment numItems in hashtable */
  this->numItems++;

  /* allocate new wordItem */
  wordItem* newWord = new wordItem;

  /* initialize new wordItem info */
  newWord->word = word;
  newWord->count = 1;
  newWord->next = NULL;

  /* if there is a collision, increment numCollisions field, and add new word
    as the head */
  if(this->hashTable[getHash(word)] != NULL){
    this->numCollisions++;
    /* let new word point to what the head points to */
    newWord->next = this->hashTable[getHash(word)];
    /* let the head point to the new word */
    this->hashTable[getHash(word)] = newWord;
  }

  /* if there is no collision, simply let the head point to the new word */
  if(this->hashTable[getHash(word)] == NULL){
    this->hashTable[getHash(word)] = newWord;
  }
}





/* return num of collisions that occurred in the hashtable */
int HashTable::getNumCollisions(){
  return this->numCollisions;
}




/* return num of items in the hashtable */
int HashTable::getNumItems(){
  return this->numItems;
}






/* return total count of all the words stored in hashtable */
int HashTable::getTotalNumWords(){

  /* initialize total count */
  int totalCount = 0;

  /* allocate temp wordItem node for searching linked list */
  wordItem* temp = new wordItem;

  /* iterate through the hashtable */
  for(int idx = 0; idx < this->hashTableSize; idx++){

    /* as long as linked-list is not empty, iterate through the linked-list */
    if(this->hashTable[idx] != NULL){

      /* let temp point to the head */
      temp = this->hashTable[idx];
      /* traverse the list and add up all the counts */
      while(temp != NULL){
        totalCount += temp->count;
        temp = temp->next;
      }
    }
  }

  /* return total num words */
  return totalCount;
}





/* bubble sorts the wordItem array from the most common word to the least */
void sortArray(wordItem array[], int size){

  wordItem temp;

  for(int i = 0; i < size - 1; i++){
    for(int j = i + 1; j < size; j++){
      if(array[i].count < array[j].count){
        temp = array[j];
        array[j] = array[i];
        array[i] = temp;
      }
    }
  }
}





/* prints top most frequent non-stop words */
void HashTable::printTopN(int numPrint){

  /* variable for keeping track of index of wordArray */
  int idxWord = 0;

  /* create a wordItems array */
  wordItem wordArray[this->numItems];

  /* allocate temp wordItem node for searching linked list */
  wordItem* temp = new wordItem;

  /* iterate through hash table */
  for(int idxHash = 0; idxHash < this->hashTableSize; idxHash++){

    /* as long as the linked-list is not empty, iterate through the linked
      list and add each wordItem to the wordItem array */
    if(this->hashTable[idxHash] != NULL){

      /* let temp point to the head */
      temp = this->hashTable[idxHash];
      /* while temp is not null, iterate through list, and add each wordItem */
      while(temp != NULL){
        wordArray[idxWord] = *temp;
        idxWord++;
        temp = temp->next;
      }
    }
  }

  /* sort word item array by count */
  sortArray(wordArray, this->numItems);

  /* probability of occurrence = word->count / total num of non-stopwords */
  float prob = 0.0;
  float totalCount = getTotalNumWords();

  /* print the top most common words and its probability of occurrence */
  for(int idx = 0; idx < numPrint; idx++){

    prob = (float)wordArray[idx].count / totalCount;
    std::cout << std::setprecision(4) << std::fixed << prob << " - " << wordArray[idx].word << "\n";

    /* re-initialize relevant variables */
    prob = 0;
  }
}



/* load stopwords into the stopwords hashtable */
void getStopWords(char *ignoreWordsTxt, HashTable &stopwordsTable){

  /* initialize variables for reading file */
  std::ifstream file;
  std::string word;

  /* open and read stopWords.txt, adding each word to the given hashtable */
  file.open(ignoreWordsTxt);
  while(file >> word){
    stopwordsTable.addWord(word);
  }

  /* close file */
  file.close();
}





/* returns true if 'word' is a stopword, else returns false */
bool isStopWord(std::string word, HashTable &stopwordsTable){
    return stopwordsTable.isInTable(word);
}





/* driver function takes in 4 command line arguments:
  1. num of most common words to print
  2. HW7.txt
  3. HW7stopWords.txt
  4. size of hashtable */
int main(int argc, char *argv[]){

  /* variables for reading HW7.txt */
  std::ifstream file;
  std::string word;

  /* create a stopwords hashtable, and a non-stopwords hashtable */
  HashTable stopwordsTable(STOPWORD_TABLE_SIZE);
  HashTable nonStopwordsTable(std::stoi(argv[4]));

  /* store stopwords in a stopwords hash table */
  getStopWords(argv[3], stopwordsTable);

  /* open HW7.txt */
  file.open(argv[2]);

  /* read each word in given txt */
  while(file >> word){

    /* if the word is not a stopword, enter this if-statement */
    if(isStopWord(word, stopwordsTable) == false){
      /* if the word is already in the hashtable, increment its count */
      if(nonStopwordsTable.isInTable(word) == true){
        nonStopwordsTable.incrementCount(word);
      }
      /* if the word is not yet in the hashtable, add it to the hashtable */
      else{
        nonStopwordsTable.addWord(word);
      }
    }
  }

  /* print top most common words in txt */
  nonStopwordsTable.printTopN(std::stoi(argv[1]));

  /* print the num of collisions that occurred */
  std::cout << "#\n";
  std::cout << "Number of collisions: " << nonStopwordsTable.getNumCollisions() << "\n";

  /* print the total number of unique words in the given txt */
  std::cout << "#\n";
  std::cout << "Unique non-stop words: " << nonStopwordsTable.getNumItems() << "\n";

  /* print total word count of the given txt */
  std::cout << "#\n";
  std::cout << "Total non-stop words: " << nonStopwordsTable.getTotalNumWords() << "\n";

  /* close file and exit */
  file.close();
  return 0;
}
