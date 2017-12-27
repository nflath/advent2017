#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <stack>
#include <fstream>
#include <set>
#include <map>

class Graph {
public:
  int id;
  std::vector<int> neighbors;
  Graph(int id, std::vector<int>& neighbors) : id(id),neighbors(neighbors) {}

};

int main() {
  std::ifstream infile("day12input");
  std::string line;
  std::map<int, Graph*> m;

  while(std::getline(infile, line)) {
    std::istringstream iss(line);

    int id;
    std::vector<int> neighbors;
    iss >> id;

    std::string tmp;
    iss >> tmp;

    int neighbor;
    while(iss >> neighbor) {
      neighbors.push_back(neighbor);
      char c;
      iss >> c;
    }

    m[id] = new Graph(id, neighbors);
  }

  std::set<int> reachable;

  std::stack<int> ids;
  ids.push(0);

  while(ids.size()) {
    int id = ids.top();
    ids.pop();

    if(reachable.find(id) == reachable.end()) {
      reachable.insert(id);
      for(auto v : m[id]->neighbors) {
        ids.push(v);
      }
    }
  }
  std::cout << reachable.size() << std::endl;

  int groups = 1;

  std::cout << m.size() << std::endl;
  for(int i = 1; i < m.size(); ++i) {
    if(reachable.find(i) == reachable.end()) {
      std::stack<int> ids;
      ids.push(i);

      while(ids.size()) {
        int id = ids.top();
        ids.pop();

        if(reachable.find(id) == reachable.end()) {
          reachable.insert(id);
          for(auto v : m[id]->neighbors) {
            ids.push(v);
          }
        }
      }

      groups++;
    }
  }

  std::cout << groups << std::endl;

}
