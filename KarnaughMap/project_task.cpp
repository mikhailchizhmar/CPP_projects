#include "project_task.h"

bool validation(string function) {
  if (function.size() != 16) return false;
  for (int i = 0; i < 16; i++) {
    if (function[i] != '0' && function[i] != '1') return false;
  }
  return true;
}

KarnaughMap::KarnaughMap(string function) {
  for (int i = 0; i < NUM_OF_ROWS; i++) {
    if (function[i] == '0') {
      truth_table[i][NUM_OF_VAR] = 0;
    } else
      truth_table[i][NUM_OF_VAR] = 1;
  }
  matrix[0][0] = truth_table[0][NUM_OF_VAR];
  matrix[0][1] = truth_table[1][NUM_OF_VAR];
  matrix[0][2] = truth_table[3][NUM_OF_VAR];
  matrix[0][3] = truth_table[2][NUM_OF_VAR];
  matrix[1][0] = truth_table[4][NUM_OF_VAR];
  matrix[1][1] = truth_table[5][NUM_OF_VAR];
  matrix[1][2] = truth_table[7][NUM_OF_VAR];
  matrix[1][3] = truth_table[6][NUM_OF_VAR];
  matrix[2][0] = truth_table[12][NUM_OF_VAR];
  matrix[2][1] = truth_table[13][NUM_OF_VAR];
  matrix[2][2] = truth_table[15][NUM_OF_VAR];
  matrix[2][3] = truth_table[14][NUM_OF_VAR];
  matrix[3][0] = truth_table[8][NUM_OF_VAR];
  matrix[3][1] = truth_table[9][NUM_OF_VAR];
  matrix[3][2] = truth_table[11][NUM_OF_VAR];
  matrix[3][3] = truth_table[10][NUM_OF_VAR];
}

void KarnaughMap::printTruthTable() {
  cout << "--------------\n";
  cout << "| a b c d | f|\n";
  cout << "--------------\n";
  for (int i = 0; i < NUM_OF_ROWS; i++) {
    cout << "|";
    for (int j = 0; j < NUM_OF_VAR + 1; j++) {
      cout << (j == NUM_OF_VAR ? " | " : " ") << truth_table[i][j];
    }
    cout << "|\n";
  }
  cout << "--------------\n";
  cout << "\n";
}

void KarnaughMap::printKarnaughMap() {
  cout << "-------------\n";
  cout << "|\\ d|0|1|1|0|\n";
  cout << "| \\c|0|0|1|1|\n";
  cout << "|ab\\| | | | |\n";
  cout << "-------------\n";
  cout << "|00 |" << matrix[0][0] << "|" << matrix[0][1] << "|" << matrix[0][2]
       << "|" << matrix[0][3] << "|\n";
  cout << "|01 |" << matrix[1][0] << "|" << matrix[1][1] << "|" << matrix[1][2]
       << "|" << matrix[1][3] << "|\n";
  cout << "|11 |" << matrix[2][0] << "|" << matrix[2][1] << "|" << matrix[2][2]
       << "|" << matrix[2][3] << "|\n";
  cout << "|10 |" << matrix[3][0] << "|" << matrix[3][1] << "|" << matrix[3][2]
       << "|" << matrix[3][3] << "|\n";
  cout << "-------------\n";
}

bool& KarnaughMap::operator()(int i, int j) {
  if (i < 0) i = 4 + i;
  if (i > 3) i = i % 4;
  if (j < 0) j = 4 + j;
  if (j > 3) j = j % 4;
  return matrix[i][j];
}

bool KarnaughMap::is_taken(int i, int j) {
  for (const vector<int>& vec : taken_indexes) {
    if (vec[0] == i && vec[1] == j) {
      return true;
    }
  }
  return false;
}

bool KarnaughMap::is_in_group(vector<vector<int>> group, int i, int j) {
  for (const vector<int>& vec : group) {
    if (vec[0] == i && vec[1] == j) {
      return true;
    }
  }
  return false;
}

int KarnaughMap::max_amount_of_neighbours(int i, int j) {
  bool all_neighbours = 1;
  for (int n = 0; n < 4; n++) {
    for (int k = 0; k < 4; k++) {
      if (!(*this)(n, k)) all_neighbours = 0;
    }
  }
  if (all_neighbours) return 15;

  if (((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3) &&
       (*this)(i + 1, j) && (*this)(i + 1, j + 1) && (*this)(i + 1, j + 2) &&
       (*this)(i + 1, j + 3)) ||
      ((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3) &&
       (*this)(i - 1, j) && (*this)(i - 1, j + 1) && (*this)(i - 1, j + 2) &&
       (*this)(i - 1, j + 3)) ||
      ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j) &&
       (*this)(i, j + 1) && (*this)(i + 1, j + 1) && (*this)(i + 2, j + 1) &&
       (*this)(i + 3, j + 1)) ||
      ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j) &&
       (*this)(i, j - 1) && (*this)(i + 1, j - 1) && (*this)(i + 2, j - 1) &&
       (*this)(i + 3, j - 1)))
    return 7;

  if (((*this)(i, j - 1) && (*this)(i - 1, j) && (*this)(i - 1, j - 1)) ||
      ((*this)(i - 1, j) && (*this)(i, j + 1) && (*this)(i - 1, j + 1)) ||
      ((*this)(i, j - 1) && (*this)(i + 1, j) && (*this)(i + 1, j - 1)) ||
      ((*this)(i, j + 1) && (*this)(i + 1, j) && (*this)(i + 1, j + 1)) ||
      ((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3)) ||
      ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j)))
    return 3;

  if ((*this)(i, j - 1) || (*this)(i - 1, j) || (*this)(i, j + 1) ||
      (*this)(i + 1, j)) {
    return 1;
  } else {
    return 0;
  }
}

void KarnaughMap::gluing(int i, int j, int n_neighbours) {
  (*this).taken_indexes.push_back({i, j});
  vector<int> neighbour1, neighbour2, neighbour3, neighbour4, neighbour5,
      neighbour6, neighbour7;
  if (n_neighbours == 0) {
    (*this).groups.push_back({{i, j}});

  } else if (n_neighbours == 1) {
    if ((*this)(i, j - 1)) {
      neighbour1 = {i, (j - 1 + 4) % 4};
    } else if ((*this)(i - 1, j)) {
      neighbour1 = {(i - 1 + 4) % 4, j};
    } else if ((*this)(i, j + 1)) {
      neighbour1 = {i, (j + 1) % 4};
    } else if ((*this)(i + 1, j)) {
      neighbour1 = {(i + 1) % 4, j};
    }
    (*this).groups.push_back({{i, j}, neighbour1});
    (*this).taken_indexes.push_back(neighbour1);

  } else if (n_neighbours == 3) {
    if ((*this)(i, j - 1) && (*this)(i - 1, j) && (*this)(i - 1, j - 1)) {
      neighbour1 = {i, (j - 1 + 4) % 4};
      neighbour2 = {(i - 1 + 4) % 4, j};
      neighbour3 = {(i - 1 + 4) % 4, (j - 1 + 4) % 4};
    } else if ((*this)(i - 1, j) && (*this)(i, j + 1) &&
               (*this)(i - 1, j + 1)) {
      neighbour1 = {(i - 1 + 4) % 4, j};
      neighbour2 = {i, (j + 1) % 4};
      neighbour3 = {(i - 1 + 4) % 4, (j + 1) % 4};
    } else if ((*this)(i, j - 1) && (*this)(i + 1, j) &&
               (*this)(i + 1, j - 1)) {
      neighbour1 = {i, (j - 1 + 4) % 4};
      neighbour2 = {(i + 1) % 4, j};
      neighbour3 = {(i + 1) % 4, (j - 1 + 4) % 4};
    } else if ((*this)(i, j + 1) && (*this)(i + 1, j) &&
               (*this)(i + 1, j + 1)) {
      neighbour1 = {i, (j + 1) % 4};
      neighbour2 = {(i + 1) % 4, j};
      neighbour3 = {(i + 1) % 4, (j + 1) % 4};
    } else if ((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3)) {
      neighbour1 = {i, (j + 1) % 4};
      neighbour2 = {i, (j + 2) % 4};
      neighbour3 = {i, (j + 3) % 4};
    } else if ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j)) {
      neighbour1 = {(i + 1) % 4, j};
      neighbour2 = {(i + 2) % 4, j};
      neighbour3 = {(i + 3) % 4, j};
    }
    (*this).groups.push_back({{i, j}, neighbour1, neighbour2, neighbour3});
    (*this).taken_indexes.push_back(neighbour1);
    (*this).taken_indexes.push_back(neighbour2);
    (*this).taken_indexes.push_back(neighbour3);

  } else if (n_neighbours == 7) {
    if ((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3) &&
        (*this)(i + 1, j) && (*this)(i + 1, j + 1) && (*this)(i + 1, j + 2) &&
        (*this)(i + 1, j + 3)) {
      neighbour1 = {i, (j + 1) % 4};
      neighbour2 = {i, (j + 2) % 4};
      neighbour3 = {i, (j + 3) % 4};
      neighbour4 = {(i + 1) % 4, j};
      neighbour5 = {(i + 1) % 4, (j + 1) % 4};
      neighbour6 = {(i + 1) % 4, (j + 2) % 4};
      neighbour7 = {(i + 1) % 4, (j + 3) % 4};
    } else if ((*this)(i, j + 1) && (*this)(i, j + 2) && (*this)(i, j + 3) &&
               (*this)(i - 1, j) && (*this)(i - 1, j + 1) &&
               (*this)(i - 1, j + 2) && (*this)(i - 1, j + 3)) {
      neighbour1 = {i, (j + 1) % 4};
      neighbour2 = {i, (j + 2) % 4};
      neighbour3 = {i, (j + 3) % 4};
      neighbour4 = {(i - 1 + 4) % 4, j};
      neighbour5 = {(i - 1 + 4) % 4, (j + 1) % 4};
      neighbour6 = {(i - 1 + 4) % 4, (j + 2) % 4};
      neighbour7 = {(i - 1 + 4) % 4, (j + 3) % 4};
    } else if ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j) &&
               (*this)(i, j + 1) && (*this)(i + 1, j + 1) &&
               (*this)(i + 2, j + 1) && (*this)(i + 3, j + 1)) {
      neighbour1 = {(i + 1) % 4, j};
      neighbour2 = {(i + 2) % 4, j};
      neighbour3 = {(i + 3) % 4, j};
      neighbour4 = {i, (j + 1) % 4};
      neighbour5 = {(i + 1) % 4, (j + 1) % 4};
      neighbour6 = {(i + 2) % 4, (j + 1) % 4};
      neighbour7 = {(i + 3) % 4, (j + 1) % 4};
    } else if ((*this)(i + 1, j) && (*this)(i + 2, j) && (*this)(i + 3, j) &&
               (*this)(i, j - 1) && (*this)(i + 1, j - 1) &&
               (*this)(i + 2, j - 1) && (*this)(i + 3, j - 1)) {
      neighbour1 = {(i + 1) % 4, j};
      neighbour2 = {(i + 2) % 4, j};
      neighbour3 = {(i + 3) % 4, j};
      neighbour4 = {i, (j - 1 + 4) % 4};
      neighbour5 = {(i + 1) % 4, (j - 1 + 4) % 4};
      neighbour6 = {(i + 2) % 4, (j - 1 + 4) % 4};
      neighbour7 = {(i + 3) % 4, (j - 1 + 4) % 4};
    }
    (*this).groups.push_back({{i, j},
                              neighbour1,
                              neighbour2,
                              neighbour3,
                              neighbour4,
                              neighbour5,
                              neighbour6,
                              neighbour7});
    (*this).taken_indexes.push_back(neighbour1);
    (*this).taken_indexes.push_back(neighbour2);
    (*this).taken_indexes.push_back(neighbour3);
    (*this).taken_indexes.push_back(neighbour4);
    (*this).taken_indexes.push_back(neighbour5);
    (*this).taken_indexes.push_back(neighbour6);
    (*this).taken_indexes.push_back(neighbour7);
  } else if (n_neighbours == 15) {
    (*this).groups = {{{0, 0},
                       {0, 1},
                       {0, 2},
                       {0, 3},
                       {1, 0},
                       {1, 1},
                       {1, 2},
                       {1, 3},
                       {2, 0},
                       {2, 1},
                       {2, 2},
                       {2, 3},
                       {3, 0},
                       {3, 1},
                       {3, 2},
                       {3, 3}}};
    for (int n = 0; n < 4; n++) {
      for (int k = 0; k < 4; k++) {
        (*this).taken_indexes.push_back({n, k});
      }
    }
  }
}

void KarnaughMap::grouping() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if ((*this)(i, j)) {
        if (!(*this).is_taken(i, j)) {
          (*this).gluing(i, j, (*this).max_amount_of_neighbours(i, j));
        }
      }
    }
  }
}

void KarnaughMap::group_to_DNF(vector<vector<int>> group) {
  if (group.size() == 1) {
    if (group[0][0] == 0) {
      if (group[0][1] == 0) {
        DNF += "a'b'c'd'";
      } else if (group[0][1] == 1) {
        DNF += "a'b'c'd";
      } else if (group[0][1] == 2) {
        DNF += "a'b'cd";
      } else if (group[0][1] == 3) {
        DNF += "a'b'cd'";
      }
    } else if (group[0][0] == 1) {
      if (group[0][1] == 0) {
        DNF += "a'bc'd'";
      } else if (group[0][1] == 1) {
        DNF += "a'bc'd";
      } else if (group[0][1] == 2) {
        DNF += "a'bcd";
      } else if (group[0][1] == 3) {
        DNF += "a'bcd'";
      }
    } else if (group[0][0] == 2) {
      if (group[0][1] == 0) {
        DNF += "abc'd'";
      } else if (group[0][1] == 1) {
        DNF += "abc'd";
      } else if (group[0][1] == 2) {
        DNF += "abcd";
      } else if (group[0][1] == 3) {
        DNF += "abcd'";
      }
    } else if (group[0][0] == 3) {
      if (group[0][1] == 0) {
        DNF += "ab'c'd'";
      } else if (group[0][1] == 1) {
        DNF += "ab'c'd";
      } else if (group[0][1] == 2) {
        DNF += "ab'cd";
      } else if (group[0][1] == 3) {
        DNF += "ab'cd'";
      }
    }
  } else if (group.size() == 2) {
    if ((group[0][1] == 0 && group[1][1] == 1) ||
        (group[0][1] == 1 && group[1][1] == 0)) {
      if (group[0][0] == 0 && group[1][0] == 0) {
        DNF += "a'b'c'";
      } else if (group[0][0] == 1 && group[1][0] == 1) {
        DNF += "a'bc'";
      } else if (group[0][0] == 2 && group[1][0] == 2) {
        DNF += "abc'";
      } else if (group[0][0] == 3 && group[1][0] == 3) {
        DNF += "ab'c'";
      }
    } else if ((group[0][1] == 1 && group[1][1] == 2) ||
               (group[0][1] == 2 && group[1][1] == 1)) {
      if (group[0][0] == 0 && group[1][0] == 0) {
        DNF += "a'b'd";
      } else if (group[0][0] == 1 && group[1][0] == 1) {
        DNF += "a'bd";
      } else if (group[0][0] == 2 && group[1][0] == 2) {
        DNF += "abd";
      } else if (group[0][0] == 3 && group[1][0] == 3) {
        DNF += "ab'd";
      }
    } else if ((group[0][1] == 2 && group[1][1] == 3) ||
               (group[0][1] == 3 && group[1][1] == 2)) {
      if (group[0][0] == 0 && group[1][0] == 0) {
        DNF += "a'b'c";
      } else if (group[0][0] == 1 && group[1][0] == 1) {
        DNF += "a'bc";
      } else if (group[0][0] == 2 && group[1][0] == 2) {
        DNF += "abc";
      } else if (group[0][0] == 3 && group[1][0] == 3) {
        DNF += "ab'c";
      }
    } else if ((group[0][1] == 0 && group[1][1] == 3) ||
               (group[0][1] == 3 && group[1][1] == 0)) {
      if (group[0][0] == 0 && group[1][0] == 0) {
        DNF += "a'b'd'";
      } else if (group[0][0] == 1 && group[1][0] == 1) {
        DNF += "a'bd'";
      } else if (group[0][0] == 2 && group[1][0] == 2) {
        DNF += "abd'";
      } else if (group[0][0] == 3 && group[1][0] == 3) {
        DNF += "ab'd'";
      }
    }

    else if ((group[0][0] == 0 && group[1][0] == 1) ||
             (group[0][0] == 1 && group[1][0] == 0)) {
      if (group[0][1] == 0 && group[1][1] == 0) {
        DNF += "a'c'd'";
      } else if (group[0][1] == 1 && group[1][1] == 1) {
        DNF += "a'c'd";
      } else if (group[0][1] == 2 && group[1][1] == 2) {
        DNF += "a'cd";
      } else if (group[0][1] == 3 && group[1][1] == 3) {
        DNF += "a'cd'";
      }
    } else if ((group[0][0] == 1 && group[1][0] == 2) ||
               (group[0][0] == 2 && group[1][0] == 1)) {
      if (group[0][1] == 0 && group[1][1] == 0) {
        DNF += "bc'd'";
      } else if (group[0][1] == 1 && group[1][1] == 1) {
        DNF += "bc'd";
      } else if (group[0][1] == 2 && group[1][1] == 2) {
        DNF += "bcd";
      } else if (group[0][1] == 3 && group[1][1] == 3) {
        DNF += "bcd'";
      }
    } else if ((group[0][0] == 2 && group[1][0] == 3) ||
               (group[0][0] == 3 && group[1][0] == 2)) {
      if (group[0][1] == 0 && group[1][1] == 0) {
        DNF += "ac'd'";
      } else if (group[0][1] == 1 && group[1][1] == 1) {
        DNF += "ac'd";
      } else if (group[0][1] == 2 && group[1][1] == 2) {
        DNF += "acd";
      } else if (group[0][1] == 3 && group[1][1] == 3) {
        DNF += "acd'";
      }
    } else if ((group[0][0] == 3 && group[1][0] == 0) ||
               (group[0][0] == 0 && group[1][0] == 3)) {
      if (group[0][1] == 0 && group[1][1] == 0) {
        DNF += "b'c'd'";
      } else if (group[0][1] == 1 && group[1][1] == 1) {
        DNF += "b'c'd";
      } else if (group[0][1] == 2 && group[1][1] == 2) {
        DNF += "b'cd";
      } else if (group[0][1] == 3 && group[1][1] == 3) {
        DNF += "b'cd'";
      }
    }
  } else if (group.size() == 4) {
    if (is_in_group(group, 0, 0) && is_in_group(group, 0, 1) &&
        is_in_group(group, 1, 0) && is_in_group(group, 1, 1)) {
      DNF += "a'c'";
    } else if (is_in_group(group, 0, 1) && is_in_group(group, 0, 2) &&
               is_in_group(group, 1, 1) && is_in_group(group, 1, 2)) {
      DNF += "a'd";
    } else if (is_in_group(group, 0, 2) && is_in_group(group, 0, 3) &&
               is_in_group(group, 1, 2) && is_in_group(group, 1, 3)) {
      DNF += "a'c";
    } else if (is_in_group(group, 0, 0) && is_in_group(group, 0, 3) &&
               is_in_group(group, 1, 0) && is_in_group(group, 1, 3)) {
      DNF += "a'd'";
    }

    else if (is_in_group(group, 1, 0) && is_in_group(group, 1, 1) &&
             is_in_group(group, 2, 0) && is_in_group(group, 2, 1)) {
      DNF += "bc'";
    } else if (is_in_group(group, 1, 1) && is_in_group(group, 1, 2) &&
               is_in_group(group, 2, 1) && is_in_group(group, 2, 2)) {
      DNF += "bd";
    } else if (is_in_group(group, 1, 2) && is_in_group(group, 1, 3) &&
               is_in_group(group, 2, 2) && is_in_group(group, 2, 3)) {
      DNF += "bc";
    } else if (is_in_group(group, 1, 0) && is_in_group(group, 1, 3) &&
               is_in_group(group, 2, 0) && is_in_group(group, 2, 3)) {
      DNF += "bd'";
    }

    else if (is_in_group(group, 2, 0) && is_in_group(group, 2, 1) &&
             is_in_group(group, 3, 0) && is_in_group(group, 3, 1)) {
      DNF += "ac'";
    } else if (is_in_group(group, 2, 1) && is_in_group(group, 2, 2) &&
               is_in_group(group, 3, 1) && is_in_group(group, 3, 2)) {
      DNF += "ad";
    } else if (is_in_group(group, 2, 2) && is_in_group(group, 2, 3) &&
               is_in_group(group, 3, 2) && is_in_group(group, 3, 3)) {
      DNF += "ac";
    } else if (is_in_group(group, 2, 0) && is_in_group(group, 2, 3) &&
               is_in_group(group, 3, 0) && is_in_group(group, 3, 3)) {
      DNF += "ad'";
    }

    else if (is_in_group(group, 0, 0) && is_in_group(group, 0, 1) &&
             is_in_group(group, 3, 0) && is_in_group(group, 3, 1)) {
      DNF += "b'c'";
    } else if (is_in_group(group, 0, 1) && is_in_group(group, 0, 2) &&
               is_in_group(group, 3, 1) && is_in_group(group, 3, 2)) {
      DNF += "b'd";
    } else if (is_in_group(group, 0, 2) && is_in_group(group, 0, 3) &&
               is_in_group(group, 3, 2) && is_in_group(group, 3, 3)) {
      DNF += "b'c";
    } else if (is_in_group(group, 0, 0) && is_in_group(group, 0, 3) &&
               is_in_group(group, 3, 0) && is_in_group(group, 3, 3)) {
      DNF += "b'd'";
    }

    else if (group[0][0] == group[1][0] && group[0][0] == group[2][0] &&
             group[0][0] == group[3][0]) {
      if (is_in_group(group, 0, 0) && is_in_group(group, 0, 1) &&
          is_in_group(group, 0, 2) && is_in_group(group, 0, 3)) {
        DNF += "a'b'";
      } else if (is_in_group(group, 1, 0) && is_in_group(group, 1, 1) &&
                 is_in_group(group, 1, 2) && is_in_group(group, 1, 3)) {
        DNF += "a'b";
      } else if (is_in_group(group, 2, 0) && is_in_group(group, 2, 1) &&
                 is_in_group(group, 2, 2) && is_in_group(group, 2, 3)) {
        DNF += "ab";
      } else if (is_in_group(group, 3, 0) && is_in_group(group, 3, 1) &&
                 is_in_group(group, 3, 2) && is_in_group(group, 3, 3)) {
        DNF += "ab'";
      }
    } else if (group[0][1] == group[1][1] && group[0][1] == group[2][1] &&
               group[0][1] == group[3][1]) {
      if (is_in_group(group, 0, 0) && is_in_group(group, 1, 0) &&
          is_in_group(group, 2, 0) && is_in_group(group, 3, 0)) {
        DNF += "c'd'";
      } else if (is_in_group(group, 0, 1) && is_in_group(group, 1, 1) &&
                 is_in_group(group, 2, 1) && is_in_group(group, 3, 1)) {
        DNF += "c'd";
      } else if (is_in_group(group, 0, 2) && is_in_group(group, 1, 2) &&
                 is_in_group(group, 2, 2) && is_in_group(group, 3, 2)) {
        DNF += "cd";
      } else if (is_in_group(group, 0, 3) && is_in_group(group, 1, 3) &&
                 is_in_group(group, 2, 3) && is_in_group(group, 3, 3)) {
        DNF += "cd'";
      }
    }
  } else if (group.size() == 8) {
    if (is_in_group(group, 0, 0) && is_in_group(group, 0, 1) &&
        is_in_group(group, 0, 2) && is_in_group(group, 0, 3) &&
        is_in_group(group, 1, 0) && is_in_group(group, 1, 1) &&
        is_in_group(group, 1, 2) && is_in_group(group, 1, 3)) {
      DNF += "a'";
    } else if (is_in_group(group, 1, 0) && is_in_group(group, 1, 1) &&
               is_in_group(group, 1, 2) && is_in_group(group, 1, 3) &&
               is_in_group(group, 2, 0) && is_in_group(group, 2, 1) &&
               is_in_group(group, 2, 2) && is_in_group(group, 2, 3)) {
      DNF += "b";
    } else if (is_in_group(group, 2, 0) && is_in_group(group, 2, 1) &&
               is_in_group(group, 2, 2) && is_in_group(group, 2, 3) &&
               is_in_group(group, 3, 0) && is_in_group(group, 3, 1) &&
               is_in_group(group, 3, 2) && is_in_group(group, 3, 3)) {
      DNF += "a";
    } else if (is_in_group(group, 0, 0) && is_in_group(group, 0, 1) &&
               is_in_group(group, 0, 2) && is_in_group(group, 0, 3) &&
               is_in_group(group, 1, 0) && is_in_group(group, 1, 1) &&
               is_in_group(group, 1, 2) && is_in_group(group, 1, 3)) {
      DNF += "b'";
    } else if (is_in_group(group, 0, 0) && is_in_group(group, 1, 0) &&
               is_in_group(group, 2, 0) && is_in_group(group, 3, 0) &&
               is_in_group(group, 0, 1) && is_in_group(group, 1, 1) &&
               is_in_group(group, 2, 1) && is_in_group(group, 3, 1)) {
      DNF += "c'";
    } else if (is_in_group(group, 0, 1) && is_in_group(group, 1, 1) &&
               is_in_group(group, 2, 1) && is_in_group(group, 3, 1) &&
               is_in_group(group, 0, 2) && is_in_group(group, 1, 2) &&
               is_in_group(group, 2, 2) && is_in_group(group, 3, 2)) {
      DNF += "d";
    } else if (is_in_group(group, 0, 2) && is_in_group(group, 1, 2) &&
               is_in_group(group, 2, 2) && is_in_group(group, 3, 2) &&
               is_in_group(group, 0, 3) && is_in_group(group, 1, 3) &&
               is_in_group(group, 2, 3) && is_in_group(group, 3, 3)) {
      DNF += "c";
    } else if (is_in_group(group, 0, 3) && is_in_group(group, 1, 3) &&
               is_in_group(group, 2, 3) && is_in_group(group, 3, 3) &&
               is_in_group(group, 0, 0) && is_in_group(group, 1, 0) &&
               is_in_group(group, 2, 0) && is_in_group(group, 3, 0)) {
      DNF += "d'";
    }
  } else if (group.size() == 16) {
    DNF += "1";
  }
}

void KarnaughMap::to_DNF() {
  grouping();
  for (const vector<vector<int>>& group : groups) {
    group_to_DNF(group);
    if (group != groups[groups.size() - 1]) {
      DNF += " V ";
    }
  }
  if (DNF.empty()) DNF += "0";
}

void KarnaughMap::print_vector() {
  for (const vector<vector<int>>& group : (*this).groups) {
    cout << "Группа:" << endl;
    for (const vector<int>& vec : group) {
      for (int value : vec) {
        cout << value << " ";
      }
      cout << endl;
    }
  }
}

#ifndef RUN_TESTS
int main() {
  while (true) {
    string func = "";
    char response = 'y';
    cout << "Введите функцию в формате '1111111100000000':\n";
    cin >> func;
    if (!validation(func)) {
      cout << "Некорректный ввод\n";
    } else {
      KarnaughMap K_map(func);
      cout << "Таблица истинности: \n";
      K_map.printTruthTable();
      cout << "Карта Карно:\n";
      K_map.printKarnaughMap();
      K_map.to_DNF();
      K_map.print_vector();
      cout << "ДНФ: " << K_map.DNF << endl << endl;
      cout << "Продолжить? (y/n)\n";
      cin >> response;
      if (response == 'n' || response == 'N') break;
    }
  }
  return 0;
}
#endif