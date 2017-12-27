#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
#include <map>

int main() {
  std::ifstream infile("day8input");
  std::string line;
  std::map<std::string, int> registers;
  int max2 = 0;
  while(std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string register_;
    std::string operation;
    int val;
    std::string if_;
    std::string comparison_register;
    std::string comparison_operation;
    int comparison_val;
    iss >> register_ >> operation >> val >> if_ >> comparison_register >> comparison_operation >> comparison_val;
    if(operation == "dec") {
      val *= -1;
    } else if(operation == "inc") {
    } else {
      std::cerr << "UNKNOWN OPERATION: " << operation << std::endl;
      return -1;
    }



    bool proceed;

    if(comparison_operation == "<") {
      proceed = registers[comparison_register] < comparison_val;
    } else if(comparison_operation == "<=") {
      proceed = registers[comparison_register] <= comparison_val;
    } else if(comparison_operation == "==") {
      proceed = registers[comparison_register] == comparison_val;
    }  else if(comparison_operation == "!=") {
      proceed = registers[comparison_register] != comparison_val;
    }else if(comparison_operation == ">=") {
      proceed = registers[comparison_register] >= comparison_val;
    } else if(comparison_operation == ">") {
      proceed = registers[comparison_register] > comparison_val;
    } else {
      std::cerr << "UNKNOWN COMPARISON OPERATION: " << comparison_operation << std::endl;
      std::cerr << line << std::endl;
      return -1;
    }
    if(proceed) {
      registers[register_] += val;
    }
    max2 = std::max(max2,registers[register_]);
  }

  int max = registers.begin()->second;
  for(auto r : registers) {
    max = std::max(max,r.second);
  }
  std::cout << max << " " << max2 <<std::endl;

}
