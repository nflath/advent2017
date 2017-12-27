#include <iostream>

class List {
public:
  List* next;
  int val;
  List(int val): val(val) {}
};

int main() {
  int input = 359;
  {
  List* head = new List(0);
  head->next = head;

  //  nextpos = (pos + input) % i

  List* pos = head;
  for(int i = 1; i <= 2017; i++) {

    for(int j = 0; j < input; j++) {
      pos = pos->next;
    }
    List* nn = pos->next;
    pos->next = new List(i);
    pos->next->next=nn;
    pos = pos->next;
  }
  std::cout << pos->next->val << std::endl;
  }

  {
    int pos = 0;
    int last = -1;
    for(int i = 1; i <= 50000000; ++i) {
      pos = ((pos + input) % i) + 1;
      if(pos == 1) {
        last = i;
      }
      if(i < 10) {
        std::cout << "Inserting i ="<< i << " at pos: " << pos << std::endl;
      }
    }
    std::cout << last << std::endl;
  }
}
