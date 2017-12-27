#include <map>
#include <iostream>

int main() {
  std::map<int, short> t;
  char s = 'A';
  int c;

  for(int i = 0; i < 12481997; i++) {

  switch(s) {
  case 'A':
    if(t[c] == 0) {
      t[c] = 1;
      c++;
      s = 'B';
    } else if(t[c] == 1) {
      t[c] = 0;
      c--;
      s = 'C';
    }
    break;
  case 'B':
    if(t[c] == 0) {
      t[c] = 1;
      c--;
      s = 'A';
    } else if(t[c] == 1) {
      t[c] = 1;
      c++;
      s = 'D';
    }
    break;
case 'C':
    if(t[c] == 0) {
      t[c] = 0;
      c--;
      s = 'B';
    } else if(t[c] == 1) {
      t[c] = 0;
      c--;
      s = 'E';
    }
    break;
case 'D':
    if(t[c] == 0) {
      t[c] = 1;
      c++;
      s = 'A';
    } else if(t[c] == 1) {
      t[c] = 0;
      c++;
      s = 'B';
    }
    break;
  case 'E':
    if(t[c] == 0) {
      t[c] = 1;
      c--;
      s = 'F';
    } else if(t[c] == 1) {
      t[c] = 1;
      c--;
      s = 'C';
    }
    break;
case 'F':
    if(t[c] == 0) {
t[c] = 1;
      c++;
      s = 'D';
    } else if(t[c] == 1) {
      t[c] = 1;
      c++;
      s = 'A';
    }
    break;


  }
  }
  int count = 0;
  for(auto i : t) {
    if(i.second == 1) {
      count++;
    }
  }
  std::cout << count << std::endl;

}
