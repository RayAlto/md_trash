# 客户端示例教程

## 一、初始设置&基础知识

设置好基本的类型、打开和关闭连接、发送和接收信息。

### 开始

先整一个循环接收处理用户命令的程序，最后目标是给它整成能通过 WebSocket 从服务器那边获取信息的程序。

```c++
#include <iostream>
#include <string>

int main(int argc, char const* argv[]) {
    bool done = false;
    std::string input;

    while (!done) {
        std::cout << "Enter Command: ";
        std::getline(std::cin, input);

        if (input == "quit") {
            done = true;
        } else if (input == "help") {
            std::cout
                << "\nCommand List:\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        } else {
            std::cout << "Unrecognized Command" << std::endl;
        }
    }

    return 0;
}
```

### 加上 WebSocket++

WebSocket++ 有两个主要的对象类型，“endpoint”和“connection”， endpoint 创建并启动新的 connection 并维护这些 connection 的初始设置，还可以管理任何共享的网络资源。 connection 则保存每个 WebSocket 对话的信息

> 注意： connection 一旦启动了， endpoint 和这个 connection 就没有任何的链接了， endpoint 会把所有的初始设置复制进这个 connection 里。所以修改 endpoint 里的初始设置只会影响之后的 connection 。

connection 不会持有一个指向与它们关联的 endpoint 的链接。 endpoint 里也没有一个存放创建了的 connection 的列表，如果你想遍历这些 connection 的话，你得自己动手。
