#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <H5Cpp.h>

using namespace std;
using namespace H5;

class main_parameters {
public:
    float l_wire, r_wire,dr_wire,r_water,dr_water,t_min,t_max,dt_min;
    int n_h5,n_png,n_proc;
    main_parameters(string filename) {
        ifstream inFile(filename);
         string line;

        // skip header line: "Parameter,Value,Comment"
        getline(inFile, line);

        while (getline(inFile, line)) {
            if (line.empty()) continue;

            // split line by commas
            stringstream ss(line);
            string name, valueStr, comment;
            getline(ss, name, ',');
            getline(ss, valueStr, ',');
            getline(ss, comment, ',');

            float value = stof(valueStr);

            if      (name == "l_wire")  l_wire  = value;
            else if (name == "r_wire")  r_wire  = value;
            else if (name == "dr_wire") dr_wire = value;
            else if (name == "r_water") r_water = value;
            else if (name == "dr_water")dr_water= value;
            else if (name == "t_min")   t_min   = value;
            else if (name == "t_max")   t_max   = value;
            else if (name == "dt_min")  dt_min  = value;
            else if (name == "n_h5")    n_h5    = (int)value;
            else if (name == "n_png")   n_png   = (int)value;
            else if (name == "n_proc")  n_proc  = (int)value;
        }


        inFile.close();
    }
};

int main() {

    main_parameters main_parameter("input/parameters.csv");
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
