#include <cstddef>
#include <iostream>

/**
 * Bag
 * - 不支持删除元素
 * - 迭代顺序不确定
 */

template <typename T>
class Bag {
public:
    Bag() = default;
    Bag(const Bag&) = default;
    Bag(Bag&&) noexcept = default;
    Bag& operator=(const Bag&) = default;
    Bag& operator=(Bag&&) noexcept = default;
    virtual ~Bag() = default;

    void add(T item);

    bool empty();

    std::size_t size();
};

int main(int argc, char const* argv[]) {
    std::cout << "hello" << std::endl;
    return 0;
}
