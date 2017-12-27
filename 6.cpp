#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <set>
int input_[] = {0,	5,	10,	0,	11,	14,	13,	4,	11,	8,	8,	7,	1,	4,	12,	11};

int main() {

  std::vector<int> cycle_start;
  {
    std::vector<int> input;
    for(int i = 0; i < sizeof(input_) / 4; ++i) {
      input.push_back(input_[i]);
    }
    std::set<std::vector<int> > seen;
    int result = 0;
    seen.insert(input);

    while(true) {
      result++;

      int max_idx = 0;
      for(int i = 1; i < input.size(); ++i) {
        if(input[max_idx] < input[i]) {
          max_idx = i;
        }
      }


      int redistribute = input[max_idx];
      input[max_idx] = 0;
      max_idx = (max_idx + 1) % input.size();
      int increments = 0;
      for(int i = 0; i < redistribute; ++i) {
        input[max_idx] += 1;
        max_idx = (max_idx + 1) % input.size();
        increments++;
      }
      //std::cout << increments << std::endl;
      if(seen.find(input) != seen.end()) {
        std::cout << result << std::endl;
        cycle_start = input;
        break;
      }
      seen.insert(input);
    }

    result = 0;
    while(true) {
      result++;
int max_idx = 0;
      for(int i = 1; i < input.size(); ++i) {
        if(input[max_idx] < input[i]) {
          max_idx = i;
        }
      }


      int redistribute = input[max_idx];
      input[max_idx] = 0;
      max_idx = (max_idx + 1) % input.size();
      int increments = 0;
      for(int i = 0; i < redistribute; ++i) {
        input[max_idx] += 1;
        max_idx = (max_idx + 1) % input.size();
        increments++;
      }
      if(input == cycle_start) {
        std::cout << result << std::endl;
        cycle_start = input;
        break;
      }
      seen.insert(input);
    }
  }
}
