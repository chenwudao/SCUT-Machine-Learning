#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ifstream fin;
    string buffer;
    fin.open("test.txt",ios::in);
    while (fin >> buffer) cout << buffer << endl;
    fin.close();
}