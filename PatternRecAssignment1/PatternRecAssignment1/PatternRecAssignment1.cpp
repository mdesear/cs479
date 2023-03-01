#include <iostream>
#include <vector>
#include "boxmuller.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<pair<float, float>> dataSet1, dataSet2;
    for(int i = 0; i < 200001; i++)
        dataSet1.emplace_back(std::make_pair(boxmuller::box_muller(0, 1), boxmuller::box_muller(0, 1)));

    for (auto data : dataSet1)
    {
        cout << data.first << " " << data.second << endl;
    }
    
    dataSet1.clear();
    
    return 0;
}
