#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream inFile("user.txt");
    string line;
    inFile>>line;
    inFile.close();
    ofstream outFile("hello.txt");
    outFile <<"Hello, " << line << "!\n";
    outFile.close();
    
    cout << "File created and written successfully!\n";
    return 0;
}
