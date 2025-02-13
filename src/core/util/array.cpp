#include "array.h"
#include <vector>
#include <algorithm> 

float* array::vectorToArray(std::vector<float> vector, size_t& sizeAr)
{
    const int size = vector.size();
    float* arr = new float[size];
    std::copy(vector.begin(), vector.end(), arr);
    sizeAr = size;
    return arr;
}