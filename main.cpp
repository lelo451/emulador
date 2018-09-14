#include "main.h"

int main() {
    string line;
    ifstream file;
    int inst = 0;
    file.open("instrucoes.txt", ios::out);
    if (file.is_open()) {
        while ( getline(file,line) ) {
            decode(line, inst);
            inst++;
        }
        file.close();
    }
    execute();
    return 0;
}