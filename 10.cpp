#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>

void reverse(std::vector<int>& lst, int start, int length) {
  for(int i = 0; i < length/2; ++i) {
    int pos1 = (i+start)%lst.size();
    int pos2 = (start+length-i-1)%lst.size();
    int tmp = lst[pos1];
    lst[pos1] = lst[pos2];
    lst[pos2] = tmp;
  }
}

std::string input = "192,69,168,160,78,1,166,28,0,83,198,2,254,255,41,12";
//192,69,168,160,78,1,166,28,0,83,198,2,254,255,41,12
//std::string input = "1,2,3";
//std::string input = "";//AoC 2017";
int main() {
  {
    std::vector<int> list(256);
    for(int i = 0 ; i < list.size(); ++i) {
      list[i] = i;
    }

    int position = 0;
    int skip = 0;

    std::stringstream in(input);
    for(int j = 0 ; j < list.size(); ++j) {
      if(j == position) {
        std::cout << "[" << list[j] << "] ";
      } else {
        std::cout << list[j] << " ";
      }
    }
    std::cout << std::endl;
    int length = 0;
    while(in >> length) {
      char c;
      in >> c;
      reverse(list, position, length);

      position += skip + length;
      position %= list.size();
      for(int j = 0 ; j < list.size(); ++j) {
        if(j == position) {
          std::cout << "[" << list[j] << "] ";
        } else {
          std::cout << list[j] << " ";
        }
      }
      std::cout << std::endl;
      skip++;
    }

    std::cout << list[0] * list[1] << std::endl;
  }

  {
    std::vector<int> lst(256);
    for(int i = 0 ; i < lst.size(); ++i) {
      lst[i] = i;
    }

    int position = 0;
    int skip = 0;

    std::vector<int> lengths;
    char length;
    std::stringstream in(input);
    while(in >> length) {
      lengths.push_back(length);
    }
    lengths.push_back(17);
    lengths.push_back(31);
    lengths.push_back(73);
    lengths.push_back(47);
    lengths.push_back(23);

    for(int i = 0; i < 64; ++i) {
      char length;
      for(auto length : lengths) {
        reverse(lst, position, length);

        position += skip + length;
        position %= lst.size();
        skip++;
      }
    }

    std::vector<int> dense(16);
    for(int i = 0; i < lst.size()/16; i++) {
      dense[i] = lst[i*16];
      for(int j = 1; j < 16; j++) {
        dense[i] ^= lst[i*16+j];
      }
      std::cout << std::hex << std::setfill('0') << std::setw(2) << dense[i];
    }
    std::cout << std::endl;
  }



}
