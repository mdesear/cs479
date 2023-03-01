#include <iostream>
#include <string>
#include <vector>
#include "boxmuller.h"

using namespace std;

vector<pair<float, float>>* SetupData(float m, float s)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200001; i++)
    {
        (*newData).emplace_back(std::make_pair(boxmuller::box_muller(m, s), boxmuller::box_muller(m, s)));
    }

    return newData;
}

int main(int argc, char* argv[])
{
    vector<pair<float, float>> dataSetA = *SetupData(1, 1);
    vector<pair<float, float>> dataSetB = *SetupData(4, 4);

    for(int i = 0; i < dataSetA.size(); i++)
        printf("Data Set 1: %.4f %.4f\tData Set 2: %.4f %.4f\t Number: %i\n", dataSetA[i].first, dataSetA[i].second, dataSetB[i].first, dataSetB[i].second, i + 1);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}
