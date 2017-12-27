#include <fstream>
#include <set>
#include <sstream>
#include <iostream>

int main() {
  {
    int result = 0;
    std::ifstream infile("day4input");
    std::string line;
    while(std::getline(infile, line)) {
      std::cout << "line: " << line << std::endl;
      std::set<std::string> s;

      std::istringstream iss(line);
      std::string word;
      bool found = false;
      while(iss >> word) {
        if(s.count(word)== 0) {
          s.insert(word);
        } else {
          std::cout << "Duplicate: " << word<< " " << s.count(word) << std::endl;
          found = true;
          break;
        }
      }
      if(!found) {
        result++;
      }
    }
    std::cout << result << std::endl;

  }
  {
    int result = 0;
    std::ifstream infile("day4input");
    std::string line;
    while(std::getline(infile, line)) {
      std::set<std::string> s;

      std::istringstream iss(line);
      std::string word;
      bool found = false;
      while(iss >> word) {
        std::sort(word.begin(), word.end());
        if(s.count(word)== 0) {
          s.insert(word);
        } else {
          found = true;
          break;
        }
      }
      if(!found) {
        result++;
      }
    }
    std::cout << result << std::endl;
  }
}
