/* Assignment 6 - Binary Search Trees II

OBJECTIVES
1. Delete nodes in a BST
2. Create a super data structure combining BST and LL */




#include "HW6.hpp"





/* movie node default constructor */
LLMovieNode::LLMovieNode(){
  ranking = 0;
  title = "";
  year = 0;
  rating = 0;
  this->next = NULL;
}






/* MovieTree constructor */
MovieTree::MovieTree(){
  /* let root point to null */
  this->root = NULL;
}






/* helper function for deleting each linked list */
void deleteList(LLMovieNode* head) {

  /* pointers for deleting list */
  LLMovieNode* current = head;
  LLMovieNode* next = NULL;

  /* while current pointer has not reached end of list, traverse the list
    and delete each node */
  while(current != NULL){
    next = current->next;
    free(current);
    current = next;
  }

  /* let the head point to null */
  head = NULL;
}






/* helper function for deleting the BST */
void deleteTree(TreeNode* root){

  /* base case: if root is null, return */
  if(root == NULL){
    return;
  }

  /* delete both subtrees */
  deleteTree(root->leftChild);
  deleteTree(root->rightChild);

  /* then delete the root, by deleting the linked list, then the tree node */
  deleteList(root->head);
  delete root;
}




/* MovieTree destructor */
MovieTree::~MovieTree(){
  deleteTree(this->root);
}







/* searches for a tree node with the given titleChar key in the BST */
TreeNode* searchTreeNode(TreeNode* root, char key){

  /* base cases: if root is null or key is present at root, return root */
  if(root == NULL || root->titleChar == key){
    return root;
  }

  /* if key is greater than root's key, recur on right subtree */
  if(root->titleChar < key){
    return searchTreeNode(root->rightChild, key);
  }
  /* if key is smaller than root's key, recur on left subtree */
  else if(root->titleChar > key){
    return searchTreeNode(root->leftChild, key);
  }
}






/* inserts movie node in tree node */
void insertMovieNode(TreeNode* treeNode, LLMovieNode* movieNode){

  /* idx of the first different character */
  int idxChar = 0;

  /* let a temp pointer point to the linked-list head */
  LLMovieNode* temp = treeNode->head;

  /* if list is empty, let movie node become head, and return */
  if(temp == NULL){
    treeNode->head = movieNode;
    return;
  }

  /* find the idx of the first different character between the head and the
    movie node */
  for(int idx = 0; idx < 10; idx++){
    if(treeNode->head->title[idx] != movieNode->title[idx]){
      idxChar = idx;
      break;
    }
  }

  /* if the movie node comes before the head alphabetically, insert the movie
    node as the head, and return */
  if(treeNode->head->title[idxChar] > movieNode->title[idxChar]){
    /* let the movie node point to what the head points to */
    movieNode->next = treeNode->head;
    /* let the head point to the movie node */
    treeNode->head = movieNode;
    return;
  }

  /* otherwise, traverse the list */
  for(int i = 0; i < 1000; i++){

    /* if end of list is reached, insert movie node at end */
    if(temp->next == NULL){
      temp->next = movieNode;
      break;
    }

    /* find the idx of the first different character between the current node
      and the movie node */
    for(int idx = 0; idx < 10; idx++){
      if(temp->next->title[idx] > movieNode->title[idx]){
        idxChar = idx;
        break;
      }
    }

    /* compare titles alphabetically and insert the movie node in its
      alphabetically-correct place*/
    if(temp->next->title[idxChar] > movieNode->title[idxChar]){
      movieNode->next = temp->next;
      temp->next = movieNode;
      break;
    }

    /* else, continue to traverse the list */
    else{
      temp = temp->next;
    }
  }
}







/* insert tree node in the BST, and return pointer to the new tree */
TreeNode* insertTreeNode(TreeNode* root, TreeNode* treeNode){

  /* if the BST is empty, let the tree node become the root */
  if(root == NULL){
    root = treeNode;
    return root;
  }

  /* if the tree node's title is less than the root's title, recur on left */
  if(treeNode->titleChar < root->titleChar){
    root->leftChild = insertTreeNode(root->leftChild, treeNode);
  }
  /* if the tree node's title is greater than the root's title, recur on right */
  else if(treeNode->titleChar > root->titleChar){
    root->rightChild = insertTreeNode(root->rightChild, treeNode);
  }

  /* return the (unchanged) node pointer */
  return root;
}








/* add a new movie to the BST */
void MovieTree::addMovie(int ranking, std::string title, int year, float rating){

  /* allocate new tree node for searching */
  struct TreeNode* tempTreeNode = NULL;

  /* allocate new movie node */
  struct LLMovieNode* newMovieNode = new LLMovieNode(ranking, title, year, rating);

  /* search for the tree node that corresponds to the first letter of title */
  tempTreeNode = searchTreeNode(this->root, title[0]);

  /* if there is no tree node corresponding to the first letter of title,
    create it and insert the movie node in it, then insert it in the BST */
  if(tempTreeNode == NULL){

    /* create a new tree node */
    TreeNode* newTreeNode = new TreeNode;
    newTreeNode->titleChar = title[0];

    /* insert the new movie node in the new tree node */
    insertMovieNode(newTreeNode, newMovieNode);
    /* insert the new tree node in the BST */
    this->root = insertTreeNode(this->root, newTreeNode);
  }

  /* if the tree node corresponding to the first letter of title IS found,
    then simply insert the new movie node in this found tree node */
  if(tempTreeNode != NULL){
    insertMovieNode(tempTreeNode, newMovieNode);
  }

}






/* helper function that prints a linked list */
void printList(LLMovieNode *head) {
  /* before reaching end of linked-list, traverse the list and print movie
    info at each node */
  while(head != NULL){
     std::cout << " >> " << head->title << " " << head->rating << "\n";
     head = head->next;
  }
}





/* helper function for printing BST in inorder */
void printInorder(TreeNode* root){

  /* base case: if root is null, return */
  if(root == NULL){
    return;
  }

  /* first recur on left child */
  printInorder(root->leftChild);

  /* print the linked list at this tree node */
  std::cout << "Movies starting with letter: " << root->titleChar << "\n";
  printList(root->head);

  /* now recur on right child */
  printInorder(root->rightChild);
}





/* prints BST in alphabetical order */
void MovieTree::printMovieInventory(){
  printInorder(this->root);
}






/* finds and returns the inorder successor */
TreeNode* inorderSuccessor(TreeNode* root){

  /* allocate temp tree node for searching tree */
  struct TreeNode* temp = root;

  /* loop down to find the leftmost leaf */
  while(temp->leftChild != NULL){
    temp = temp->leftChild;
  }

  /* return min value tree node */
  return temp;
}








/* deletes tree node with input char, returns pointer to the tree node after
  deletion has occurred */
TreeNode* deleteTreeNode(TreeNode* root, char key){

  /* base case: if root is null, return the root */
  if(root == NULL){
    return root;
  }

  /* if the key is smaller than the root's titleChar, recur on left subtree */
  if(key < root->titleChar){
    root->leftChild = deleteTreeNode(root->leftChild, key);
  }
  /* if the key is greater than the root's titleChar, recur on right subtree */
  else if (key > root->titleChar){
    root->rightChild = deleteTreeNode(root->rightChild, key);
  }

  /* if key has been found, delete this tree node */
  else if(key == root->titleChar){

    /* for a node with zero children or only a left child */
    if(root->leftChild == NULL){
      /* allocate temp tree node to store the right subtree */
      TreeNode *temp = root->rightChild;
      /* delete the tree node */
      delete root;
      /* if right subtree exists, let its parent be null */
      if(temp != NULL){
        temp->parent = NULL;
      }
      /* return right subtree */
      return temp;
    }

    /* for a node with only a right child */
    else if(root->rightChild == NULL){
      /* allocate temp tree node to store the left subtree */
      TreeNode *temp = root->leftChild;
      /* delete the tree node */
      delete root;
      /* if the left subtree exists, let its parent be null */
      if(temp != NULL){
        temp->parent = NULL;
      }
      /* return left subtree */
      return temp;
    }

    /* for a node with two children, get the inorder successor: the smallest
      in the right subtree */
    TreeNode* temp = inorderSuccessor(root->rightChild);

    /* copy the inorder successor's content to its parent */
    root->titleChar = temp->titleChar;
    root->head = temp->head;

    /* delete the inorder successor */
    root->rightChild = deleteTreeNode(root->rightChild, temp->titleChar);
  }

  /* return the root after deletion has occurred */
  return root;
}









/* deletes linked-list node, returns pointer to the new linked-list after
  deletion */
LLMovieNode* deleteListNode(LLMovieNode *head, std::string title) {

  /* allocate temp and prev node for deletion; let both point to head */
  LLMovieNode* temp = head;
  LLMovieNode* prev = head;

  /* if the head node contains the title */
  if(temp != NULL && temp->title == title){
    /* let head point to temp->next */
    head = temp->next;
    /* delete temp node and return head pointer */
    delete temp;
    return head;
  }

  /* traverse the list to search for title */
  while(temp != NULL && temp->title != title) {
    prev = temp;
    temp = temp->next;
    /* if end of list reached and title was not found, return head pointer */
    if(temp == NULL){
      return head;
    }
  }

  /* once the title has been found, unlink it from the linked-list and free
    memory, and return the head pointer */
  prev->next = temp->next;
  delete temp;
  return head;
}






/* delete the linked-list node that contains title */
void MovieTree::deleteMovie(std::string title){

  /* allocate new tree node */
  TreeNode* tempTreeNode = NULL;

  /* search for the tree node corresponding to input title */
  tempTreeNode = searchTreeNode(this->root, title[0]);

  /* if the movie does not exist, return */
  if(tempTreeNode == NULL){
    std::cout << "Movie: " << title << " not found, cannot delete.\n";
    return;
  }

  /* otherwise, delete the linked-list node from the tree node */
  tempTreeNode->head = deleteListNode(tempTreeNode->head, title);

  /* if the linked-list is empty after deletion, also delete the tree node */
  if(tempTreeNode->head == NULL){
    this->root = deleteTreeNode(this->root, tempTreeNode->titleChar);
  }

}











/* display menu to get user input */
void displayMenu(){
  std::cout << "======Main Menu======\n";
  std::cout << "1. Print the inventory\n";
  std::cout << "2. Delete a movie\n";
  std::cout << "3. Quit\n";
}




/* driver function takes in one command line argument: HW6.csv */
int main(int argc, char *argv[]){

  /* initialize variables */
  std::ifstream file;
  std::string line;
  std::string ranking, title, year, rating;
  std::string choice, deleteTitle;
  int idxTitle = 0;
  int idxYear = 0;
  int idxRating = 0;

  /* instantiate BST */
  MovieTree myTree;

  /* open HW6.csv and return -1 if open file fail  */
  file.open(argv[1]);
  if(file.fail()){
    return -1;
  }

  /* read HW6.csv and store movies as nodes in MovieTree */
  while(getline(file, line)){

    /* read and store movie ranking */
    for(int ch = 0; line[ch] != ','; ch++){
      ranking += line[ch];
      idxTitle++;
    }

    /* read and store movie title */
    idxYear = idxTitle;
    for(int ch = idxTitle + 1; line[ch] != ','; ch++){
      title += line[ch];
      idxYear++;
    }

    /* read and store movie release year */
    idxRating = idxYear + 1;
    for(int ch = idxYear + 2; line[ch] != ','; ch++){
      year += line[ch];
      idxRating++;
    }

    /* read and store movie rating */
    for(int ch = idxRating + 2; line[ch] != '\0'; ch++){
      rating += line[ch];
    }

    /* store movie info as a node in a MovieTree */
    myTree.addMovie(stoi(ranking), title, stoi(year), stof(rating));

    /* re-initialize relevant variables */
    ranking = "";
    title = "";
    year = "";
    rating = "";
    idxTitle = 0;
    idxYear = 0;
    idxRating = 0;
  }


  /* while user chooses to not quit, repeat this while-loop */
  while(choice != "3"){

    /* repeatedly display menu and get user's choice */
    displayMenu();
    getline(std::cin, choice);

    /* switch cases based on user choice */
    switch(stoi(choice)){

      /* case 1: Print inventory */
      case 1:
        myTree.printMovieInventory();
        break;

      /* case 2: Delete a movie */
      case 2:
        std::cout << "Enter a movie title:\n";
        getline(std::cin, deleteTitle);
        myTree.deleteMovie(deleteTitle);
        break;

      /* case 3: Quit */
      case 3:
        break;

      /* default case: break */
      default:
        break;
    }
  }

  /* print "Goodbye!", close file, and exit */
  std::cout << "Goodbye!\n";
  file.close();

  return 0;
}

// end of program
