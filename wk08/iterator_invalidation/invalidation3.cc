#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;


    Iter end = vec.end();
    Iter it = vec.begin();
    int count = 0;
    while (it != vec.end()){
        if ( *it % 2 == 0 ){
            vec.insert(it, *it);
            end = vec.end();
            count++;
        }
        else {
            vec.erase(it);
            end = vec.end();
            count--;
        }
        count++;
        it = vec.begin() + count;
    }
}

