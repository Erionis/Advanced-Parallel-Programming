#include "array.hpp"

template<typename T, typename OUTPUT>
OUTPUT average(const Array<T>& a)
{
    OUTPUT sum{0};

    for (size_t i=0; i<a.size(); ++i) {
        sum += a[i];
    }

    return sum/a.size();
}