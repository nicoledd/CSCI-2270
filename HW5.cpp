// movie node structure
struct MovieNode{
  int year;
  int ranking;
  string title;
  float rating;

  MovieNode *parent = NULL;
  MovieNode *leftChild = NULL;
  MovieNode *rightChild = NULL;

  MovieNode(){}

  MovieNode( int r, string t, int y, float q ):
  ranking(r), title(t), year(y), rating(q) {}
};

// binary tree structure
class MovieTree{

private:
  // pointer to movie found
  MovieNode *search( string title );

public:
  // pointer to root node
  MovieNode *root;
  // constructor
  MovieTree();
  void printMovieInventory();
  void addMovieNode( int ranking, string title, int year, float rating );
  void findMovie( string title );
  void queryMovies( float rating, int year );
  void averageRating();
  void deleteTree( MovieNode* node );
  // destructor
  ~MovieTree();
};


MovieTree::MovieTree(){
  this->root = NULL;
}


// delete entire tree
void MovieTree::deleteTree( MovieNode* node ){
  // if tree is empty, return
  if (node == NULL) return;

  /* first delete both subtrees */
  deleteTree(node->leftChild);
  deleteTree(node->rightChild);

  /* then delete the node */
  delete node;
}


MovieTree::~MovieTree(){
  deleteTree( this->root );
}

MovieNode* MovieTree::search( string title ){
  struct MovieNode* new_node = new MovieNode;
  new_node->leftChild = NULL;
  new_node->rightChild = NULL;
  return new_node;
}


struct MovieNode *newNode( int ranking, string title, int year, float rating ){
    struct MovieNode *new_node =  new MovieNode;
    new_node->ranking = ranking;
    new_node->title = title;
    new_node->year = year;
    new_node->rating = rating;
    new_node->parent = NULL;
    new_node->leftChild = NULL;
    new_node->rightChild = NULL;
    return new_node;
}


/* A utility function to insert a new node with given key in BST */
struct MovieNode* insert(struct MovieNode* node, int ranking, string title, int year, float rating) {
    /* If the tree is empty, return a new node */
    if (node == NULL) return newNode( ranking, title, year, rating );

    char letter = title[0];

    /* Otherwise, recur down the tree */
    if (letter < node->title[0])
        node->leftChild  = insert(node->leftChild, ranking, title, year, rating);
    else if (letter > node->title[0])
        node->rightChild = insert(node->rightChild, ranking, title, year, rating);

    // if first char is the same
    else if (title[0] == node->title[0]){
      letter = title[1];
      if (letter < node->title[1])
          node->leftChild  = insert(node->leftChild, ranking, title, year, rating);
      else if (letter > node->title[1])
          node->rightChild = insert(node->rightChild, ranking, title, year, rating);
    }

    /* return the (unchanged) node pointer */
    return node;
}


void MovieTree::addMovieNode( int ranking, string title, int year, float rating ){

  // allocate new_node
  struct MovieNode* new_node = new MovieNode;

  // initialize data in new_node
  new_node->ranking = ranking;
  new_node->title = title;
  new_node->year = year;
  new_node->rating = rating;

  // initialize pointers in new_node
  new_node->parent = NULL;
  new_node->leftChild = NULL;
  new_node->rightChild = NULL;

  // if tree is empty, make new_node the root
  if( this->root == NULL ){
    this->root = new_node;
    return;
  }

  // if title char > parent char, insert right
  // if title char < parent char, insert left
  // if title char = parent char, look at next letter
  insert( this->root, ranking, title, year, rating);

}


/* Given a binary tree, print its nodes in preorder*/
void printInorder(struct MovieNode* node){
    if (node == NULL)
        return;

    /* first recur on left sutree */
    printInorder(node->leftChild);

    /* then print data of node */
    cout << "Movie: " << node->title << " " << node->rating << "\n";

    /* now recur on right subtree */
    printInorder(node->rightChild);
}


void MovieTree::printMovieInventory(){
  printInorder( this->root );
}


struct MovieNode* searchTitle( struct MovieNode* root, string title ){
    // Base Cases: root is null or key is present at root
    if ( root == NULL || root->title == title)
       return root;

    // Key is greater than root's key
    if (root->title[0] < title[0])
      return searchTitle(root->rightChild, title);

    // Key is smaller than root's key
    if( root->title[0] > title[0] )
      return searchTitle(root->leftChild, title);

    // Key is equal
    if( root->title[0] == title[0] ){
      if (root->title[1] < title[1])
        return searchTitle(root->rightChild, title);
      if( root->title[1] > title[1] )
        return searchTitle(root->leftChild, title);
    }
}


void MovieTree::findMovie( string title ){
  // allocate new_node
  struct MovieNode* temp = new MovieNode;
  temp = searchTitle(this->root, title);
  if ( temp == NULL ){
    cout << "Movie not found.\n";
  }
  else{
    cout << "Movie Info:\n";
    cout << "==================\n";
    cout << "Ranking:" << temp->ranking << "\n";
    cout << "Title  :" << temp->title << "\n";
    cout << "Year   :" << temp->year << "\n";
    cout << "rating :" << temp->rating << "\n";
  }
}



 void searchQuery( struct MovieNode* root, float rating, int year ){
    // Base Cases: root is null or key is present at root
    if( root == NULL )
       return;

    if( root->rating >= rating && root->year >= year ){
      cout << root->title << "(" << root->year << ") " << root->rating << "\n";
    }

    searchQuery( root->leftChild, rating, year );
    searchQuery( root->rightChild, rating, year );
}



void MovieTree::queryMovies( float rating, int year ){
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":\n";
  searchQuery( this->root, rating, year );
}


/* Function to find sum of all the elements*/
float sumOfElements( MovieNode* root ){
    if (root == NULL)
        return 0;
    return (root->rating + sumOfElements(root->leftChild) + sumOfElements(root->rightChild));
}

int numOfElements( MovieNode* root ){
    int count = 1;
    if (root->leftChild != NULL) {
       count += numOfElements(root->leftChild);
    }
    if (root->rightChild != NULL) {
        count += numOfElements(root->rightChild);
    }
    return count;
}

void MovieTree::averageRating(){
  float count = 0;
  float sum = 0;
  float average = 0;
  sum = sumOfElements( this->root );
  if( this->root != NULL ){
    count = numOfElements( this->root );
    average = sum/count;
  }
  else{
    average = 0;
  }
  cout << "Average rating:" << average << "\n";
}











void displayMenu(){
  cout << "======Main Menu======\n";
  cout << "1. Find a movie\n";
  cout << "2. Query movies\n";
  cout << "3. Print the inventory\n";
  cout << "4. Average Rating of movies\n";
  cout << "5. Quit\n";
}




// main function
// takes in 1 command line argument
// 1. Movies.csv
int main( int argc, char *argv[] ){

  // initialize variables
  ifstream file;  // initialize Movies.csv
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
  string title_1;
  string min_rating;
  string min_year;

  // open Movies.csv
  file.open( argv[1] );

  // if open file fail, return -1
  if ( file.fail() ){
    return -1;
  }

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
    // store in new node
    tree.addMovieNode( stoi(ranking), title, stoi(year), stof(rating) );
    // re-initialize variables
    ranking = "";
    title = "";
    year = "";
    rating = "";
    idx_title = 0;
    idx_year = 0;
    idx_rating = 0;
  }


  // display menu
  while( choice != "5" ){
    displayMenu();
    getline(cin, choice);

    switch( stoi(choice) ){

      case 1:
      cout << "Enter title:\n";
      getline(cin, title_1);
      tree.findMovie(title_1);
      break;

      case 2:
      cout << "Enter minimum rating:\n";
      getline(cin, min_rating);
      cout << "Enter minimum year:\n";
      getline(cin, min_year);
      tree.queryMovies(stof(min_rating), stoi(min_year));
      break;

      case 3:
      tree.printMovieInventory();
      break;

      case 4:
      tree.averageRating();
      break;

      default:
      break;
    }
  }
  cout << "Goodbye!\n";

  file.close();

  return 0;
}
