#include "array.hpp"
#include <vector>
#include <algorithm> 

float* array::vectorToArray(std::vector<float> vector, int& sizeAr)
{
    const int size = vector.size();
    float* arr = new float[size];
    std::copy(vector.begin(), vector.end(), arr);
    sizeAr = size;
    return arr;
}