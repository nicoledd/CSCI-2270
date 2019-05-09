/* Assignment 9 - Graphs

OBJECTIVES
1. Build an undirected weighted graph
2. Perform Breadth First Traversal (BFT) and Depth First Traversal (DFT) */





#include "HW9.hpp"






/* searches for a returns a pointer to the vertex with the specified name */
vertex* Graph::findVertex(std::string name){

  /* iterate through the collection of vertices */
  for(int i = 0; i < this->vertices.size(); i++){
    /* if the name is found, return pointer to that vertex */
    if(this->vertices[i].name == name){
      return &this->vertices[i];
    }
  }

  /* if not found, return null */
  return NULL;
}






/* create a new vertex, and push it into the graph's collection of vertices */
void Graph::addVertex(std::string cityName){
  vertex newVertex;
  newVertex.name = cityName;
  newVertex.visited = false;

  this->vertices.push_back(newVertex);
}







/* establishes a single edge from startCity to endCity, with weight 'distance' */
void Graph::addEdge(std::string startCity, std::string endCity, int distance){

  /* allocate a new edge, and initialize its 'distance' and 'v' fields,
    where v is a pointer to the endCity */
  Edge newEdge;
  newEdge.distance = distance;
  newEdge.v = findVertex(endCity);

  /* add this new edge to the 'Edges' vector field for the startCity, which is
    a collection of pointers to the cities that are adjacent to startCity */
  findVertex(startCity)->Edges.push_back(newEdge);
}






/* set all vertices unvisited by iterating through the vertices vector
  and setting each vertex's 'visited' field to false
  - this function should be called before BFT and DFT */
void Graph::setAllVerticesUnvisited(){
  for(int i = 0; i < this->vertices.size(); i++){
    this->vertices[i].visited = false;
  }
}







/* prints depth-first traversal of a given vertex */
void Graph::DFT_traversal(vertex *startVertex){
  /* if the current vertex has not been visited yet, print it and mark it as
    visited */
  if(startVertex->visited == false){
    std::cout << startVertex->name << "\n";
  }
  startVertex->visited = true;

  /* now recur for all vertices adjacent to this starting vertex */
  for(int i = 0; i < startVertex->Edges.size(); i++){
    if(startVertex->Edges[i].v->visited == false){
      DFT_traversal(startVertex->Edges[i].v);
    }
  }
}






/* print the graph using depth-first traversal */
void Graph::printDFT(){
  /* set all vertices unvisited */
  setAllVerticesUnvisited();
  /* call DFT_traversal on each vertex (since the graph may be disconnected) */
  for(int i = 0; i < this->vertices.size(); i++){
    DFT_traversal(&this->vertices[i]);
  }
}






/* given a vertex, print its breadth-first traversal */
void Graph::BFT_traversal(vertex *startVertex){

  /* initialize a queue */
  std::queue<vertex> myQueue;

  /* enqueue this vertex, and mark it as visited */
  startVertex->visited = true;
  myQueue.push(*startVertex);

  /* while the queue is not empty, repeat this while-loop */
  while(!myQueue.empty()){

    /* create a new vertex variable, and let it equal the queue front. */
    vertex* newVertex = new vertex;
    *newVertex = myQueue.front();

    /* print the queue front, and dequeue */
    std::cout << newVertex->name << "\n";
    myQueue.pop();

    /* iterate through all adjacent vertices of the dequeued vertex */
    for(int i = 0; i < newVertex->Edges.size(); i++){
      /* if the adjacent vertex has not yet been visited, mark its
        'visited' field as true, and enqueue it */
      if(newVertex->Edges[i].v->visited == false){
        newVertex->Edges[i].v->visited = true;
        myQueue.push(*newVertex->Edges[i].v);
      }
    }
  }
}






/* print the graph using breadth-first traversal */
void Graph::printBFT(){

  /* set all vertices unvisited */
  setAllVerticesUnvisited();

  /* call BFT_traversal on each vertex (since the graph may be disconnected) */
  for(int i = 0; i < this->vertices.size(); i++){
    if(vertices[i].visited == false){
      BFT_traversal(&this->vertices[i]);
    }
  }
}






/* display all edges of graph as an adjacency list */
void Graph::displayEdges(){

  /* initialize variable 'distance' for the distance between the starting
    vertex and its adjacent vertex */
  int distance = 0;

  /* iterate through each vertex, printing each vertex and its adjacent vertices */
  for(int i = 0; i < vertices.size(); i++){
    /* print the vertex */
    std::cout << vertices[i].name << "-->";

    /* iterate through all its adjacent vertices, and print them too */
    for(int j = 0; j < vertices[i].Edges.size(); j++){
      std::cout << vertices[i].Edges[j].v->name << " (" << distance + vertices[i].Edges[j].distance << " miles)";
      if(j != vertices[i].Edges.size() - 1){
        std::cout << "***";
      }
    }
    std::cout << "\n";

    /* re-initialize 'distance' variable */
    distance = 0;
  }
}






/* dynamically resize given array */
void resizeArray(std::string **oldArray, int *capacity){

  /* allocate new array with a new size that is double the size of the old one */
  std::string *newArray = new std::string[(*capacity) * 2];

  /* copy all data from old array to new array */
  for(int idx = 0; idx < (*capacity); idx++){
    newArray[idx] = (*oldArray)[idx];
  }

  /* free all memory associated with oldArray */
  delete[] *oldArray;
  *oldArray = newArray;
  *capacity *= 2;
}







/* load cities as vertices into Graph */
void createGraph(char *simpleCitiesTxt, Graph &myGraph){

  /* initialize variables for reading file */
  std::ifstream file;
  std::string line;
  std::string cityName, vertexStart, distance;
  int vertexStartIdx = 0;

  /* initialize variables for dynamic array allocation */
  int currCapacity = 0;
  int maxCapacity = 10;
  int arrIdx = 0;
  std::string *vertexEnds;
  vertexEnds = new std::string[maxCapacity];

  /* open the file */
  file.open(simpleCitiesTxt);

  /* Read the first line of the file. It contains a list of all the cities,
    separated by commas. Store them all as vertices in the graph */
  getline(file, line);

  for(int idxLine = 7; line[idxLine] != '\0'; idxLine++){
    /* read the name of each city */
    if(line[idxLine] != ','){
      cityName += line[idxLine];
    }

    /* store each city as a vertex in the graph */
    if(line[idxLine] == ',' || line[idxLine + 1] == '\0'){
      myGraph.addVertex(cityName);

      /* if the max capacity of vertexEndpoints array is met, resize the array */
      if(currCapacity == maxCapacity){
        resizeArray(&vertexEnds, &maxCapacity);
      }
      /* store each city in the vertexEndpoints array */
      vertexEnds[currCapacity] = cityName;

      /* increment currCapacity of vertexEndpoints array, and re-initialize
        the relevant variables*/
      currCapacity++;
      cityName = "";
    }
  }

  /* now start reading from the second line of the file */
  while(getline(file, line)){

    /* read the name of the starting vertex */
    for(int idxLine = 0; line[idxLine] != ','; idxLine++){
      vertexStart += line[idxLine];
      vertexStartIdx = idxLine + 2;
    }

    /* continue reading the file */
    for(int idxLine = vertexStartIdx; line[idxLine] != '\0'; idxLine++){

      /* now read the distance between vertexStart and vertexEnd */
      if(line[idxLine] != ','){
        distance += line[idxLine];
      }

      /* for each distance, add an edge between the starting vertex and
        end vertex, with a weight of 'distance'. We know the end vertex by
        using the vertexEndpoints array */
      if(line[idxLine] == ',' || line[idxLine + 1] == '\0'){
        /* disregard the distance if it is either 0 or -1 */
        if(distance != "0" && distance != "-1"){
          std::cout << " ... Reading in " << vertexStart << " -- " << vertexEnds[arrIdx] << " -- " << distance << "\n";
          myGraph.addEdge(vertexStart, vertexEnds[arrIdx], stoi(distance));
        }
        arrIdx++;
        distance = "";
      }
    }

    /* re-initialize relevant variables */
    arrIdx = 0;
    vertexStart = "";
  }

  /* close the file */
  file.close();
}








/* driver function takes in one command line argument: HW9.txt */
int main(int argc, char *argv[]){

  /* instantiate a graph */
  Graph myGraph;

  /* put file info into graph */
  createGraph(argv[1], myGraph);

  /* print breadth-first traversal of graph */
  std::cout << "------------------------------ \n";
  std::cout << "Breadth First Traversal\n";
  std::cout << "------------------------------\n";
  myGraph.printBFT();

  /* print depth-first traversal of graph */
  std::cout << "------------------------------ \n";
  std::cout << "Depth First Traversal\n";
  std::cout << "------------------------------\n";
  myGraph.printDFT();

  /* display edges of graph as an adjacency list */
  std::cout << "------------------------------ \n";
  std::cout << "Display Edges\n";
  std::cout << "------------------------------\n";
  myGraph.displayEdges();

  return 0;
}
