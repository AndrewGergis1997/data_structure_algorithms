#include <iterator>
#include <vector>
#include <algorithm>
#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    // Create three empty vectors to store the elements divisible by 3, with
    // remainder 1, and with remainder 2, respectively.
    std::vector<int> DivBy3;
    std::vector<int> Remainder1;
    std::vector<int> Remainder2;

    // Partition the input vector `v` into the three vectors based on the remainder
    // of each element when divided by 3.
    std::partition_copy(v.begin(), v.end(), std::back_inserter(DivBy3),
                        [](int x) { return x % 3 == 0; });
    std::partition_copy(v.begin(), v.end(), std::back_inserter(Remainder1),
                        [](int x) { return x % 3 == 1; });
    std::partition_copy(v.begin(), v.end(), std::back_inserter(Remainder2),
                        [](int x) { return x % 3 == 2; });

    // Sort the three vectors in ascending order.
    std::sort(DivBy3.begin(), DivBy3.end());
    std::sort(Remainder1.begin(), Remainder1.end());
    std::sort(Remainder2.begin(), Remainder2.end());

    // Concatenate the three vectors back into the input vector `v` in the desired
    // order.
    v.clear();
    v.insert(v.end(), DivBy3.begin(), DivBy3.end());
    v.insert(v.end(), Remainder1.begin(), Remainder1.end());
    v.insert(v.end(), Remainder2.begin(), Remainder2.end());

    return EXIT_SUCCESS;
}

