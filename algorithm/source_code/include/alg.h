#ifndef TEST_ALG_H_
#define TEST_ALG_H_

#include <cstddef>
#include <iostream>
#include <string>
#include <vector>

namespace alg {

std::vector<int> parse_int_args(const int& argc, const char* argv[]);
std::vector<std::string> parse_string_args(const int& argc, const char* argv[]);
std::string parse_string_arg(const int& argc, const char* argv[]);

template <typename T>
void print_array(const std::vector<T>& array, const std::size_t& index) {
    for (std::size_t i = 0; i < array.size(); ++i) {
        if (i == index) {
            std::cout << '[' << array[i] << "], ";
        }
        else {
            std::cout << array[i] << ", ";
        }
    }
    std::cout << std::endl;
}

} // namespace alg

#endif // TEST_ALG_H_
