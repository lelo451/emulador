#ifndef EMULADOR_MAIN_H
#define EMULADOR_MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

#define SIZE 1024
#define REGISTERS 10

void execute();

int aritmetic(int x, int y, int op);

void jump(int x, int y, int op);

void mov(int x, int y);

void loadi(int x, int y);

void write(int x);

void read(int x);

void loadm(int x, int y);

void storem(int x, int y);

void counthotness(int pc);

struct instruction {
    int op;
    int dest;
    int src1;
    int src2;
};

struct mem {
    int palavra;
    instruction code;
} memoria[SIZE];

int pc = 0;
//int backjmpflag = 0;

vector<int> registers(REGISTERS, 0);
unordered_map<int, int> hotness;

void decode(string line, int instcount) {
    stringstream stream(line);
    stringstream s2;
    string tmp;
    stream >> tmp;
    if (tmp == "ADD") {
        memoria[instcount].code.op = 1;
    } else if (tmp == "SUB") {
        memoria[instcount].code.op = 2;
    } else if (tmp == "DIV") {
        memoria[instcount].code.op = 3;
    } else if (tmp == "MUL") {
        memoria[instcount].code.op = 4;
    } else if (tmp == "MOV") {
        memoria[instcount].code.op = 5;
    } else if (tmp == "LOADM") {
        memoria[instcount].code.op = 6;
    } else if (tmp == "STOREM") {
        memoria[instcount].code.op = 7;
    } else if (tmp == "LOADI") {
        memoria[instcount].code.op = 8;
    } else if (tmp == "WRITE") {
        memoria[instcount].code.op = 9;
    } else if (tmp == "READ") {
        memoria[instcount].code.op = 10;
    } else if (tmp == "EXIT") {
        memoria[instcount].code.op = 11;
    } else if (tmp == "BRZ") {
        memoria[instcount].code.op = 12;
    } else if (tmp == "BRNZ") {
        memoria[instcount].code.op = 13;
    } else if (tmp == "IBRZ") {
        memoria[instcount].code.op = 14;
    } else if (tmp == "BLZ") {
        memoria[instcount].code.op = 15;
    }
    stream >> tmp;
    s2 << tmp;
    tmp = s2.str();
    if (tmp[0] == 'r') {
        stringstream convert(tmp.erase(0, 1));
        convert >> memoria[instcount].code.src1;
    } else {
        stringstream convert(tmp);
        convert >> memoria[instcount].code.src1;
    }
    memoria[instcount].code.dest = memoria[instcount].code.src1;
    stream >> tmp;
    if (tmp[0] == 'r') {
        stringstream convert(tmp.erase(0, 1));
        convert >> memoria[instcount].code.src2;
    } else {
        stringstream convert(tmp);
        convert >> memoria[instcount].code.src2;
    }
}

void execute() {
    int instruction = 0;
    while (1) {
        int x = memoria[pc].code.src1;
        int y = memoria[pc].code.src2;
        int dest = memoria[pc].code.dest;
        int op = memoria[pc].code.op;
        if (op == 1) {
            registers[dest] = aritmetic(x, y, 1);
            pc++;
        } else if (op == 2) {
            registers[dest] = aritmetic(x, y, 2);
            pc++;
        } else if (op == 3) {
            registers[dest] = aritmetic(x, y, 3);
            pc++;
        } else if (op == 4) {
            registers[dest] = aritmetic(x, y, 4);
            pc++;
        } else if (op == 5) {
            mov(x, y);
            pc++;
        } else if (op == 6) {
            loadm(x, y);
            pc++;
        } else if (op == 7) {
            storem(x, y);
            pc++;
        } else if (op == 8) {
            loadi(x, y);
            pc++;
        } else if (op == 9) {
            write(x);
            pc++;
        } else if (op == 10) {
            read(x);
            pc++;
        } else if (op == 11) {
            cout << instruction << endl;
            exit(0);
        } else if (op == 12) {
            jump(x, y, 1);
        } else if (op == 13) {
            jump(x, y, 2);
        } else if (op == 14) {
            jump(x, y, 3);
        } else if (op == 15) {
            jump(x, y, 4);
        }
        instruction++;
    }
}

int aritmetic(int x, int y, int op) {
    switch (op) {
        case 1: // add
            return registers[x] + registers[y];
            break;
        case 2: // sub
            return registers[x] - registers[y];
            break;
        case 3: // div
            return registers[x] / registers[y];
            break;
        case 4: // mul
            return registers[x] * registers[y];
            break;
    }
}

void jump(int x, int y, int op) {
    switch (op) {
        case 1: // brz
            if (registers[x] == 0) {
                pc += y;
                if (y < 0) {
                    //backjmpflag = 1;
                    counthotness(pc);
                }
            } else {

                pc++;
            }
            break;
        case 2: // brnz
            if (registers[x] != 0) {
                pc += y;
                if (y < 0) {
                    counthotness(pc);
                }
            } else
                pc++;
            break;
        case 3: //ibrz
            if (registers[x] == 0) {
                pc = y;
                if (y < 0) {
                    counthotness(pc);
                }
            } else
                pc++;
            break;
        case 4: //blz
            if (registers[x] < 0) {
                pc += y;
                if (y < 0) {
                    counthotness(pc);
                }
            } else
                pc++;
            break;
    }
}

void counthotness(int pc) {
    auto it = hotness.find(pc);
    if (it != hotness.end()) {
        it->second = it->second + 1;
        if (it->second >= 50) {
            cout << "Uma area pegando fogo foi encontrada! " << endl;
        }
    } else
        hotness.insert(make_pair(pc, 1));
}

void mov(int x, int y) {
    registers[x] = registers[y];
}

void loadi(int x, int y) {
    registers[x] = y;
}

void write(int x) {
    cout << registers[x] << endl;
}

void read(int x) {
    cin >> registers[x];
}

void loadm(int x, int y) {
    registers[x] = memoria[y].palavra;
}

void storem(int x, int y) {
    memoria[y].palavra = registers[x];
}

#endif
