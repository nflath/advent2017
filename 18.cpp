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
      //std::cout << idx << "::" << pc << ": " << op->instruction << " " << op->arg1 << " " << op->arg2 << "  ";

      if(op->instruction == "snd") {
        sends++;
        out->push(val(op->arg1));
      } else if(op->instruction == "set") {
        registers[op->arg1[0]-'a'] = val(op->arg2);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "add") {
        registers[op->arg1[0]-'a'] += val(op->arg2);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "mul") {
        registers[op->arg1[0]-'a'] *= val(op->arg2);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "mod") {
        registers[op->arg1[0]-'a'] %= abs(val(op->arg2));
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
      } else if(op->instruction == "rcv") {
        if(in->size()==0) {
          state = WAITING;
          //std::cout << std::endl;
          return;
        }

        registers[op->arg1[0]-'a'] = in->front();
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'];
        in->pop();
      } else if(op->instruction == "jgz") {
        if(val(op->arg1) > 0) {
          pc += val(op->arg2);
          //  std::cout << std::endl;
          continue;
        }
      }
      //std::cout << std::endl;
      pc += 1;
    }
  }

};


int main() {
  std::vector<long long> registers(26);
  std::vector<Operation*> operations;


  std::ifstream infile("day18input");
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
    long long pc = 0;
    long long stored_freq = 0;
    while(true) {
      Operation* op = operations[pc];
      //// std::cout << op->instruction << " " << op->arg1 << " " << op->arg2 << std::endl;

      if(op->instruction == "snd") {
        stored_freq = val(op->arg1, registers);
      } else if(op->instruction == "set") {
        registers[op->arg1[0]-'a'] = val(op->arg2, registers);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
      } else if(op->instruction == "add") {
        registers[op->arg1[0]-'a'] += val(op->arg2, registers);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
      } else if(op->instruction == "mul") {
        registers[op->arg1[0]-'a'] *= val(op->arg2, registers);
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
      } else if(op->instruction == "mod") {
        registers[op->arg1[0]-'a'] %= abs(val(op->arg2, registers));
        //std::cout << op->arg1[0] << " = " << registers[op->arg1[0]-'a'] << std::endl;
      } else if(op->instruction == "rcv") {
        if(stored_freq != 0) {
          std::cout << "stored_freq: " << stored_freq << std::endl;
          break;
        }
      } else if(op->instruction == "jgz") {
        if(val(op->arg1, registers) > 0) {
          pc += val(op->arg2, registers);
          continue;
        }
      }
      pc += 1;
    }
  }

  {

    std::vector<std::queue<long long> > input(2);


    Emulator* emulator[2];
    emulator[0] = new Emulator(0, &input[0], &input[1]);
    emulator[1] = new Emulator(1, &input[1], &input[0]);

    for(long long i = 0; i < 2; ++i) {
      emulator[i]->operations = operations;
      emulator[i]->registers['p'-'a'] = i;
    }

    long long idx = 0;
    while(!(emulator[0]->state == Emulator::STOPPED &&
            emulator[1]->state == Emulator::STOPPED)) {

      if(emulator[0]->state == Emulator::WAITING && input[0].size()==0 &&
         emulator[1]->state == Emulator::WAITING && input[1].size()==0) {
        std::cout << "Breaking because deadlock" << std::endl;
        break;
      }


      long long other = (idx + 1)%2;
      if(emulator[idx]->state == Emulator::STOPPED &&
         (emulator[other]->state == Emulator::WAITING))

        break;

      emulator[idx]->run();

      idx += 1;
      idx %= 2;
    }
    std::cout << emulator[0]->state << " " << emulator[1]->state << std::endl;
    std::cout << emulator[0]->sends << " ";
    std::cout << emulator[1]->sends << std::endl;
  }
}
