#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <set>

int findStrongest(int start, std::map<int, std::set<int>> components, int z = 0) {
  int longest = 0;
  std::set<int> startset = components[start];

  for(int i : startset) {
    components[start].erase(i);
    components[i].erase(start);
    // for(int j = 0; j < z; j++) {
    //   std::cout << "  ";
    // }
    // std::cout << i << std::endl;

    // 0-1
    // 1-10
    // 10-9

    // 0 + 1
    // 1 + 10
    // 10 + 9

    longest = std::max(longest, i + start + findStrongest(i, components, z + 1));
    components[start].insert(i);
    components[i].insert(start);
  }
  return longest;
}

std::pair<int, int> findStrongestLongest(int start, std::map<int, std::set<int>> components, int z = 0) {
  std::pair<int, int> longest(0, 0);
  std::set<int> startset = components[start];

  for(int i : startset) {
    components[start].erase(i);
    components[i].erase(start);
    // for(int j = 0; j < z; j++) {
    //   std::cout << "  ";
    // }
    // std::cout << i << std::endl;

    // 0-1
    // 1-10
    // 10-9

    // 0 + 1
    // 1 + 10
    // 10 + 9

    auto result = findStrongestLongest(i, components, z+1);
    if(result.first > longest.first ||
       (result.first == longest.first &&
        (result.second+i+z) > longest.second)) {
      longest = std::pair<int, int>(result.first, i+start+result.second);
    }

    //longest = std::max(longest, i + start + findStrongest(i, components, z + 1));
    components[start].insert(i);
    components[i].insert(start);
  }
   return longest;
}

int main() {
  std::ifstream infile("day24input");
  std::map<int, std::set<int>> components;
  std::string line;
  while(std::getline(infile, line)) {
    char c;
    int begin;
    int end;
    std::stringstream ss(line);
    ss >> begin >> c >> end;
    components[begin].insert(end);
    components[end].insert(begin);
  }
  // std::cout << findStrongest(0, components) << std::endl;

  // for(auto i : components) {
  //   std::cout << i.first << " -> ";
  //   for (int j : i.second) {
  //     std::cout << j << " ";
  //   }
  //   std::cout << std::endl;
  // }


  auto r = findStrongestLongest(0, components);
  std::cout << r.first << " " << r.second << std::endl;


}
