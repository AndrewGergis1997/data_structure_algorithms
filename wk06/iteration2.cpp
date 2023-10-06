/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    bool print = true;
        for (const auto& item : lst) {
            if (print) {
                std::cout << item << " ";
            }
            print = !print;
        }
        std::cout << std::endl;
}
