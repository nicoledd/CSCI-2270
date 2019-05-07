/* Assignment 5 - Binary Search Trees

OBJECTIVES
1. Build a binary search tree (BST)
2. Search and traverse a BST */

#include "HW5.hpp"






/* default constructor for MovieTree: let root point to null */
MovieTree::MovieTree(){
  this->root = NULL;
}







/* helper function that deletes this BST */
void deleteMovieTree(MovieNode* root){

  /* base case: if root is null, return */
  if(root == NULL){
    return;
  }

  /* first delete both subtrees */
  deleteMovieTree(root->leftChild);
  deleteMovieTree(root->rightChild);

  /* then delete the root */
  delete root;
}


/* MovieTree destructor: frees all memory associated with this BST */
MovieTree::~MovieTree(){
  deleteMovieTree(this->root);
}





/* allocates and returns a new movie node */
MovieNode *newNode(int ranking, std::string title, int year, float rating){

  /* allocate memory for a new movie node */
  MovieNode *newNode = new MovieNode;

  /* initialize variables and pointers for new movie node */
  newNode->ranking = ranking;
  newNode->title = title;
  newNode->year = year;
  newNode->rating = rating;
  newNode->parent = NULL;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;

  /* return new node */
  return newNode;
}






/* helper function to insert a new node with given title in BST */
MovieNode* insertMovieNode(MovieNode* node, int ranking, std::string title, int year, float rating){

  /* If the tree is empty, return a new node */
  if(node == NULL){
    return newNode(ranking, title, year, rating);
  }

  /* Otherwise, recur down the tree. If the new node title is less than the
    current node's title, recur down left subtree */
  if(title[0] < node->title[0]){
    node->leftChild  = insertMovieNode(node->leftChild, ranking, title, year, rating);
  }
  /* else if the new node title is greater than the current node's title, recur
    down right subtree */
  else if(title[0] > node->title[0]){
    node->rightChild = insertMovieNode(node->rightChild, ranking, title, year, rating);
  }

  /* if root title and new node title start with same letter, compare the
    second letter instead */
  else if(title[0] == node->title[0]){
    if(title[1] < node->title[1]){
      node->leftChild  = insertMovieNode(node->leftChild, ranking, title, year, rating);
    }
    else if(title[1] > node->title[1]){
      node->rightChild = insertMovieNode(node->rightChild, ranking, title, year, rating);
    }
  }

  /* return the (unchanged) node pointer */
  return node;
}








/* add a node to the BST in the correct place based on its title */
void MovieTree::addMovieNode(int ranking, std::string title, int year, float rating){

  /* allocate a new tree node */
  MovieNode* newNode = new MovieNode;

  /* initialize variables and pointers for the new node */
  newNode->ranking = ranking;
  newNode->title = title;
  newNode->year = year;
  newNode->rating = rating;
  newNode->parent = NULL;
  newNode->leftChild = NULL;
  newNode->rightChild = NULL;

  /* if tree is empty, make the new node the root */
  if(this->root == NULL){
    this->root = newNode;
    return;
  }

  /* insert new node into the BST */
  insertMovieNode(this->root, ranking, title, year, rating);
}








/* helper function for printing tree using inorder traversal */
void printInorder(MovieNode* root){
  /* base case: if root is null, return */
  if(root == NULL){
    return;
  }

  /* first recur on left sutree */
  printInorder(root->leftChild);

  /* then print data of node */
  std::cout << "Movie: " << root->title << " " << root->rating << "\n";

  /* now recur on right subtree */
  printInorder(root->rightChild);
}


/* print the tree using inorder traversal */
void MovieTree::printMovieInventory(){
  printInorder(this->root);
}






/* helper function to search for a given title
- returns pointer to node found with input title */
MovieNode* searchTitle(MovieNode* root, std::string title){

  /* base cases: if leaf node is reached or if title is present at root,
    return the root */
  if(root == NULL || root->title == title){
    return root;
  }

  /* if movie title is greater than root's title, recur down right subtree */
  if(root->title[0] < title[0]){
    return searchTitle(root->rightChild, title);
  }
  /* if movie title is smaller than root's title, recur down left subtree */
  if( root->title[0] > title[0] )
    return searchTitle(root->leftChild, title);

  /* if first letter of movie title and root title are the same, compare
    the second letter instead */
  if(root->title[0] == title[0]){
    if(root->title[1] < title[1]){
      return searchTitle(root->rightChild, title);
    }
    if(root->title[1] > title[1]){
      return searchTitle(root->leftChild, title);
    }
  }
}





/* find the movie with the given title, and print its information */
void MovieTree::findMovie(std::string title){

  /* allocate temp node for searching tree */
  MovieNode* temp = new MovieNode;

  /* let temp point to the tree node with the given title */
  temp = searchTitle(this->root, title);

  /* if given title does not exist, print "Movie not found." */
  if(temp == NULL){
    std::cout << "Movie not found.\n";
  }

  /* otherwise, print movie info */
  else{
    std::cout << "Movie Info:\n";
    std::cout << "==================\n";
    std::cout << "Ranking:" << temp->ranking << "\n";
    std::cout << "Title  :" << temp->title << "\n";
    std::cout << "Year   :" << temp->year << "\n";
    std::cout << "rating :" << temp->rating << "\n";
  }
}







/* helper function for queryMovies */
void searchQuery(MovieNode* root, float rating, int year){

  /* base case: if leaf node reached, return */
  if(root == NULL){
    return;
  }

  /* if movie meets min requirements, print movie */
  if(root->rating >= rating && root->year >= year){
    std::cout << root->title << "(" << root->year << ") " << root->rating << "\n";
  }

  /* else, iterate down left subtree and right subtree */
  searchQuery(root->leftChild, rating, year);
  searchQuery(root->rightChild, rating, year);
}






/* print all movies with a rating greater than or equal to input rating, and
  which are newer than the input year
  - use preorder */
void MovieTree::queryMovies(float rating, int year){
  std::cout << "Movies that came out after " << year << " with rating at least " << rating << ":\n";
  searchQuery(this->root, rating, year);
}






/* helper function to find sum of all the elements in tree */
float sumOfElements(MovieNode* root){
  /* if leaf node is reached, return 0 */
  if(root == NULL){
    return 0;
  }
  /* add the root's rating, the sum of its left children, and the sum of its right children */
  return (root->rating + sumOfElements(root->leftChild) + sumOfElements(root->rightChild));
}






/* helper function to find num of elements in tree */
int numOfElements(MovieNode* root){

  /* initialize numElements as 1, since we counted the root */
  int numElements = 1;

  /* count the root's left children */
  if(root->leftChild != NULL){
     numElements += numOfElements(root->leftChild);
  }
  /* count the root's right children */
  if(root->rightChild != NULL){
    numElements += numOfElements(root->rightChild);
  }

  /* return the total num of elements in tree */
  return numElements;
}





/* print the average rating for all movies in the tree
- if the tree is empty, print 0.0 */
void MovieTree::averageRating(){

  /* initialize variables */
  float numElements = 0;
  float sumElements = 0;
  float average = 0;

  /* if tree is empty, average rating is 0.0 */
  if(this->root == NULL){
    average = 0;
  }

  /* else if tree is not empty, calculate average rating */
  else if(this->root != NULL){
    sumElements = sumOfElements(this->root);
    numElements = numOfElements(this->root);
    average = sumElements/numElements;
  }

  /* print the average rating */
  std::cout << "Average rating:" << average << "\n";
}










/* display menu for user to choose from */
void displayMenu(){
  std::cout << "======Main Menu======\n";
  std::cout << "1. Find a movie\n";
  std::cout << "2. Query movies\n";
  std::cout << "3. Print the inventory\n";
  std::cout << "4. Average rating of movies\n";
  std::cout << "5. Quit\n";
}






/* driver function takes in one command line argument: HW5.csv */
int main(int argc, char *argv[]){

  /* initialize variables */
  std::ifstream file;
  std::string line, ranking, title, year, rating;
  std::string choice, findTitle, minRating, minYear;
  int idxTitle = 0;
  int idxYear = 0;
  int idxRating = 0;

  /* instantiate tree */
  MovieTree myTree;

  /* open HW5.csv and return -1 if open file fail */
  file.open(argv[1]);
  if(file.fail()){
    return -1;
  }

  /* read each line of HW5.csv and store each movie as a node in MovieTree */
  while(getline(file, line)){

    /* read and store the movie ranking */
    for(int ch = 0; line[ch] != ','; ch++){
      ranking += line[ch];
      idxTitle++;
    }

    /* read and store the movie title */
    idxYear = idxTitle;
    for(int ch = idxTitle + 1; line[ch] != ','; ch++){
      title += line[ch];
      idxYear++;
    }

    /* read and store the movie release year */
    idxRating = idxYear + 1;
    for(int ch = idxYear + 2; line[ch] != ','; ch++){
      year += line[ch];
      idxRating++;
    }

    /* read and store the movie rating */
    for(int ch = idxRating + 2; line[ch] != '\0'; ch++){
      rating += line[ch];
    }

    /* create a new node with movie info, and store new node in the BST */
    myTree.addMovieNode(stoi(ranking), title, stoi(year), stof(rating));

    /* re-initialize the variables used in this while-loop */
    ranking = "";
    title = "";
    year = "";
    rating = "";
    idxTitle = 0;
    idxYear = 0;
    idxRating = 0;
  }


  /* while user does not choose to quit, repeat this while-loop */
  while(choice != "5"){

    /* repeatedly display menu and get user choice */
    displayMenu();
    getline(std::cin, choice);

    /* switch cases depending on user choice */
    switch(stoi(choice)){

      /* case 1: Find a Movie */
      case 1:
        std::cout << "Enter title:\n";
        getline(std::cin, findTitle);
        myTree.findMovie(findTitle);
        break;

      /* case 2: Query Movies */
      case 2:
        std::cout << "Enter minimum rating:\n";
        getline(std::cin, minRating);
        std::cout << "Enter minimum year:\n";
        getline(std::cin, minYear);
        myTree.queryMovies(stof(minRating), stoi(minYear));
        break;

      /* case 3: Print the Inventory */
      case 3:
        myTree.printMovieInventory();
        break;

      /* case 4: Average Rating of Movies */
      case 4:
        myTree.averageRating();
        break;

      /* default case: break */
      default:
        break;
    }
  }

  /* print "Goodbye!", close file, and quit */
  std::cout << "Goodbye!\n";
  file.close();

  return 0;
}
