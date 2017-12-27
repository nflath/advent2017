#include <vector>
#include <sstream>
#include <stdlib.h>
#include <stack>

#include <algorithm>
#include <string>
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

std::vector<int> knot(std::string input) {
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
      //std::cout << std::hex << std::setfill('0') << std::setw(2) << dense[i];
    }
    return dense;
    //std::cout << std::endl;
  }
}

int main() {
  std::string input = "hfdlxzhv";
  //std::string input = "flqrgnkx";
  int count = 0;

  int map[128][128];

  for(int i = 0; i < 128; i++) {

    std::stringstream ss;
    ss << input << "-" << i;
    std::vector<int> knothash = knot(ss.str());
    for(int k = 0; k < knothash.size(); k++) {
      int a = knothash[k];

      for(int j = 0; j < 8; j++) {
        count += std::bitset<32>(a)[j];
        map[i][k*8+j] = std::bitset<32>(a)[7-j];
      }
      //std::cout << std::bitset<8>(a);

    }
    //    std::cout << std::endl;
  }
  std::cout << count << std::endl;

  int regions = 0;
  int current_region = 2;
  for(int i = 0; i < 128; i++) {
    for(int j = 0; j < 128; j++) {
      //std::cout << i << " " << j << " " << map[i][j]
      if(map[i][j]==1) {

        std::stack<std::pair<int, int>> s;
        s.push(std::pair<int, int>(i,j));

        while(!s.empty()) {
          std::pair<int, int> cur = s.top();
          s.pop();
          if(cur.first < 0 || cur.first >= 128 || cur.second < 0 || cur.second >= 128 || map[cur.first][cur.second]!=1) {
            continue;
          }
          //std::cout << "Setting: " << cur.first << " " << cur.second << " " << current_region << std::endl;
          map[cur.first][cur.second] = current_region;
          s.push(std::pair<int, int>(cur.first+1, cur.second));
          s.push(std::pair<int, int>(cur.first-1, cur.second));
          s.push(std::pair<int, int>(cur.first, cur.second+1));
          s.push(std::pair<int, int>(cur.first, cur.second-1));
        }
        regions++;
        current_region++;
        current_region = current_region % 1000;
        if(!current_region) current_region+=2;
      }
    }
  }

  for(int i = 0; i < 128; i++) {
    for(int j = 0; j < 128; j++) {
      //  std::cout << map[i][j] << '\t';
    }
    //std::cout << std::endl;
  }


  std::cout << regions << std::endl;

}
