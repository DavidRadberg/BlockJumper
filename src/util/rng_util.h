
#include <cstdlib>

float generate_random_float(float max = 1.0, float min = 0.0)
{
    return min + static_cast <float> (rand()) / ( static_cast <float> (RAND_MAX / (max - min)));
}