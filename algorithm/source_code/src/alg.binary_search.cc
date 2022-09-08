#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

#include "alg.h"

std::size_t binary_search(const int& key, const std::vector<int>& array) {
    std::size_t lo = 0;
    std::size_t hi = array.size() - 1;
    std::size_t mid = 0;
    while (lo <= hi) {
        mid = lo + (hi - lo) / 2;
        const int& mid_num = array[mid];
        if (key < mid_num) {
            hi = mid - 1;
        }
        else if (mid_num > key) {
            lo = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}

int main(int argc, char const* argv[]) {
    std::vector<int> array = alg::parse_int_args(argc, argv);
    int key = 0;
    std::cout << "Input key: " << std::endl;
    std::cin >> key;
    std::sort(array.begin(), array.end());
    std::size_t found = binary_search(key, array);
    alg::print_array(array, found);
    return 0;
}
