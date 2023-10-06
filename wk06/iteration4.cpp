/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration4.hh"
using namespace std;


void printReverse(const list<int>& lst)
{
    for (auto it = lst.rbegin(); it != lst.rend(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
}
