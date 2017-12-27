#include <iostream>

int main() {
  //int a = 618;
  //int b = 814;
  {
  int count = 0;

  unsigned long long a = 618;
  unsigned long long b = 814;

  for(int i = 0; i < 40 * 1000 * 1000; i++) {
    a = (a * 16807) % 2147483647;
    b = (b * 48271) % 2147483647;


    if((a & 0xffff) == (b & 0xffff)) {
      count++;

    }
  }
  std::cout << count << std::endl;
  }

{
  int count = 0;

  unsigned long long a = 618;
  unsigned long long b = 814;

  for(int i = 0; i < 5 * 1000 * 1000; i++) {
    //for(int i = 0; i < 5; i++) {

    a = (a * 16807) % 2147483647;
    while( a % 4) {
      a = (a * 16807) % 2147483647;
    }

    b = (b * 48271) % 2147483647;
    while(b % 8) {
      b = (b * 48271) % 2147483647;
    }
    //std::cout << a << " " << b << std::endl;

    if((a & 0xffff) == (b & 0xffff)) {
      count++;
    }
  }
  std::cout << count << std::endl;
  }
}
