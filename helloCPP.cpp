#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <H5Cpp.h>

using namespace std;
using namespace H5;

int main() {
    ifstream inFile("user.txt");
    string names;
    getline(inFile, names);

    float Amplitude, Omega, Phi0, time_start, time_end, time_step;
    inFile >> Amplitude >> Omega >> Phi0 >> time_start >> time_end >> time_step;
    inFile.close();

    ofstream outFile("hello.txt");
    outFile << fixed << setprecision(2);
    outFile << "time(s) Voltage(V)\n";

    vector<float> times;
    vector<float> voltages;

    for (float t = time_start; t <= time_end; t += time_step) {
        float voltage = Amplitude * sin(Omega * t + Phi0);
        times.push_back(t);
        voltages.push_back(voltage);
        outFile << t << " " << voltage << "\n";
    }

    const hsize_t count = static_cast<hsize_t>(times.size());
    hsize_t dims[1] = {count};

    H5File file("output.h5", H5F_ACC_TRUNC);
    DataSpace dataspace(1, dims);
    DataSet tset = file.createDataSet("time", PredType::NATIVE_FLOAT, dataspace);
    tset.write(times.data(), PredType::NATIVE_FLOAT);
    DataSet vset = file.createDataSet("voltage", PredType::NATIVE_FLOAT, dataspace);
    vset.write(voltages.data(), PredType::NATIVE_FLOAT);

    cout << "Sinusoidal data generated successfully!\n";
    cout << "Saved output array to output.h5\n";
    system("python plot.py");
    //system("pause");
    return 0;
}
