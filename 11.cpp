#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <stack>
#include <fstream>
#include <set>
#include <map>

int main() {
  std::ifstream infile("day11input");
  char c;
  int n = 0;
  int s = 0;
  int nw = 0;
  int ne = 0;
  int sw = 0;
  int se = 0;

  int max_away = 0;

  while(infile >> c) {
    std::string dir;
    while(true) {
      dir += c;
      if(!(infile >> c)
         ||c==',') {
        break;
      }
    }
    //std::cout << "dir: " << std::endl;
    if(dir == "n") n++;
    if(dir == "s") s++;
    if(dir == "nw") nw++;
    if(dir == "ne") ne++;
    if(dir == "sw") sw++;
    if(dir == "se") se++;


    max_away = std::max(std::abs(n-s) + std::abs(nw-se) +std::abs(ne-sw), max_away);


    if(n > s) {
      n -= s;
      s -= s;
    } else {
      s -= n;
      n -= n;
    }

    if(nw > se) {
      nw -= se;
      se -= se;
    } else {
      se -= nw;
      nw -= nw;
    }

    if(ne > sw) {
      ne -= sw;
      sw -= sw;
    } else {
      sw -= ne;
      ne -= ne;
    }


    for(int i = 0; i < 1; ++i) {
      int max;

      max = std::min(sw, n);
      sw -= max;
      nw += max;
      n -= max;

      max = std::min(se, n);
      se -= max;
      ne += max;
      n -= max;

      max = std::min(nw, s);
      nw -= max;
      sw += max;
      s -= max;

      max = std::min(ne, s);
      ne -= max;
      se += max;
      s -= max;

      max = std::min(se, sw);
      se -= max;
      sw -= max;
      s += max;


      max = std::min(ne, nw);
      ne -= max;
      nw -= max;
      n += max;
    }



  }

  // ne + s = se
  // nw + s = sw
  int max;








  std::cout << n << " " << s << " " << nw << " " << se << " " << ne << " " << sw << std::endl;
  std::cout << std::abs(n-s) + std::abs(nw-se) +std::abs(ne-sw) << std::endl;
  std::cout << max_away << std::endl;
}
