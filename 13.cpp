#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <stack>
#include <fstream>
#include <set>
#include <map>

class Laser {
public:
  int position;
  int range;
  int depth;

  Laser(int depth, int range): range(range), depth(depth), position(0), direction(1) {}

  int step() {
    if(direction == 1 && position == range - 1) {
      direction = -1;
    } else if(direction == -1 && position == 0) {
      direction = 1;
    }
    position += direction;
    return position;
  }

  int direction;
};

int main() {

  std::ifstream infile("day13input");
  std::vector<Laser*> lasers;
  int max_depth = 0;

  std::string line;
  while(std::getline(infile, line)) {
    std::istringstream iss(line);
    int depth;
    int range;
    char c;

    iss >> depth;
    iss >> c;
    iss >> range;
    max_depth = std::max(max_depth, depth);
    lasers.push_back(new Laser(depth, range));
  }


  int my_depth = 0;

  int severity = 0;
  for(int my_depth = 0; my_depth <= max_depth; my_depth++) {
    for(auto laser : lasers) {
      if(laser->position == 0 && laser->depth == my_depth) {
        severity += laser->depth * laser->range;
      }
      laser->step();
    }
  }

  std::cout << severity << std::endl;

  int delay = 0;
  while(severity != 0) {
    delay++;
    severity = 0;
    for(auto laser : lasers) {
      if(!((delay + laser->depth)%(laser->range*2-2))) {
        severity = 1;
        break;
      }
    }
  }
    // for(auto laser : lasers) {

    //   laser->direction = 1;
    //   for(int i = 0; i < delay; i++) {
    //     laser->step();
    //   }
    // }

    // for(int my_depth = 0; my_depth <= max_depth; my_depth++) {
    //   for(auto laser : lasers) {
    //     if(laser->position == 0 && laser->depth == my_depth) {
    //       severity += 1;
    //       std::cout << "Caught at position: " << my_depth << " with delay: " << delay << std::endl;
    //       break;
    //     }
    //     laser->step();
    //   }
    //   if(severity) {
    //     break;
    //   }
    // }
  // }

  // (delay+depth) cannot be divisible by (range * 2 - 2)

  std::cout << delay << std::endl;


}
