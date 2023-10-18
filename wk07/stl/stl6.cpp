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
bool isGreater (int i,int given) {
  return (i>=given);
}

int findAtLeastGiven(std::map<std::string, int>& m, int given)
{
        // create a empty vector of pairs
       vector<pair<string, int>> vec;

        // copy key-value pairs from the map to the vector
      map<string, int> :: iterator it2;
      for (it2=m.begin(); it2!=m.end(); it2++)
      {
        vec.push_back(make_pair(it2->first, it2->second));
      }

        // // sort the vector by increasing order of its pair's second value
      sort(vec.begin(), vec.end(), [m](pair<string, int> &a,const pair<string, int> &b){ return (a.second < b.second); });
    // Create an iterator to the first element in the map.
      auto it = vec.begin();

      it = std::lower_bound(vec.begin(), vec.end(), given,
                             [](const auto& p, int value) { return p.second < value; });

      if (it == vec.end()) {
        return NOT_FOUND;
      }

      return it->second;
}

