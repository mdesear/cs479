#include <iostream>
#include <string>
#include <vector>
#include "boxmuller.h"

using namespace std;

vector<pair<float, float>>* SetupData(float m1, float s1, float m2, float s2)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200000; i++)
    {
        if (i < 60000)
            (*newData).emplace_back(std::make_pair(boxmuller::box_muller(m1, s1), boxmuller::box_muller(m1, s1)));
        else
            (*newData).emplace_back(std::make_pair(boxmuller::box_muller(m2, s2), boxmuller::box_muller(m2, s2)));
    }

    return newData;
}

int main(int argc, char* argv[])
{
    vector<pair<float, float>> dataSetA = *SetupData(1, 1, 1, 1);
    vector<pair<float, float>> dataSetB = *SetupData(1, 1, 4, 8);

    for(int i = 0; i < dataSetA.size(); i++)
        printf("Data Set 1: %.4f %.4f\tData Set 2: %.4f %.4f\t Number: %i\n", dataSetA[i].first, dataSetA[i].second, dataSetB[i].first, dataSetB[i].second, i + 1);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}
