#include <iostream>
#include <string>
#include <vector>
using namespace std;
#define NUM_OF_VAR 4
#define NUM_OF_ROWS 16

class KarnaughMap {
 public:
  bool truth_table[NUM_OF_ROWS][NUM_OF_VAR + 1] = {
      {0, 0, 0, 0, 0}, {0, 0, 0, 1, 0}, {0, 0, 1, 0, 0}, {0, 0, 1, 1, 0},
      {0, 1, 0, 0, 0}, {0, 1, 0, 1, 0}, {0, 1, 1, 0, 0}, {0, 1, 1, 1, 0},
      {1, 0, 0, 0, 0}, {1, 0, 0, 1, 0}, {1, 0, 1, 0, 0}, {1, 0, 1, 1, 0},
      {1, 1, 0, 0, 0}, {1, 1, 0, 1, 0}, {1, 1, 1, 0, 0}, {1, 1, 1, 1, 0}};
  bool matrix[4][4];
  vector<vector<int>> taken_indexes;
  vector<vector<vector<int>>> groups;
  string DNF = "";

  KarnaughMap(string function);
  void printTruthTable();
  void printKarnaughMap();
  bool &operator()(int i, int j);
  bool is_taken(int i, int j);
  bool is_in_group(vector<vector<int>> group, int i, int j);
  int max_amount_of_neighbours(int i, int j);
  void gluing(int i, int j, int n_neighbours);
  void grouping();
  void group_to_DNF(vector<vector<int>> group);
  void to_DNF();
  void print_vector();
};
