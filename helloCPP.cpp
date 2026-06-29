#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
    ifstream inFile("user.txt");
    string names;
    getline(inFile, names);
    float Amplitude, Omega, Phi0, time_start, time_end, time_step;
    inFile >> Amplitude >> Omega >> Phi0 >> time_start >> time_end >> time_step;
    inFile.close();
    ofstream outFile("hello.txt");
    outFile << fixed << setprecision(2);
    outFile <<"time(s) Voltage(V)\n";
    for (float t = time_start; t <= time_end; t += time_step)
    {
        float voltage = Amplitude * sin(Omega * t + Phi0);
        outFile << t << " " << voltage << "\n";
    }
    
    outFile.close();
    
    cout << "Sinusoidal data generated successfully!\n";
    return 0;
}
