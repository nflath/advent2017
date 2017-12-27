#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>

class InfiniteGrid {
public:
  std::vector<std::vector<bool>> grid;

  int min_row;
  int max_row;
  int min_col;

  int max_col;

  InfiniteGrid(std::vector<std::vector<bool>> grid):
    grid(grid),
    min_row(0),
    max_row(grid.size()),
    min_col(0),
    max_col(grid[0].size()) {
  }

  bool val(int row, int col) {
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }
    return grid[row - min_row][col - min_col];
  }

  void resize() {
    int rows = max_row - min_row;
    int cols = max_col - min_col;
    std::vector<std::vector<bool>> new_grid;
    for(int i = 0; i < rows / 2; ++i) {
      new_grid.push_back(std::vector<bool>(cols * 2));
    }
    for(int i = 0; i < rows; ++i) {
      std::vector<bool> new_row(cols * 2);
      for(int j = cols / 2; j < cols * 1.5; ++j) {
        new_row[j] = grid[i][j-cols/2];
      }
      new_grid.push_back(new_row);
    }
    for(int i = 0; i < rows / 2; ++i) {
      new_grid.push_back(std::vector<bool>(cols * 2));
    }
    grid = new_grid;
    min_row = min_row - rows/2;
    min_col = min_col - cols/2;
    max_row = max_row + rows/2;
    max_col = max_col + cols/2;
  }

  void set(int row, int col, bool value) {
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }
    grid[row-min_row][col-min_col] = value;
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }

  }

};

class InfiniteCharGrid {
public:
  std::vector<std::vector<char>> grid;

  int min_row;
  int max_row;
  int min_col;

  int max_col;

  InfiniteCharGrid(std::vector<std::vector<char>> grid):
    grid(grid),
    min_row(0),
    max_row(grid.size()),
    min_col(0),
    max_col(grid[0].size()) {
  }

  char val(int row, int col) {
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }
    return grid[row - min_row][col - min_col];
  }

  void resize() {
    int rows = max_row - min_row;
    int cols = max_col - min_col;
    int new_rows = rows/2;
    int new_cols = cols/2;
    std::vector<std::vector<char>> new_grid;

    for(int i = 0; i < new_rows; ++i) {
      new_grid.push_back(std::vector<char>(cols * 2, '.'));
    }

    for(int i = 0; i < rows; ++i) {
      std::vector<char> new_row(cols + new_cols * 2+1,'.');
      for(int j = 0; j < cols; ++j) {
        new_row[j+new_cols] = grid[i][j];
      }
      new_grid.push_back(new_row);
    }
    for(int i = 0; i < new_rows; ++i) {
      new_grid.push_back(std::vector<char>(cols * 2,'.'));
    }
    grid = new_grid;
    min_row = min_row - rows/2;
    min_col = min_col - cols/2;
    max_row = max_row + rows/2;
    max_col = max_col + cols/2;
  }

  void set(int row, int col, char value) {
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }
    grid[row-min_row][col-min_col] = value;
    if(row < min_row) {
      resize();
    } else if(row >= max_row) {
      resize();
    } else if(col < min_col) {
      resize();
    } else if(col >= max_col) {
      resize();
    }

  }

};

class Virus {
 public:
  int row;
  int col;
  InfiniteGrid* g;
  std::pair<int, int> direction;
  int infections = 0;

  Virus(InfiniteGrid* g): row(g->max_row/2), col(g->max_col/2), g(g), direction(-1, 0) {}

  void print() {
    for(int x = 0;  x < g->grid.size(); ++x) {

     for(int y = 0;  y < g->grid[0].size(); ++y) {
       if((row - g->min_row) == x &&
          (col - g->min_col) == y) {
         std::cout << "[" << (g->grid[x][y] ? "#" : ".") << "]";
       } else {
         std::cout << " " << (g->grid[x][y] ? "#" : ".") << " ";
       }
     }
     std::cout << std::endl;
    }
  }

  void turnRight() {
    if(direction.first == -1) {
      direction = std::pair<int, int>(0, 1);
    } else if(direction.first == 1) {
      direction = std::pair<int, int>(0, -1);
    } else if(direction.second == -1) {
      direction = std::pair<int, int>(-1, 0);
    } else if(direction.second == 1) {
      direction = std::pair<int, int>(1, 0);
    }
  }

void turnLeft() {
    if(direction.first == 1) {
      direction = std::pair<int, int>(0, 1);
    } else if(direction.first == -1) {
      direction = std::pair<int, int>(0, -1);
    } else if(direction.second == 1) {
      direction = std::pair<int, int>(-1, 0);
    } else if(direction.second == -1) {
      direction = std::pair<int, int>(1, 0);
    }
  }

  void advance() {
    if(g->val(row, col)) {
      turnRight();
    } else {
      turnLeft();
    }
    g->set(row, col, !g->val(row, col));
    if(g->val(row, col)) {
      infections++;
    }
    row += direction.first;
    col += direction.second;
    g->val(row, col);
  }

};

class Virus2 {
 public:
  int row;
  int col;
  InfiniteCharGrid* g;
  std::pair<int, int> direction;
  int infections = 0;

  Virus2(InfiniteCharGrid* g): row(g->max_row/2), col(g->max_col/2), g(g), direction(-1, 0) {}

  void print() {
    for(int x = 0;  x < g->grid.size(); ++x) {

     for(int y = 0;  y < g->grid[0].size(); ++y) {
       if((row - g->min_row) == x &&
          (col - g->min_col) == y) {
         std::cout << "[" << g->grid[x][y] << "]";
       } else {
         std::cout << " " << g->grid[x][y] << " ";
       }
     }
     std::cout << std::endl;
    }
  }

  void turnRight() {
    if(direction.first == -1) {
      direction = std::pair<int, int>(0, 1);
    } else if(direction.first == 1) {
      direction = std::pair<int, int>(0, -1);
    } else if(direction.second == -1) {
      direction = std::pair<int, int>(-1, 0);
    } else if(direction.second == 1) {
      direction = std::pair<int, int>(1, 0);
    }
  }

void turnLeft() {
    if(direction.first == 1) {
      direction = std::pair<int, int>(0, 1);
    } else if(direction.first == -1) {
      direction = std::pair<int, int>(0, -1);
    } else if(direction.second == 1) {
      direction = std::pair<int, int>(-1, 0);
    } else if(direction.second == -1) {
      direction = std::pair<int, int>(1, 0);
    }
  }

  void advance() {

    if(g->val(row, col) == '.') {
      turnLeft();
      g->set(row, col, 'W');
    } else if(g->val(row, col) == 'W'){
      g->set(row, col, '#');
    } else if(g->val(row, col) == '#'){
      turnRight();
      g->set(row, col, 'F');
    } else if(g->val(row, col) == 'F'){
      direction = std::pair<int, int>(-direction.first, -direction.second);
      g->set(row, col, '.');
    }


    if(g->val(row, col) == '#') {
      infections++;
    }
    row += direction.first;
    col += direction.second;
    g->val(row, col);
  }

};

int main() {
  // {
  // std::vector<std::vector<bool>> g;
  // std::string line;
  // std::ifstream infile("day22input");
  // while(std::getline(infile, line)) {
  //   std::stringstream ss(line);
  //   char c;
  //   std::vector<bool> row;
  //   while(ss >> c) {
  //     row.push_back(c == '#');
  //   }
  //   g.push_back(row);
  // }

  // InfiniteGrid grid(g);
  // Virus v(&grid);
  // v.print();
  // std::cout << std::endl;
  // for(int i = 0; i < 10000; ++i) {
  //   v.advance();
  //   //v.print();
  //   //std::cout << std::endl;
  // }
  // std::cout << v.infections << std::endl;
  // }

  {
    std::vector<std::vector<char>> g;
    std::string line;
    std::ifstream infile("day22input");
    while(std::getline(infile, line)) {
      std::stringstream ss(line);
      std::cout << "line: " << line << std::endl;
      char c;
      std::vector<char> row;
      while(ss >> c) {

        row.push_back(c);
      }
      g.push_back(row);
    }

    InfiniteCharGrid grid(g);
    Virus2 v(&grid);


    // for(int i = 0; i < 10; ++i) {
    //   v.advance();
    //   v.print();
    //   std::cout << std::endl;
    // }
    // return 0;

    for(int i = 0; i < 10000000; ++i) {
      v.advance();
      //v.print();
      //std::cout << std::endl;
    }
    std::cout << v.infections << std::endl;
  }
}
