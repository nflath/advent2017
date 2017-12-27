#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <set>

class List {
public:
  List* next;
  char name;
  List(char name): name(name) {}
};

class Operation {
public:
  char op;
  int arg1;
  int arg2;
  Operation(char op, int arg1, int arg2):op(op),arg1(arg1),arg2(arg2) {}
};

int main() {
  std::map<char, int> map;
  std::vector<char> v;
  int listlen = 16;
  for(int i = 0; i < 16; i++) {
    v.push_back('a' + i);
    map['a'+i] = i;
  }
  std::vector<Operation*> ops;

  std::ifstream infile("day16input");
  char comma;
  char op;

  int total_spin_length;

  while(infile >> op) {
    if(op == 's') {
      int len;
      infile >> len;
      ops.push_back(new Operation('s',len,0));
      total_spin_length += len;
    } else if(op == 'x') {
      int A, B;
      char slash;
      infile >> A >> comma >> B;
      ops.push_back(new Operation('x',A,B));
    } else if(op == 'p') {
      char A, B;
      char slash;
      infile >> A >> comma >> B;
      ops.push_back(new Operation('p',A,B));
    }
    char comma;
    infile >> comma;
  }

  //int num_dances = 1;
  //ops.push_back(new Operation('s', total_spin_length % listlen, 0));

  int opcount = 0;
  int cycle_length = 0;
  int num_dances = 1000000000;
  for(int i = 0; i < num_dances; i++) {
    //if(!(i%1000))std::cout << i << std::endl;

    for(int j = 0; j < ops.size(); ++j) {
      Operation* op = ops[j];
      ++opcount;
      if(op->op == 's') {
        std::vector<char> v2;

        int i = listlen - op->arg1;
        for(; i < 16; ++i) {
          v2.push_back(v[i]);
        }

        for(int i = 0; i < listlen - op->arg1;++i) {
          v2.push_back(v[i]);
        }
        v = v2;

        for(int i = 0; i < listlen; i++) {
          map[v[i]] = i;
        }

      } else if(op->op == 'x') {
        char tmp = v[op->arg1];
        v[op->arg1] = v[op->arg2];
        v[op->arg2] = tmp;
        map[char(v[op->arg1])] = op->arg1;
        map[char(v[op->arg2])] = op->arg2;
    } else if(op->op == 'p') {

        // std::cout << "p " << char(op->arg1) << "/" << char(op->arg2) << std::endl;
        // std::cout << map[(char)op->arg1] << " " << map[(char)op->arg2] << std::endl;

        v[map[(char)op->arg1]] = op->arg2;
        v[map[(char)op->arg2]] = op->arg1;

        //deagpfjklmnohibc
          //        v[6] = 'k';
          //v[110] = 'g'

        int tmp = map[(char)op->arg1];
        map[(char)op->arg1] = map[(char)op->arg2];
        map[(char)op->arg2] = tmp;
      //   std::cout << op->op << " " << op->arg1 << "/" << op->arg2 << " ";
      // for(int i  = 0; i < 16; ++i) {
      //   std::cout << v[i];
      // }
      // std::cout << std::endl;
      // return 0;
    }

      bool same = true;
      for(int j = 0; j < 16; ++j) {
        if(v[j] != 'a'+j) {
          same = false;
          break;
        }
      }
      if(same&&!cycle_length) {
        std::cout << "cycle found at: " << opcount << " " << i << std::endl;
        cycle_length = opcount;
        long long total_ops = num_dances * ops.size();

        long long remainder = total_ops % cycle_length;
        std::cout << "remainder: " << remainder << std::endl;

        i = num_dances - (remainder / ops.size())-1;
        j = ops.size()-(remainder % ops.size());
        std::cout << "Setting i to: " << i << std::endl;
        std::cout << "Setting j to: " << j << std::endl;
      }
    }
      //std::set<char> s;
      //std::cout << op->op << " " << op->arg1 << "/" << op->arg2 << " ";
      for(int i  = 0; i < 16; ++i) {
        std::cout << v[i];
      }
      std::cout << std::endl;
      // for(int i  = 0; i < 16; ++i) {
      //   if(s.count(v[i])) {
      //     std::cout << "exit due to duplicate" << std::endl;
      //     return 0;
      //   }
      //   if(i != map[v[i]] ){
      //     std::cout << "exit due to incorrect map" << std::endl;
      //     for(int j = 0; j < 16; j++) {
      //       std::cout << (char)('a'+j) << ": " <<map['a'+j] << std::endl;
      //     }
      //     return 0;
      //   }

      //   s.insert(v[i]);

      // }

  }




}
