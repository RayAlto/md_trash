#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

#include "alg.h"

class A {};
class B : public A {};

int main(int argc, char const* argv[]) {
    for (const int& arg : alg::parse_int_args(argc, argv)) {
        std::cout << arg << std::endl;
    }
    return 0;
}
