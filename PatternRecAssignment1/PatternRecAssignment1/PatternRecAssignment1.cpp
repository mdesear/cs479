#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "boxmuller.h"

using namespace std;
using namespace Eigen;

typedef pair<float, float> PairData;
enum Label { ClassOne, ClassTwo };

string DataSetA_File = "Data\\DataSetA.csv";
string DataSetB_File = "Data\\DataSetB.csv";

//prototypes
vector<PairData>* SetupData(string fname, PairData, Matrix2f, PairData, Matrix2f);
vector<PairData>* ReadInData(string);
void SaveDataToFile(string, vector<PairData>);
bool CheckIfFileExists(string);

int main(int argc, char* argv[])
{
    // Sigma Values
    Matrix2f matrix1;
    Matrix2f matrix2;
    matrix1 << 1, 0, 0, 1;
    matrix2 << 4, 0, 0, 8;
    
    // Mu Values
    constexpr PairData pair1 = make_pair(1, 1);
    constexpr PairData pair2 = make_pair(4, 4);

    // Datasets created from the Mu and Sigma values fed into a Boxmuller
    vector<PairData> dataSetA = CheckIfFileExists(DataSetA_File) ? *ReadInData(DataSetA_File) : *SetupData(DataSetA_File, pair1, matrix1, pair2, matrix1);
    vector<PairData> dataSetB = CheckIfFileExists(DataSetB_File) ? *ReadInData(DataSetB_File) : *SetupData(DataSetB_File, pair1, matrix1, pair2, matrix2);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}

bool CheckIfFileExists(string fname)
{
    ifstream file (fname.c_str());
    return file.good();
}

vector<PairData>* ReadInData(string fname)
{
    const auto newData = new vector<pair<float, float>>;
    string line, value;
    
    fstream file (fname, ios::in);
    if(file.is_open())
    {
        while(getline(file, line))
        {
            int i = 0;
            PairData temp;
            stringstream str(line);
            while(getline(str, value, ','))
            {
                if (i ==  0)
                    temp.first = stof(value);
                else
                    temp.second = stof(value);
                i++;
            }
            (*newData).emplace_back(temp);
        }
    }
    file.close();
    return newData;
}

void SaveDataToFile(string fname, vector<PairData>* dataSet)
{
    fstream file (fname, ios::out);
    if(file.is_open())
    {
        for (auto data : *dataSet)
            file << data.first << "," << data.second << "\n";
    }
    file.close();
}

vector<PairData>* SetupData(string fname, PairData u1, Matrix2f e1, PairData u2, Matrix2f e2)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200000; i++)
    {
        if (i < 60000)
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u1.first, sqrt(e1(0, 0))), boxmuller::box_muller(u1.second, sqrt(e1(1, 1)))));
        else
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u2.first, sqrt(e2(0, 0))), boxmuller::box_muller(u2.second, sqrt(e2(1, 1)))));
    }

    SaveDataToFile(fname, newData);
    return newData;
}