#include <iostream>
#include <vector>
#include <utility>
#include <sstream>
#include <cmath>
#include <stack>
#include <fstream>
#include <set>
#include <map>
#include <queue>

long long val(std::string const& arg, std::vector<long long> const& registers) {
  long long i = 0;
  if(arg.size()==1 && arg[0] >= 'a' && arg[0] <= 'z') {
    return registers[arg[0]-'a'];
  } else {
    return atoi(arg.c_str());
  }
}

class Operation {
public:

  Operation(std::string op, std::string arg1, std::string arg2):
    instruction(op), arg1(arg1), arg2(arg2) {}
  std::string instruction;
  std::string arg1;
  std::string arg2;
};

class Emulator {
public:
  Emulator(long long idx, std::queue<long long>* in, std::queue<long long>* out): idx(idx),registers(26), pc(0), in(in), out(out), sends(0) {}
long long idx;

  std::vector<long long> registers;
  long long pc;
  std::vector<Operation*> operations;

  std::queue<long long>* in;
  std::queue<long long>* out;

  enum State {
    UNKNOWN,
    RUNNING,
    WAITING,
    STOPPED
  };
  State state;
  long long sends;

  long long val(std::string const& arg) {
    long long i = 0;
    if(arg.size()==1 && arg[0] >= 'a' && arg[0] <= 'z') {
      return registers[arg[0]-'a'];
    } else {
      return atoi(arg.c_str());
    }
  }

  void run() {
    state = RUNNING;
    while(true) {
      if(pc >= operations.size() || pc < 0) {
        state = STOPPED;
        std::cout << "STOPPED due to pc: " << pc << ": returning" << std::endl;
        return;
      }
      Operation* op = operations[pc];
      std::cout << idx << "::" << pc << ": " << op->instruction << " " << op->arg1 << " " << op->arg2 << "  ";

      if(op->instruction == "snd") {
        sends++;
        out->push(val(op->arg1));
      } else if(op->instruction == "set") {
        registers[op->arg1[0]-'a'] = val(op->arg2);
        std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "add") {
        registers[op->arg1[0]-'a'] += val(op->arg2);
        std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "mul") {
        registers[op->arg1[0]-'a'] *= val(op->arg2);
        std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "mod") {
        registers[op->arg1[0]-'a'] %= abs(val(op->arg2));
        std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "rcv") {
        if(in->size()==0) {
          state = WAITING;
          std::cout << std::endl;
          return;
        }

        registers[op->arg1[0]-'a'] = in->front();
        std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
        in->pop();
      } else if(op->instruction == "jgz") {
        if(val(op->arg1) > 0) {
          pc += val(op->arg2);
          std::cout << std::endl;
          continue;
        }
      }
      std::cout << std::endl;
      pc += 1;
    }
  }

};


int main() {
  std::vector<Operation*> operations;


  std::ifstream infile("day23input");
  std::string line;
  while(std::getline(infile, line)) {
    std::istringstream iss(line);
    std::string instruction, arg1, arg2;

    iss >> instruction >> arg1;
    if(instruction == "snd" || instruction == "rcv") {
      operations.push_back(new Operation(instruction, arg1, ""));
    } else {
      iss >> arg2;
      operations.push_back(new Operation(instruction, arg1, arg2));
    }
  }

  {

  }

  // {
  //   std::vector<long long> registers(26);
  //   long long pc = 0;
  //   long long stored_freq = 0;
  //   long long muls = 0;
  //   while(pc >= 0 && pc < operations.size()) {
  //     Operation* op = operations[pc];
  //     //// std::cout << op->instruction << " " << op->arg1 << " " << op->arg2 << std::endl;

  //     if(op->instruction == "set") {
  //       registers[op->arg1[0]-'a'] = val(op->arg2, registers);
  //       //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
  //     } else if(op->instruction == "sub") {
  //       registers[op->arg1[0]-'a'] -= val(op->arg2, registers);
  //       //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
  //     } else if(op->instruction == "mul") {
  //       registers[op->arg1[0]-'a'] *= val(op->arg2, registers);
  //       muls += 1;
  //       //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
  //     } else if(op->instruction == "jnz") {
  //       if(val(op->arg1, registers) != 0) {
  //         pc += val(op->arg2, registers);
  //         continue;
  //       }
  //     }
  //     pc += 1;
  //   }
  //   std::cout << muls << std::endl;
  // }

{

  long long d = 0;
  long long e = 0;
  long long h = 0;
  long long g = 0;

  long long f = 0;
  long long a = 1;
  long long b = 0;
  long long c = 0;

  b = 79;
  b = b * 100;
  b = b + 100000;
  c = b;
  c = c + 17000;

 C:
  for(; b <= c; b+= 17) {
    std::cout << b << std::endl;
    f = 1;

    for(d = 2; d < b; d++) {
      if( (b%d) == 0) {
        f = 0;
        break;
      }
    }
    if(f == 0) {
      h += 1;
    }
  }
  std::cout << h << std::endl;
 }
// not 906
}
