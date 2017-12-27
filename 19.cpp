#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

class Direction {
public:
  int x;
  int y;
  Direction(int x, int y): x(x), y(y) {}
};

class Position {
public:
  int x;
  int y;
  Position(int x, int y): x(x), y(y) {}
  Position operator+(const Direction& d) {
    return Position(x + d.x,
                    y + d.y);
  }
  bool operator!=(const Position& p) {
    return x != p.x || y != p.y;
  }
};

class Map {
public:
  char operator[](const Position& p) {
    return map[p.x][p.y];
  }
  std::vector<std::string> map;
  bool valid(const Position& p) {
    return p.x >= 0 && p.y >= 0 && p.x < map.size() && p.y < map[0].size();
  }
};


int main() {

  Map map;

  std::ifstream infile("day19input");
  std::string line;
  while(std::getline(infile, line)) {
    map.map.push_back(line);
  }
  Position pos(0,0);
  Direction dir(1,0);

  for(int i = 0; i < map.map[0].size(); ++i) {
    if(map[Position(0,i)] == '|') pos = Position(0,i);
  }

  int steps = 1;
  Position lastpos = pos;
  while(map.valid(pos)) {
    if(map.valid(pos+dir) && map[pos+dir] != ' ') {
      //std::cout << "Same dir:" << pos.x << " " << pos.y << " " << dir.x << " " << dir.y << " " << (pos+dir).x << " " << (pos+dir).y << std::endl;
      if(map[pos+dir]>= 'A' && map[pos+dir] <= 'Z') {
        std::cout << map[pos+dir];
      }
      lastpos = pos;
      //std::cout << pos.x << " " << pos.y << std::endl;
      pos = pos + dir;
      steps++;
      //std::cout << pos.x << " " << pos.y << std::endl;
    } else {
      //  std::cout << "Different dir: " << pos.x << " " << pos.y << std::endl;
      bool found = false;
      for(Direction d : {Direction(1,0), Direction(-1,0), Direction(0,1), Direction(0,-1)}) {
        Position p = pos + d;
        if(map.valid(pos+d) && map[pos+d] != ' ' && ((pos+d) != lastpos)) {

          dir = d;
          //std::cout << "Found new direction: " << dir.x << " " << dir.y << std::endl;
          found = true;
          break;
        }
      }
      if(!found) {
        break;
      }
    }
  }

  std::cout << std::endl<<steps<<std::endl;

}
