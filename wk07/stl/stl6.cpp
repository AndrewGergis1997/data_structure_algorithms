#include <iterator>
#include <map>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief From a map find the first element, whose value is at least given limit
 *        regardless of the key of the element. Return only the value or
 *        NOT_FOUND if none of the values match the the search criteria.
 * @param m map that is scanned trough
 * @param given limit for the values to search
 * @return int the real found value
 */

int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
    // Convert the map to a vector of pairs, sorted by the second value of each
    // pair.
    std::vector<std::pair<std::string, int>> vec(m.begin(), m.end());
    std::sort(vec.begin(), vec.end(), [](const auto& p1, const auto& p2) {
      return p1.second < p2.second;
    });

    // Use the std::lower_bound() algorithm to find the first element in the vector
    // whose value is greater than or equal to the given value.
    auto it = std::lower_bound(vec.begin(), vec.end(), given,
                               [](const auto& p, int value) { return p.second < value; });

    // If the iterator is at the end of the vector, then there is no element in the
    // map whose value is at least the given limit. Return NOT_FOUND.
    if (it == vec.end()) {
      return NOT_FOUND;
    }

    // Otherwise, return the value of the element at the iterator.
    return it->second;
}

