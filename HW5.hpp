#pragma once

#include <iostream>
#include <fstream>




/* node struct that will be stored in the MovieTree BST */
struct MovieNode{
  /* movie ranking */
  int ranking;
  /* movie title */
  std::string title;
  /* movie release year */
  int year;
  /* movie rating */
  float rating;

  /* pointers to parent, left child, and right child */
  MovieNode *parent = nullptr;
  MovieNode *leftChild = nullptr;
  MovieNode *rightChild = nullptr;

  /* default and parametrized constructors */
  MovieNode(){}
  MovieNode(int r, std::string t, int y, float q):
    ranking(r), title(t), year(y), rating(q) {}
};




/* BST class for storing and manipulating a tree of MovieNodes */
class MovieTree{

  private:
    /* pointer to root node */
    MovieNode *root;

  public:
    /* MovieTree constructor */
    MovieTree();
    /* MovieTree destructor */
    ~MovieTree();
    /* prints all movies in tree */
    void printMovieInventory();
    /* add new movie to tree */
    void addMovieNode(int ranking, std::string title, int year, float rating);
    /* find a movie in the tree, and print its information */
    void findMovie(std::string title);
    /* prints all movies that meet min rating and min year requirements */
    void queryMovies(float rating, int year);
    /* print average rating of all movies in tree */
    void averageRating();
};
