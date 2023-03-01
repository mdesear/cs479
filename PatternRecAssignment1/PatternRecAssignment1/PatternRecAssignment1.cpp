#include <iostream>
#include <string>
#include <vector>
#include <Eigen/Dense>
#include "boxmuller.h"

using namespace std;
using namespace Eigen;

typedef pair<float, float> PairData;

enum Label { ClassOne, ClassTwo };

vector<PairData>* SetupData(PairData u1, Matrix2f e1, PairData u2, Matrix2f e2)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200000; i++)
    {
        if (i < 60000)
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u1.first, sqrt(e1(0, 0))), boxmuller::box_muller(u1.second, sqrt(e1(1, 1)))));
        else
            (*newData).emplace_back(make_pair(boxmuller::box_muller(u2.first, sqrt(e2(0, 0))), boxmuller::box_muller(u2.second, sqrt(e2(1, 1)))));
    }

    return newData;
}

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
    vector<PairData> dataSetA = *SetupData(pair1, matrix1, pair2, matrix1);
    vector<PairData> dataSetB = *SetupData(pair1, matrix1, pair2, matrix2);
    
    for(int i = 0; i < dataSetA.size(); i++)
        printf("Data Set 1: %.4f %.4f\tData Set 2: %.4f %.4f\n", dataSetA[i].first, dataSetA[i].second, dataSetB[i].first, dataSetB[i].second);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}
