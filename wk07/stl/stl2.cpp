#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief sort a given vector to an descending order
 *
 * @param v a vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortDesc(std::vector<int>& v)
{
    std::sort (v.begin(), v.end());
    if (std::is_sorted(v.begin(),v.end())){
        std::reverse(v.begin(),v.end());
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

