#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {
    auto beg = vec.begin();
    for (auto i = beg; i != (beg + vec.size()); i++){
        vec.erase(i+1);
        if (i >= vec.end()){
            break;
        }
    }
}

