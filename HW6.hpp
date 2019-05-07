#ifndef MOVIETREE_HPP
#define MOVIETREE_HPP

#include <iostream>
#include <fstream>





/* Linked List node structure that will be stored in the tree nodes */
struct LLMovieNode{
  /* movie ranking */
  int ranking;
  /* movie title */
  std::string title;
  /* movie release year */
  int year;
  /* movie rating */
  float rating;
  /* pointer to next movie node */
  LLMovieNode* next;

  /* default and parametrized constructors */
  LLMovieNode();
  LLMovieNode(int r, std::string t, int y, float q):
    ranking(r), title(t), year(y), rating(q), next(NULL) {}
};





/* tree node that will be stored in the BST */
struct TreeNode{
  /* head pointer of linked-list */
  LLMovieNode* head = NULL;
  /* starting character of the movie titles */
  char titleChar;
  /* parent, left child, and right child pointers */
  TreeNode *parent = NULL;
  TreeNode *leftChild = NULL;
  TreeNode *rightChild = NULL;
};




/* BST class */
class MovieTree{
  private:
    /* pointer to root */
    TreeNode *root;
  public:
    /* constructor and destructor */
    MovieTree();
    ~MovieTree();
    /* print BST using inorder */
    void printMovieInventory();
    /* add new movie node to BST */
    void addMovie(int ranking, std::string title, int year, float rating);
    /* delete movie node from BST */
    void deleteMovie(std::string title);
};

#endif
