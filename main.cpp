#include "main.h"

int main() {
    string line;
    ifstream file;
    file.open("instrucoes.txt", ios::out);
    cout << dados[9] << endl;
    if (file.is_open()) {
        while ( getline(file,line) ) {
            cout << line << '\n';
        }
        file.close();
    }
    return 0;
}