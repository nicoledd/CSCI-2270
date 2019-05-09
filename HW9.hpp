#ifndef GRAPH_HPP
#define GRAPH_HPP


#include <iostream>
#include <fstream>
#include <queue>
#include <vector>



struct vertex;



/* the struct for the adjacent vertices for each vertex in the graph. */
struct Edge{
  /* pointer to the end vertex */
  vertex *v;
  /* weight of the edge */
  int distance;
};



/* the struct for each vertex in the graph. */
struct vertex{
  /* name of the vertex */
  std::string name;
  /* used in BFT and DFT */
  bool visited;
  /* a collection of pointers to the cities that are adjacent to this vertex */
  std::vector<Edge> Edges;
};



class Graph{
  private:
    /* collection of all the vertices in the graph */
    std::vector<vertex> vertices;
    /* searches for and returns a pointer to the specified vertex */
    vertex *findVertex(std::string);
    /* breadth-first and depth-first traversal helper functions */
    void BFT_traversal(vertex *v);
    void DFT_traversal(vertex *v);
  public:
    /* constructor and destructor */
    Graph(){};
    ~Graph(){};
    /* add a new vertex to the graph */
    void addVertex(std::string);
    /* add a new edge between two vertices in the graph */
    void addEdge(std::string, std::string, int);
    /* print adjacency list */
    void displayEdges();
    /* breadth-first and depth-first traversal */
    void printDFT();
    void printBFT();
    /* used before BFT and DFT functions */
    void setAllVerticesUnvisited();
};

#endif
