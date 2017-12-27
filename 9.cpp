#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <stack>
#include <fstream>
#include <set>
#include <map>

std::pair<std::string, int> remove_garbage(std::string const& line) {
  std::string newline;
  bool in_garbage = false;
  int removed = 0;
  for(int i = 0; i < line.size(); ++i) {
    if(!in_garbage && line[i] != '<') {
      newline += line[i];
    } else if(!in_garbage && line[i] == '<') {
      in_garbage = true;
    } else if(in_garbage) {
      if(line[i] == '!') {
        ++i;
      } else if(line[i] == '>') {
        in_garbage = false;

      } else {
      removed++;
      }
    }
  }
  return std::pair<std::string, int>(newline, removed);
}

int score(std::string const& clean) {
  int score = 0;
  std::stack<char> stack;
  for(char c : clean) {
    if(c == '{') {
      stack.push('{');
    } else if(c == '}') {
      score += stack.size();
      stack.pop();
    } else if(c == ',') {
    } else {
      std::cerr << "ERROR: UNKNWON CHAR: " << c << " in " << clean;
    }
  }
  return score;
}

int main() {
  std::ifstream infile("day9input");
  std::string line;
  std::map<std::string, int> registers;
  int max2 = 0;
  int total_score = 0;
  int total_removed = 0;
  while(std::getline(infile, line)) {
    std::pair<std::string, int> cleaned = remove_garbage(line);
    total_score += score(cleaned.first);
    total_removed += cleaned.second;
  }
  std::cout << total_score << std::endl;
 std::cout << total_removed << std::endl;
}
