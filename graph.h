
#include <vector>
#include "../src/graph.cpp"

using namespace std;

class graph{
public:
  int vertex;
  vector <int> edges;

  graph(int);
  void setEdges(string);
  void setVertex(int);

  //Get class variables
  int getVertex();
  vector<int> getEdges();

  //Operations on table
  int** createTable(int, int);
  void freeTable(int**, int);
  void printTable(int**, int, int);

  //Operations on graph

  //Return adjacency matrix
  //Input: edges vector, no of vertices
  int** adjacencyMatrix(vector<int>, int);

  //Return a pointer to an array of distance to a given root using BFS or DFS
  //Input: adjacency matrix, no of vertices and root number
  int* BFS(int**, int , int);
  int* DFS(int**, int , int);

  //Return distance matrix and connectivity
  //True if all connected and 0 otherwise
  //Input: adjacency matrix, output distance matrix and number of vertices
  bool distanceMatrix(int**, int**, int);

  //Return the diameter if the graph is connected, -1 otherwise
  //Input: adjacency matrix and no of vertices
  int Diameter(int** adjacency_matrix, int vertices);

  //Print connected groups of vertices
  //Input: adjacency matrix, no of vertices
  void Components(int** adjacency_matrix, int vertices)

};
