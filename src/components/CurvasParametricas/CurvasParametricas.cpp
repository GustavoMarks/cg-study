#include "CurvasParametricas.hpp"

// BÃ©zier's Blending Functions
double b_1(double t)
{
    return (1.0 - t - t*t + t*t*t);
}

double b_2(double t)
{
    return (t - 2.0*t*t + t*t*t);
}

double b_3(double t)
{
    return (t*t - t*t*t);
}

double b_4(double t)
{
    return (2.0*t*t - t*t*t);
}