/**
 * iteration1.cc
 *
 * Print all items of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration1.hh"
using namespace std;


void printAllItems(const list<int>& lst)
{
    for (auto& item : lst) {
            std::cout << item << " ";
        }
        std::cout << std::endl;
}
