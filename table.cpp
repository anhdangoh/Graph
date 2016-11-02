

#include <iostream>

using namespace std;
//Create a 2 dimensional table which is a pointer to an array of pointers
//each pointing to an array of each row
int** createTable(int rows, int columns){
  //get the return pointer pointing to a new array of pointers with rows elements
  int** table = new int*[rows];
  for (int i = 0; i < rows; i++) {
    //get each pointer of the array pointing to a new array of columns elements
    table[i] = new int[columns];
  }
  return table;
}


//Delete table
void freeTable(int** table, int rows){
  if (table){
    for (int i = 0; i < rows; i++){
      if (table[i]){
        delete[] table[i];
        table[i] = NULL;
      }
    }
  }
  delete table;
  table = NULL;
}


//Print table
void printTable(int** table, int rows, int columns){
  for (int i = 0; i < rows; i++){
    for (int j = 0; j < columns; j++){
      printf("%d\t", table[i][j]);
    }
    cout << "\n";
  }
  cout << endl;
}
