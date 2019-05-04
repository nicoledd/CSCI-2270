/*
OBJECTIVES
1. Build an undirected weighted graph
2. Perform Breadth First Traversal (BFT) and Depth First Traversal (DFT)

Overview
You were just a humble map programmer, but that was before the zombies attacked! Now, your
skills are put to coordinating the survivors and finding routes between cities that haven’t been
overtaken. Some of the roads between these cities have been overrun and you will have to
avoid them, which has caused the nation to be divided into multiple smaller districts (think
disconnected components in a graph). You will have to build a graph with each vertex
representing a city and each edge between vertices representing a route between them. The
following structs will facilitate your graph.

*/

// include libraries ///////////////////////////////////////////////////////////
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "Graph.hpp"
using namespace std;


Graph::Graph(){
}
Graph::~Graph(){
}

// vertex* Graph::findVertex(string name) //////////////////////////////////////
// - return a pointer to the vertex with the specified name.
vertex* Graph::findVertex(string name){
  // search vertices for name
  for(int i = 0; i < this->vertices.size(); i++){
    // if name found, return address of that name
    if(this->vertices[i].name == name){
      return &this->vertices[i];
    }
  }
  // if not found, return NULL
  return NULL;
}

// void Graph::addVertex(string cityName) //////////////////////////////////////
// - create a new vertex with name cityName
// - and push it back to your vector of vertices
void Graph::addVertex(string cityName){
  // create a new vertex
  vertex newVertex;
  // add data to new vertex
  newVertex.name = cityName;
  newVertex.visited = false;
  // push into vector of vertices
  this->vertices.push_back(newVertex);
}

// void Graph::addEdge(string city1, string city2, int distance) ///////////////
// - establish a single edge from city1 to city2
// - create edge with distance equal to parameter distance
//   and v equal to address of vertex with name city2
// - push back the edge to the Edges vector of the vertex with name city1
void Graph::addEdge(string city1, string city2, int distance){
  // create a new edge
  Edge newEdge;
  // set distance and v of newEdge
  newEdge.distance = distance;
  newEdge.v = findVertex(city2);
  // push back the new edge
  vertex* ptrToCity1 = findVertex(city1);
  ptrToCity1->Edges.push_back(newEdge);
}

// void Graph::setAllVerticesUnvisited() ///////////////////////////////////////
// - loop through the vertices vector and set each vertex’s visited field to false
// - this function should be called right before any traversal (BFT, DFT)
//  that uses the visited member
void Graph::setAllVerticesUnvisited(){
  for(int i = 0; i < this->vertices.size(); i++){
    this->vertices[i].visited = false;
  }
}

// void Graph::DFT_traversal(vertex *v) ////////////////////////////////////////
// - perform a depth first traversal of the graph beginning with vertex v,
//  printing the name of each vertex you visit.
// - cout << v->name << endl;
void Graph::DFT_traversal(vertex *v){
  // if current vertex has not been visited yet, print it
  if(v->visited == false){
    cout << v->name << "\n";
  }
  // mark current vertex as visited
  v->visited = true;
  // recur for all vertices adjacent to this vertex
  for(int i = 0; i < v->Edges.size(); i++){
    if(v->Edges[i].v->visited == false){
      DFT_traversal(v->Edges[i].v);
    }
  }
}

// void Graph::printDFT() //////////////////////////////////////////////////////
// - use a depth first traversal of the graph to print the names of every city
//  beginning with the first vertex in your vertices vector
// - use your helper functions setAllVerticesUnvisited and DFT_traversal
// - note that there may be disconnected components in the graph!
void Graph::printDFT(){
  // set all vertices unvisited
  setAllVerticesUnvisited();
  // call the recursive helper function to print DFS traversal
  for(int i = 0; i < this->vertices.size(); i++){
    DFT_traversal(&this->vertices[i]);
  }
}


// void Graph::BFT_traversal(vertex* v) ////////////////////////////////////////
// - perform a breadth first traversal of the graph beginning with vertex v,
// - printing the name of each vertex you visit.
// - cout << v->name << endl;
void Graph::BFT_traversal(vertex *v){

  // Create a queue for BFS
  queue<vertex> myQueue;

  // enqueue vertex, and mark as visited
  v->visited = true;
  myQueue.push(*v);

  // while the queue is not empty
  while(!myQueue.empty()){

    // create a new vertex variable, and put myQueue.front() into it
    // create a new vertex variable
    vertex* newVertex = new vertex;

    *newVertex = myQueue.front();

    // print queue front, and dequeue it
    cout << newVertex->name << "\n";
    myQueue.pop();

    // get all adjacent vertices of the dequeued vertex
    for(int i = 0; i < newVertex->Edges.size(); i++){
      // if adjacent vertex has not been visited,
      if(newVertex->Edges[i].v->visited == false){
        // mark visited as true
        newVertex->Edges[i].v->visited = true;
        // enqueue it
        myQueue.push(*newVertex->Edges[i].v);
      }
    }
  }
}



// void Graph::printBFT() //////////////////////////////////////////////////////
// - use a breadth first traversal of the graph to print the names of every city
//  beginning with the first vertex in your vertices vector
// - use your helper functions setAllVerticesUnvisited and BFT_traversal
// - note that there may be disconnected components in the graph!
void Graph::printBFT(){
  // set all vertices unvisited
  setAllVerticesUnvisited();
  // call the helper function to print BFS traversal
  for(int i = 0; i < this->vertices.size(); i++){
    if(vertices[i].visited == false){
      BFT_traversal(&this->vertices[i]);
    }
  }
}

// void displayEdges() /////////////////////////////////////////////////////////

void Graph::displayEdges(){

  int distance = 0;

  // iterate through vertices vector
  for(int i = 0; i < vertices.size(); i++){
    // print vertex
    cout << vertices[i].name << "-->";

    // iterate to print adjacent vertices
    for(int j = 0; j < vertices[i].Edges.size(); j++){
      cout << vertices[i].Edges[j].v->name << " (" << distance + vertices[i].Edges[j].distance << " miles)";
      if(j != vertices[i].Edges.size() - 1){
        cout << "***";
      }
    }
    cout << "\n";

    distance = 0;
  }
}


// dynamically resize array function ///////////////////////////////////////////
void resizeArray(string **arrayPtr, int *capacity){
  // initialize int variable for new capacity of array
  int newCapacity = 0;
  // double the array capacity
  newCapacity = (*capacity) * 2;
  // dynamically allocate an array of size newCapacity
  string *newArray = new string[newCapacity];
  // copy all data from oldArray to newArray
  for(int idx = 0; idx < (*capacity); idx++){
    newArray[idx] = (*arrayPtr)[idx];
  }
  // free the memory associated with oldArray
  delete[] *arrayPtr;
  *arrayPtr = newArray;
  *capacity = newCapacity;
}


// load cities as vertices into Graph //////////////////////////////////////////
void createGraph(char *simpleCitiesTxt, Graph &myGraph){

  // initialize simpleCities.txt
  ifstream file;
  // each line of file
  string line;
  // each city in file
  string cityName;
  // vertex1 and vertex2 city names
  string vertex1;
  string vertex2;
  int vertex1ChIdx = 0;
  int vertex2ArrIdx = 0;
  // distance between cities
  string distance;

  // variables that have to do with dynamic array allocation:
  // initial capacity of vertexEndpoints array
  int maxCapacity = 10;
  // initialize dynamic array pointer
  string *vertexEndpoints;
  // allocate memory for new array of initial capacity 2
  vertexEndpoints = new string[maxCapacity];
  // counts number of elements in array so far
  int currCapacity = 0;

  // open simpleCities.txt
  file.open(simpleCitiesTxt);

  // read first line of simpleCities.txt
  // first row of txt: cities,Boulder,Denver,Chicago,Boston,Austin
  getline(file, line);
  // these are the vertex cities, store them as vertices
  for(int idxLine = 7; line[idxLine] != '\0'; idxLine++){
    // before each comma is reached, add each char of the city to the "city" variable
    if(line[idxLine] != ','){
      cityName += line[idxLine];
    }
    // if a comma is reached, or if end of first line is reached,
    if(line[idxLine] == ',' || line[idxLine + 1] == '\0'){
      // store city as a vertex in graph
      myGraph.addVertex(cityName);
      // if vertexEndpoints array capacity limit is met, resize the array
      if(currCapacity == maxCapacity){
        resizeArray(&vertexEndpoints, &maxCapacity);
      }
      // otherwise, store city in vertexEndpoints array
      vertexEndpoints[currCapacity] = cityName;
      // with each city, curr capacity of vertexEndpoints array increments
      currCapacity++;
      // re-initialize "city" as empty string
      cityName = "";
    }
  }

  // debug //////////////////////////////////
  // read second line
  while(getline(file, line)){
    // read vertex 1 cityname
    for(int idxLine = 0; line[idxLine] != ','; idxLine++){
      vertex1 += line[idxLine];
      vertex1ChIdx = idxLine + 2;
    }

    // now read the distances
    for(int idxLine = vertex1ChIdx; line[idxLine] != '\0'; idxLine++){

      // before each comma is reached, add each char of the distance to the "distance" variable
      if(line[idxLine] != ','){
        distance += line[idxLine];
      }

      // if a comma is reached, or if end of first line is reached,
      if(line[idxLine] == ',' || line[idxLine + 1] == '\0'){
        // we already know vertex1 name -- it is simply vertex1
        // we already know vertex2 name == it is vertexEndpoints[vertex2ArrIdx]
        // we already know the distance -- it is simply stoi(distance)
        if(distance != "0" && distance != "-1"){
          cout << " ... Reading in " << vertex1 << " -- " << vertexEndpoints[vertex2ArrIdx] << " -- " << distance << "\n";
          myGraph.addEdge(vertex1, vertexEndpoints[vertex2ArrIdx], stoi(distance));
        }
        // vertex2ArrIdx increments
        vertex2ArrIdx++;
        // re-initialize distance to empty string
        distance = "";
      }
    }

    vertex2ArrIdx = 0;
    vertex1 = "";
  }

  // close simpleCities.txt
  file.close();

}


// driver //////////////////////////////////////////////////////////////////////
// Your program will take exactly one command line argument
// - simpleCities.txt
int main(int argc, char *argv[]){
  // instantiate file
  char* simpleCitiesTxt = argv[1];
  // instantiate a graph
  Graph myGraph;
  // put file info into graph
  createGraph(simpleCitiesTxt, myGraph);

  cout << "------------------------------ \n";
  cout << "Breadth First Traversal\n";
  cout << "------------------------------\n";
  myGraph.printBFT();
  cout << "------------------------------ \n";
  cout << "Depth First Traversal\n";
  cout << "------------------------------\n";
  myGraph.printDFT();
  cout << "------------------------------ \n";
  cout << "Display Edges\n";
  cout << "------------------------------\n";
  myGraph.displayEdges();

  return 0;
}
