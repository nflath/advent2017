#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

class Tree {
public:
  std::string name;
  std::vector<Tree*> children;
  Tree* parent;
  int weight;

  Tree(std::string name, int weight): name(name), weight(weight){}
  Tree(std::string name): name(name){}
};

int is_balanced(Tree* tree) {
  int total_weight = tree->weight;
  if(tree->children.size() == 0) {
    return tree->weight;
  }

  std::vector<int> weights;
  int total_child_weight = 0;

  for(Tree* child : tree->children) {
    int child_weight = is_balanced(child);
    if(child_weight == -1) {
      return -1;
    }
    total_child_weight += child_weight;

    if(std::find(weights.begin(), weights.end(), child_weight) == weights.end() &&
       weights.size()) {

      std::cout << "Not balanced: " << tree->name << std::endl;

      for(int i = 0; i < tree->children.size(); i++) {
        std::cout << tree->children[i]->name << " " << is_balanced(tree->children[i]) << " " << tree->children[i]->weight << std::endl;
      }
      return -1;
    }
    total_weight += child_weight;
    weights.push_back(child_weight);
  }

  return total_weight;
}

int main() {
  {
    std::ifstream infile("day7input");
    std::string line;
    std::map<std::string, Tree*> map;
    while(std::getline(infile, line)) {
      std::string program_name;
      std::string program_weight;
      std::string arrow;

      std::istringstream iss(line);
      iss >> program_name;
      iss >> program_weight;
      int weight = atoi(program_weight.substr(1,program_weight.size()-2).c_str());

      Tree* node;
      if(map.find(program_name) != map.end()) {
        node = map[program_name];
        node->weight = weight;
      } else {
        node = new Tree(program_name, weight);
      }
      map[program_name] = node;


      if(iss >> arrow) {
        std::string word;
        while(iss >> word) {
          if(word[word.size()-1] == ',') {
            word = word.substr(0,word.size()-1);
          }
          Tree* child;
          if(map.find(word) != map.end()) {
            child = map[word];
          } else {
            child = new Tree(word);
          }
          map[word] = child;

          node->children.push_back(child);
          child->parent = node;
        }
      }
    }

    Tree* tree = map.begin()->second;
    while(tree->parent) {
      tree = tree->parent;
    }
    std::cout << tree->name << std::endl;


    is_balanced(tree);
  }

}
