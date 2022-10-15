#include <cstddef>
#include <iostream>

/**
 * Queue
 * - 后进先出, LIFO
 */

template <typename T>
class Queue {
public:
    Queue() = default;
    Queue(const Queue&) = default;
    Queue(Queue&&) noexcept = default;
    Queue& operator=(const Queue&) = default;
    Queue& operator=(Queue&&) noexcept = default;
    virtual ~Queue() = default;

    void enqueue(T item);

    T dequeue();

    bool empty();

    std::size_t size();
};

int main(int argc, char const* argv[]) {
    std::cout << "hello" << std::endl;
    return 0;
}
