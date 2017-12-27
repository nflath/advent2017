#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

int main() {
  {
  std::vector<int> instructions;
  int result = 0;
  std::ifstream infile("day5input");
  int jump;
  while(infile >> jump) {
    instructions.push_back(jump);
  }
  int instruction = 0;
  while(instruction >= 0 && instruction < instructions.size()) {
    instructions[instruction]++;
    instruction += instructions[instruction] - 1;
    result++;
  }
  std::cout << result << std::endl;
  }
  {
  std::vector<int> instructions;
  int result = 0;
  std::ifstream infile("day5input");
  int jump;
  while(infile >> jump) {
    instructions.push_back(jump);
  }
  int instruction = 0;
  while(instruction >= 0 && instruction < instructions.size()) {
    int new_instruction = instruction + instructions[instruction];
    if(instructions[instruction]>=3) {
      instructions[instruction]--;
    } else {
      instructions[instruction]++;
    }
    instruction = new_instruction;
    result++;
  }
  std::cout << result << std::endl;
  }
}
