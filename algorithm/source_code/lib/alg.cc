#include "alg.h"

#include <iostream>
#include <string>
#include <vector>

namespace alg {

std::vector<int> parse_int_args(const int& argc, const char* argv[]) {
    std::vector<int> result;
    result.reserve(argc - 1);
    for (int i = 1; i < argc; ++i) {
        result.emplace_back(std::stoi(argv[i]));
    }
    return result;
}

std::vector<std::string> parse_string_args(const int& argc,
                                           const char* argv[]) {
    std::vector<std::string> result;
    for (int i = 1; i < argc; ++i) {
        result.emplace_back(argv[i]);
    }
    return result;
}

std::string parse_string_arg(const int& argc, const char* argv[]) {
    std::string result;
    for (int i = 1; i < argc; ++i) {
        result.append(argv[i]);
        result.push_back(' ');
    }
    return result;
}

} // namespace alg
