#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Return an iterator which points to the last even integer of the vector
 *        If the value is not found, return v.rend()
 *
 * @param v the vector to be scanned through
 * @return std::vector<int>::reverse_iterator
 */
bool IsEven (int i) {
  return ((i%2)==0);
}

std::vector<int>::reverse_iterator findLastEven(std::vector<int>& v)
{
    std::vector<int>::reverse_iterator it;
    it = std::find_if(v.rbegin(),v.rend(), IsEven);
        return it;
}

