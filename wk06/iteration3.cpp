/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    auto middle = lst.begin();
        std::advance(middle, lst.size() / 2);

        for (auto it = lst.begin(); it != middle; ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
}
