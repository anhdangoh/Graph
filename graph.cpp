/*****************************************************************************
GRAPH OPERATION PROGRAM
INPUT: a graph in the format 'V x1 x2 x3 x4 .. xn -1'
  with V is the number of vertices of the GRAPH
  with x1 x2, x3 x4,... are edges, n must be even
OPERATION:
  get ajacency matrix
  BFS with a specific root
  get distance matrix and determine whether the graph is connected
  get diameter if the graph is connected
  get groups of connected vertices
OUTPUT
  number of edges
  matrix of edges
  adjacency matrix
  diameter
  number of groups (connected vertices)
  vertices of each group
******************************************************************************/


#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <queue>
#include <vector>
#include "../lib/table.h"
using namespace std;

//Return the Adjacency matrix of the Graph, taking inputs of the matrix of pairs
//the no of vertices and no of edges
int** graph::adjacencyMatrix(int** edges, int vertices, int num_of_edges){
  int** matrix = createTable(vertices, vertices); //create the return matrix as a pointer to 2 dimensional array
  for (int i = 0; i < num_of_edges; i++){ //scan all the pairs and set matrix[i,j] and [j,i] = 1 with each (i,j) pair
    matrix[edges[i][0]][edges[i][1]] = 1;
    matrix[edges[i][1]][edges[i][0]] = 1;
  }
  return matrix;
}


//Return an array of distance to the given root using BFS algorithm
int* graph::BFS(int** adjacency_matrix, int vertices, int root){
  int* distance_to_root = new int[vertices]; //create the return array
  for (int k = 0; k < vertices; k++){
    distance_to_root[k] = 0;
  }

  bool visited[vertices] = {false}; //create an array for visit attribute of each vertex, default not visited
  visited[root] = true; //set root visited
  queue <int> my_queue; //create a queue of adjacent vertices to current node
  my_queue.push(root); //add root to the queue as the first visited node
  int current_node = 0;

  //scan graph as long as there are unvisited nodes and compute distance of each unvisited node
  while (!my_queue.empty()){
    current_node = my_queue.front(); //visit the front of the queue
    my_queue.pop(); //remove this node from the queue after being taken for a visit
    //scan all nodes to find adjacent ones to the current node
    for (int i = 0; i < vertices; i++){
      if (adjacency_matrix[current_node][i]==1){ // check adjacency to the being visited node
        if (!visited[i]){ // check if the adjacent node is not visited
          visited[i] = true; // mark visited
          my_queue.push(i); // add to the queue
          distance_to_root[i] = distance_to_root[current_node] + 1; //get the distance for this node
        }
      }
    }
  }
  return distance_to_root;
}


//Return a distance matrix of all nodes by applying BFS with every node as root
//Return true if the graph is connected and otherwise
bool graph::DistanceMatrix(int** input_adjacency, int** output_distance, int vertices){
  bool connected = true;
  for (int i = 0; i < vertices; i++){
    output_distance[i] = BFS(input_adjacency, vertices, i);
  }

  //Replace disconnected pairs with -1 instead of 0
  //and check weather the graph is disconnected to return 0
  //in such case, there is at least 1 line with all value 0
  for (int i = 0; i < vertices; i++){
    for (int j = 0; j < vertices; j++){
      if (output_distance[i][j] == 0){
        output_distance[i][j] = -1;
        if (i!=j){
          connected = false;
        }
      }
    }
  }
  return connected;
}


//Return the diameter of the graph if all vertices are connect, -1 otherwise
//Diameter is the max distance between 2 vertices
int graph::Diameter(int** adjacency_matrix, int vertices){
  int** distance = createTable(vertices, vertices);
  bool connected;
  connected = DistanceMatrix(adjacency_matrix, distance, vertices);
  if (!connected){
    freeTable(distance, vertices);
    return -1;
  }else{
    int distance_max = 0;
    for (int i = 0; i < vertices; i++){
      for (int j = 0; j < vertices; j++){
        if (distance[i][j] >= distance_max){
          distance_max = distance[i][j];
        }
      }
    }
    freeTable(distance, vertices);
    return distance_max;
  }
}


//Find all vertices that are connected
void graph::Components(int** adjacency_matrix, int vertices){
  int** distance = createTable(vertices, vertices);
  bool connected = false;
  //create a distance matrix by passing an empty one to DistanceMatrix
  connected = DistanceMatrix(adjacency_matrix, distance, vertices);

  if (connected){
    cout << "All vertices are connected\n";
  }else{
    //Use a vector, each element is a queue to store a group of connected vertices
    vector<queue<int>> component;
    component.push_back(queue<int>());  //Make the 1st queue
    component[0].push(0); //Put vertex 0 into the 1st queue
    bool flag = false;
    //Visit all remaining vertices
    for (int i = 1; i < vertices; i++){
      flag = false;
      //Check connectivity with available groups
      for (int j = 0; j < component.size(); j++){
        if (distance[i][component[j].front()]!=-1){
          //If connected then put the vertex into this group and set the flag
          component[j].push(i);
          flag = true;
          break;
        }
      }
      //If the vertex is not connected to any group then make a new group with it
      if (!flag){
        component.push_back(queue<int>());
        component[component.size()-1].push(i);
      }
    }
    //print
    cout << "The component size: " << component.size() << endl;
    cout << "The connected groups of vertices:\n";
    for (int i = 0; i < component.size(); i++){
        while (!component[i].empty()){
          cout << component[i].front() << "\t";
          component[i].pop();
        }
        cout << endl;
    }
  }
  freeTable(distance, vertices); //delete distance matrix
}
