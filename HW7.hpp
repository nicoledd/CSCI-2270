#ifndef HW_7_HASH_TABLE
#define HW_7_HASH_TABLE

#include <iostream>
#include <fstream>
#include <iomanip>



/* struct to store word name and count */
struct wordItem{
  std::string word;
  int count;
  wordItem* next;
};




/* class HashTable for storing words. Create two hashtables in the driver:
 - one for storing stop words
 - one for storing unique non-stop words */
class HashTable {

  private:
    /* hash function for a given word */
    unsigned int getHash(std::string);
    /* searches table for given word, and returns a pointer to that word */
    wordItem* searchTable(std::string);

    /* hashtable array of wordItem's */
    wordItem** hashTable;
    /* size of hadhtable, num of wordItems it contains, and the total num of
      collisions that have occurred */
    int hashTableSize;
    int numItems;
    int numCollisions;

  public:
    /* constructor and destructor */
    HashTable(int);
    ~HashTable();
    /* add a new word to the hashtable */
    void addWord(std::string);
    /* return true if given word is already in the hashtable, else return false */
    bool isInTable(std::string);
    /* increments the 'count' field of a given word */
    void incrementCount(std::string);
    /* print top most common words in text */
    void printTopN(int);
    /* returns the total num of collisions that occurred */
    int getNumCollisions();
    /* return the total num of wordItems in the hashtable */
    int getNumItems();
    /* returns total word count of the txt, adding up the 'count' field of
      all the wordItems */
    int getTotalNumWords();
};




/* size of stopwords hash table */
const int STOPWORD_TABLE_SIZE = 50;






/* load stopwords into the stopwords hash table */
void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable);

/* checks table to see if a word is a stopword or not */
bool isStopWord(std::string, HashTable &stopWordsTable);

#endif
