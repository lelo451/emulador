#ifndef EMULADOR_MAIN_H
#define EMULADOR_MAIN_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

#define SIZE 1024
#define REGISTERS 10

struct instruction {
    ulong op;
    u_char dest;
    u_char src1;
    uint src2;
} code [SIZE];

uint pc;
vector<int> registers(REGISTERS, 0);
vector<string> dados(SIZE, "");

#endif
