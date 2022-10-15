#include <cstddef>
#include <iostream>
#include <memory>
#include <vector>

#include "alg.h"

using alg::container::Node;

template <typename T>
class Stack {
public:
    Stack() = default;
    Stack(const Stack&) = default;
    Stack(Stack&&) noexcept = default;
    Stack& operator=(const Stack&) = default;
    Stack& operator=(Stack&&) noexcept = default;
    virtual ~Stack() = default;

    void push(T item) {}

    T pop() {}

    bool empty() {}

    const std::size_t& size() {
        return size_;
    }

protected:
    std::unique_ptr<Node<T>> list_;
    std::size_t size_ = 0;
};

int main(int argc, char const* argv[]) {
    std::cout << "hello" << std::endl;
    return 0;
}
