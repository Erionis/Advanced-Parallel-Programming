#include <cmath>
#include "array.hpp"

template<typename T>
T norm_2(const Array<T>& a)
{
    T square_sum{0};

    for (size_t i=0; i<a.size(); ++i) {
        square_sum += a[i]*a[i];
    }

    return sqrt(square_sum);
}
