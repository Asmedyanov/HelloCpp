#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ifstream inFile("user.txt");
    string names;
    getline(inFile, names);
    float num1, num2, num3;
    inFile >> num1 >> num2 >> num3;
    inFile.close();
    ofstream outFile("hello.txt");
    outFile << fixed << setprecision(2) << "Equation: " << num1 << "x^2+" << num2 << "x+" << num3 << "=0\n";
    float D = num2 * num2 - 4 * num1 * num3;
    outFile << "Discriminant: " << D << "\n";
    float x1, x2;
    if (D > 0) {
        x1 = (-num2 + sqrt(D)) / (2 * num1);
        x2 = (-num2 - sqrt(D)) / (2 * num1);
        outFile << "Roots: " << x1 << ", " << x2 << "\n";
    } else if (D == 0) {
        x1 = -num2 / (2 * num1);
        outFile << "Root: " << x1 << "\n";
    } else {
        outFile << "No real roots.\n";
    }
    outFile.close();
    
    cout << "Square equation processed successfully!\n";
    return 0;
}
