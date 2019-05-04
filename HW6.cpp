// include libraries
#include <iostream>
#include <fstream>
using namespace std;

// linked list structure ///////////////////////////////////////////////////////
struct LLMovieNode{
  int ranking;
  string title;
  int year;
  float rating;
  struct LLMovieNode* next;
  LLMovieNode();
  LLMovieNode( int r, string t, int y, float q ):
    ranking(r), title(t), year(y), rating(q), next(NULL) {}
};


typedef LLMovieNode traceNode;

void printNode(struct LLMovieNode* x){

}

// linked list default constructor
LLMovieNode::LLMovieNode(){
  ranking = 0;
  title = "";
  year = 0;
  rating = 0;
  this->next = NULL;
}

// node structure //////////////////////////////////////////////////////////////
struct TreeNode{
  LLMovieNode* head = NULL;
  char titleChar;
  TreeNode *parent = NULL;
  TreeNode *leftChild = NULL;
  TreeNode *rightChild = NULL;
};

// binary tree class ///////////////////////////////////////////////////////////
class MovieTree{
private:
  TreeNode *root;
public:
  MovieTree();
  void addMovie( int ranking, string title, int year, float rating );
  void printMovieInventory();
  void deleteMovie(string title);
  ~MovieTree();
};

// movie tree constructor
MovieTree::MovieTree(){
  // let root point to null
  this->root = NULL;

}

// destructor
void deleteList(struct LLMovieNode* head) {
  /* deref head_ref to get the real head */
  struct LLMovieNode* current = head;
  struct LLMovieNode* next;

  while (current != NULL){
    next = current->next;
    free(current);
    current = next;
  }
  /* deref head_ref to affect the real head back
  in the caller. */
  head = NULL;
}
void deleteTree( struct TreeNode* node){
  // if tree is empty, return
  if (node == NULL) return;
  // first delete both subtrees
  deleteTree(node->leftChild);
  deleteTree(node->rightChild);
  // then delete the node
  deleteList(node->head);
  delete node;
}
MovieTree::~MovieTree(){
  deleteTree( root );
}





// C function to search a given key in a given BST /////////////////////////////
struct TreeNode* searchTreeNode(struct TreeNode* root, char key){

  // Base Cases: root is null or key is present at root
  if (root == NULL || root->titleChar == key)
    return root;

  // Key is greater than root's key
  if (root->titleChar < key)
  return searchTreeNode(root->rightChild, key);

  // Key is smaller than root's key
  return searchTreeNode(root->leftChild, key);
}

// insert list node in tree node ///////////////////////////////////////////////
void insertListNodeInTreeNode( struct TreeNode* tree_node, struct LLMovieNode* list_node ){

  // let temp point to head
  struct LLMovieNode* temp = tree_node->head;

  int idx_first_diff_char = 0;


  // if temp is null, insert list_node
  if( temp == NULL ){
    tree_node->head = list_node;
    return;
  }

  for(int idx_ch=0; idx_ch<10; idx_ch++){
    if( tree_node->head->title[idx_ch] != list_node->title[idx_ch] ){
      idx_first_diff_char = idx_ch;
      break;
    }
  }
  if( tree_node->head->title[idx_first_diff_char] > list_node->title[idx_first_diff_char] ){
    list_node->next = tree_node->head;
    tree_node->head = list_node;
    return;
  }

  // otherwise, traverse list
  for(int i=0; i<1000; i++){

    if( temp->next == NULL ){
      temp->next = list_node;
      break;
    }

    for(int idx_ch=0; idx_ch<10; idx_ch++){
      if( temp->next->title[idx_ch] > list_node->title[idx_ch] ){
        idx_first_diff_char = idx_ch;
        break;
      }
    }
    if( temp->next->title[idx_first_diff_char] > list_node->title[idx_first_diff_char] ){
      list_node->next = temp->next;
      temp->next = list_node;
      break;
    }

    else{
      temp = temp->next;
    }
  }

}



// insert tree node in binary tree /////////////////////////////////////////////
struct TreeNode* insertTreeNode( struct TreeNode* root, struct TreeNode* tree_node ) {

    // If the tree is empty, let tree node become head
    if (root == NULL) {
      root = tree_node;
      return root;
    }
    char letter = tree_node->titleChar;

    // Otherwise, recur down the tree
    if ( letter < root->titleChar )
        root->leftChild  = insertTreeNode( root->leftChild, tree_node );
    else if ( letter > root->titleChar )
        root->rightChild = insertTreeNode( root->rightChild, tree_node );

    // return the (unchanged) node pointer
    return root;
}


// add movie ///////////////////////////////////////////////////////////////////
void MovieTree::addMovie( int ranking, string title, int year, float rating ){

  // allocate new tree node
  struct TreeNode* curr_tree_node = NULL;

  // allocate new linked list node
  struct LLMovieNode* new_list_node = new LLMovieNode(ranking, title, year, rating);

  // search for tree node corresponding with movie title
  curr_tree_node = searchTreeNode( this->root, title[0] );

  // if searchTreeNode returned null,
  if( curr_tree_node == NULL ){

    // create new tree node
    struct TreeNode* new_tree_node = new TreeNode;
    new_tree_node->titleChar = title[0];

    // insert list node in new tree node
    insertListNodeInTreeNode( new_tree_node, new_list_node );

    // insert new tree node in tree
    this->root = insertTreeNode( this->root, new_tree_node );
  }

  // if searchTreeNode returned not null
  if( curr_tree_node != NULL ){
    // insert list node in curr tree node
    insertListNodeInTreeNode( curr_tree_node, new_list_node );
  }

}






// print linked list ///////////////////////////////////////////////////////////
void printList( struct LLMovieNode *n ) {
  while(n!=NULL){
     cout << " >> " << n->title << " " << n->rating << endl;
     n = n->next;
  }
}

// print movie inventory ///////////////////////////////////////////////////////
void printInorder(struct TreeNode* node) {

  if (node == NULL) return;

  // first recur on left child
  printInorder(node->leftChild);

  cout << "Movies starting with letter: " << node->titleChar << "\n";
  // then print the data of node
  printList( node->head );

  // now recur on right child
  printInorder(node->rightChild);
}

void MovieTree::printMovieInventory(){
  //cout << endl << __func__ << endl; // debug
  printInorder( this->root );
}





// delete node /////////////////////////////////////////////////////////////////

struct TreeNode * minValueNode(struct TreeNode* node) {
  // allocate temp node
  struct TreeNode* current = node;
  // loop down to find the leftmost leaf
  while (current->leftChild != NULL)
  current = current->leftChild;
  // return min value tree node
  return current;
}


// delete tree node ////////////////////////////////////////////////////////////
struct TreeNode* deleteTreeNode( struct TreeNode* root, char key ){

  // debug
  //cout << "deleteTreeNode " << key << endl;

  // base case
  if (root == NULL) {
    return root;
  }

  // If the key to be deleted is smaller than the root's key, it lies in left subtree
  if (key < root->titleChar){
    //cout << __LINE__ <<endl;  //debug
    root->leftChild = deleteTreeNode(root->leftChild, key);
  }

  // If the key to be deleted is greater than the root's key, it lies in right subtree
  else if (key > root->titleChar){
    //cout << __LINE__ <<endl;  //debug
    root->rightChild = deleteTreeNode(root->rightChild, key);
  }

  // if key is same as root's key, then This is the node to be deleted
  else if(key == root->titleChar){
    //cout << __LINE__ <<endl;  //debug
    // debug
    /*
    cout << __LINE__ << " key = " << key << endl;
    cout << "root->rightChild = " << root->rightChild->titleChar << endl;
    cout << "root->rightChild->rightChild = " << root->rightChild->rightChild << endl;
    cout << "root->rightChild->leftChild = " << root->rightChild->leftChild << endl;
    cout << "root->leftChild = " << root->leftChild << endl;
    */
    // node with only one child or no child
    if (root->leftChild == NULL){
      //cout << __LINE__ <<endl;  //debug
      struct TreeNode *temp = root->rightChild;

      // debug
      /*
      cout << "left: root->titleChar = " << root->titleChar << endl;
      cout << "left: temp->titleChar = " << temp->titleChar << endl;
      */
      delete root;
      if(temp!=NULL) temp->parent = NULL;
      return temp;
    }

    else if (root->rightChild == NULL){
      //cout << __LINE__ <<endl;  //debug
      struct TreeNode *temp = root->leftChild;

      /* debug
      cout << "right: root->titleChar = " << root->titleChar << endl;
      cout << "right: temp->titleChar = " << temp->titleChar << endl;
      */

      delete root;
      if(temp!=NULL) temp->parent = NULL;
      return temp;
    }
    //cout << __LINE__ <<endl;  //debug
    // node with two children: Get the inorder successor (smallest in the right subtree)
    struct TreeNode* temp = minValueNode(root->rightChild);

    // about to delete inorder successor:

    // Copy the inorder successor's content to its parent
    root->titleChar = temp->titleChar;
    root->head = temp->head;

    // Delete the inorder successor
    root->rightChild = deleteTreeNode(root->rightChild, temp->titleChar);
  }
  //cout << __LINE__ <<endl;  //debug
  // debug
  //cout << "root->titleChar = " << root->titleChar << endl;

  return root;
}

// delete list node ////////////////////////////////////////////////////////////
struct LLMovieNode* deleteListNode( struct LLMovieNode *head, string key ) {

  // Store head node
  struct LLMovieNode* temp = head;
  struct LLMovieNode* prev = head;

  // If head node itself holds the key to be deleted
  if (temp != NULL && temp->title == key) {
    head = temp->next;
    delete temp;
    return head;
  }

  // Search for the key to be deleted
  while (temp != NULL && temp->title != key) {
    prev = temp;
    temp = temp->next;
    // If key was not present in linked list
    if (temp == NULL) {
      return head;
    }
  }

  // Unlink the node from linked list
  prev->next = temp->next;


  // free memory
  delete temp;
  return head;
}

// delete movie ////////////////////////////////////////////////////////////////
void MovieTree::deleteMovie( string title ){

  // allocate new tree node
  struct TreeNode* curr_tree_node = NULL;

  // search for the tree root corresponding to this title
  curr_tree_node = searchTreeNode( this->root, title[0] );

  // if movie doesn't exist, cout that
  if( curr_tree_node == NULL ){
    cout << "Movie: " << title << " not found, cannot delete.\n";
    return;
  }

  // delete linked list node
  curr_tree_node->head = deleteListNode( curr_tree_node->head, title );
  if( curr_tree_node->head == NULL ){
    this->root = deleteTreeNode( this->root, curr_tree_node->titleChar );
  }

}











// display menu ////////////////////////////////////////////////////////////////
// user choice: 1. print inventory 2. delete movie 3. quit
void displayMenu(){
  cout << "======Main Menu======\n";
  cout << "1. Print the inventory\n";
  cout << "2. Delete a movie\n";
  cout << "3. Quit\n";
}

// main function ///////////////////////////////////////////////////////////////
// takes in 1 command line argument:
// 1. Movies.csv
// - read Movies.csv
// - organize movies into binary tree where each tree node is a linked list
int main( int argc, char *argv[] ){

  // initialize variables: [ranking],[title],[year],[rating]
  ifstream file;
  string line;
  string ranking;
  string title;
  string year;
  string rating;
  int idx_title = 0;
  int idx_year = 0;
  int idx_rating = 0;
  MovieTree tree;
  string choice;
  string title_to_be_deleted;

  // open Movies.csv and return -1 if open file fail
  file.open( argv[1] );
  if ( file.fail() ) return -1;


  // read Movies.csv and store in MovieTree
  while( getline(file,line) ){
    // read the ranking
    for( int ch=0; line[ch]!=','; ch++ ){
      ranking += line[ch];
      idx_title++;
    }
    // read the title
    idx_year = idx_title;
    for( int ch=idx_title+1; line[ch]!=','; ch++ ){
      title += line[ch];
      idx_year++;
    }
    // read the year
    idx_rating = idx_year+1;
    for( int ch=idx_year+2; line[ch]!=','; ch++ ){
      year += line[ch];
      idx_rating++;
    }
    // read the rating
    for( int ch=idx_rating+2; line[ch]!='\0'; ch++ ){
      rating += line[ch];
    }
    // store in tree
    tree.addMovie( stoi(ranking), title, stoi(year), stof(rating) );
    // re-initialize variables
    ranking = "";
    title = "";
    year = "";
    rating = "";
    idx_title = 0;
    idx_year = 0;
    idx_rating = 0;
  }



  // tree.printMovieInventory();

/*

  tree.addMovie( 2, "a", 1999, 9.5 );
  tree.addMovie( 2, "b", 1999, 9.5 );
  tree.addMovie( 2, "c", 1999, 9.5 );

  tree.printMovieInventory();
  cout << endl;

  tree.deleteMovie("a");
  tree.deleteMovie("b");
  tree.deleteMovie("c");

  cout << __LINE__ << endl;

  tree.printMovieInventory();
  */


  // display menu
  while( choice != "3" ){
    displayMenu();
    getline(cin, choice);

    switch( stoi(choice) ){

      case 1:
      tree.printMovieInventory();
      break;

      case 2:
      cout << "Enter a movie title:\n";
      getline(cin, title_to_be_deleted);
      tree.deleteMovie(title_to_be_deleted);
      break;

      case 3:
      break;

      default:
      break;
    }
  }

  // close file and return
  cout << "Goodbye!\n";
  file.close();

  return 0;
}

// end of program
