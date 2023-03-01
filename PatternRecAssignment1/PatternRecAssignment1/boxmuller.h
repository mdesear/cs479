#pragma once
#include <math.h>
#include <cstdlib>

class boxmuller
{
private:
    static float ranf();
public:
    static float box_muller(float m, float s);
};