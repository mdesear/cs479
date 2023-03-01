#include <iostream>
#include <string>
#include <vector>
#include "boxmuller.h"

using namespace std;

vector<pair<float, float>>* SetupData(pair<float, float> u1_firstSet, pair<float, float> u1_secondSet, pair<float, float> u2_firstSet, pair<float, float> u2_secondSet)
{
    const auto newData = new vector<pair<float, float>>;
    for(int i = 0; i < 200000; i++)
    {
        if (i < 60000)
            (*newData).emplace_back(std::make_pair(boxmuller::box_muller(u1_firstSet.first, sqrt(u1_firstSet.second)), boxmuller::box_muller(u1_secondSet.first, sqrt(u1_secondSet.second))));
        else
            (*newData).emplace_back(std::make_pair(boxmuller::box_muller(u2_firstSet.first, sqrt(u2_firstSet.second)), boxmuller::box_muller(u2_secondSet.first, sqrt(u2_secondSet.second))));
    }

    return newData;
}

int main(int argc, char* argv[])
{
    vector<pair<float, float>> dataSetA = *SetupData(std::make_pair(1, 1), std::make_pair(1, 1), std::make_pair(4, 1), std::make_pair(4, 1));
    vector<pair<float, float>> dataSetB = *SetupData(std::make_pair(1, 1), std::make_pair(1, 1), std::make_pair(4, 4), std::make_pair(4, 8));

    for(int i = 0; i < dataSetA.size(); i++)
        printf("Data Set 1: %.4f %.4f\tData Set 2: %.4f %.4f\t Number: %i\n", dataSetA[i].first, dataSetA[i].second, dataSetB[i].first, dataSetB[i].second, i + 1);
    
    dataSetA.clear();
    dataSetB.clear();
    
    return 0;
}
