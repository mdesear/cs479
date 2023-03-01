#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "boxmuller.h"

using namespace std;
using namespace Eigen;

typedef pair<float, float> PairData;

enum Label { ClassOne, ClassTwo };

vector<PairData>* SetupData(PairData u1, PairData e1, PairData u2, PairData e2)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200000; i++)
    {
        if (i < 60000)
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u1.first, sqrt(e1.first)), boxmuller::box_muller(u1.second, sqrt(e1.second))));
        else
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u2.first, sqrt(e2.first)), boxmuller::box_muller(u2.second, sqrt(e2.second))));
    }

    return newData;
}

int main(int argc, char* argv[])
{
    vector<PairData> dataSetA = *SetupData(make_pair(1, 1), make_pair(1, 1), make_pair(4, 4), make_pair(1, 1));
    vector<PairData> dataSetB = *SetupData(make_pair(1, 1), make_pair(1, 1), make_pair(4, 4), make_pair(4, 8));
    
    Matrix2f matrix_A1;
    Matrix2f matrix_B2;

    matrix_A1 << 1, 0, 0, 1;
    Matrix2f matrix_A2 = matrix_A1;
    Matrix2f matrix_B1 = matrix_A1;
    matrix_B2 << 4, 0, 0, 8;
    
    for(int i = 0; i < dataSetA.size(); i++)
        printf("Data Set 1: %.4f %.4f\tData Set 2: %.4f %.4f\t Number: %i\n", dataSetA[i].first, dataSetA[i].second, dataSetB[i].first, dataSetB[i].second, i + 1);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}
