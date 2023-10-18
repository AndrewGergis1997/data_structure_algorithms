#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    int size = v.size();
    std::sort(v.begin(), v.end());
    if (size ==0){
        return NOT_FOUND;
    }
    else if ((v.size() % 2) == 0)
    {
     return (v[size/2-1] + v[size/2]) / 2;
    }
    else
    {
    return v[size/2];
    }

}

