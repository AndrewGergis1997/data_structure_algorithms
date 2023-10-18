#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Remove from vector v all elements with value less than the limit
 * @param v a vector whose values are to be erased if less than limit
 * @param limit a threshold whose lower values are removed
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int removeLessThan(std::vector<int>& v, int limit)
{
    std ::vector<int>tempv;
    std::copy_if(v.begin(),v.end(),std::back_inserter(tempv),[limit](int x){return x > limit;});
    v.clear();
    v.insert(v.end(),tempv.begin(), tempv.end());
    return EXIT_SUCCESS;
}

