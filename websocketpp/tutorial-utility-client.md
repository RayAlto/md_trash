# 客户端示例教程

我发现长篇大论的翻译官方的教程有点傻逼，我可以花十分钟读完那一篇教程，但让我翻译成恰当的中文我可能要花两个小时，所以 fuck it。我写了个更简单的例子，包含了连接到 WebSocket 服务器、发送 "hello" 、正常关闭对话，期间还可以输出所有来自服务器的信息：

- `websocketpp::client` 包含了一些基础配置，通过它可以创建很多 connection ，也可以通过它配置所有 connection 通用的选项
- connection 一旦被创建了就和 client 没有硬性联系了， client 里的配置会被复制进 connection 里，这时可以为每个 connection 配置的不同的选项，这时修改 client 的配置并不会在已经创建了的 connection 里生效。
- 每个 connection 都有一个 handler ，对 connection 的控制（比如发送消息，关闭连接等）都需要把这个 handler 作为参数，通过创建了这个 connection 的 client 的方法实现

```c++
// std::this_thread::sleep_for 要用
#include <chrono>
// stdout
#include <iostream>
// 智能指针
#include <memory>
// std::error_code
#include <system_error>
// WebSocket 运行在另一个线程
#include <thread>

// websocketpp::client
#include "websocketpp/client.hpp"
// websocketpp::config::asio_client 不支持 tls
#include "websocketpp/config/asio_no_tls_client.hpp"
// websocketpp::utility::to_hex 用于输出服务器传来的非文本消息
#include "websocketpp/utilities.hpp"

int main(int argc, char const* argv[]) {
    // 创建一个 client ，配置为 asio_client
    websocketpp::client<websocketpp::config::asio_client> ws_client;
    // WebSocket 需要运行在另一个线程
    std::shared_ptr<std::thread> ws_thread;
    // WebSocket++ 使用 std::error_code 表示错误，而不是抛出异常
    std::error_code ws_error;

    /* 先让 WebSocket++ 安静一点 */
    ws_client.clear_access_channels(websocketpp::log::alevel::all);
    ws_client.clear_error_channels(websocketpp::log::elevel::all);

    /* 让 WebSocket 服务在另一条线程运行 */
    ws_client.init_asio();
    // 这会使 ws_client 永远运行，即使所有连接都关闭了
    ws_client.start_perpetual();
    ws_thread = std::make_shared<std::thread>(
        &websocketpp::client<websocketpp::config::asio_client>::run,
        &ws_cient);

    /** 初始化一个连接（我在本地 8080 端口运行了一个 WebSocket echo server）
      *    使用获取到的 connection_ptr 并不是永远安全的，一般在调用了下面的
      *    get_connection() 之后，在调用了后面的 connect() 之前，使用这个 ptr
      *    对连接进行一些修改是安全的，比如下面 set_xxx_handler 为连接注册一些
      *    回调；或者在回调里获取、使用 connection_ptr 也是安全的
      */
    websocketpp::client<websocketpp::client::asio_client>::connection_ptr
        ws_connection =
            ws_client.get_connection("ws://127.0.0.1:8080", ws_error);
    if (ws_error) {
        std::cout << "连接初始化失败：" << ws_error.message()
                  << std::endl;
        return -1;
    }

    /** 获取连接的 handle ，这个 handle 基本上在任何地点，任何时间都是线程安全的
      *     也作为参数在回调里存在，如果想要封装成 class 的话把这个 handle 保存
      *     下来是一个明智的决定
      */
    websocketpp::connection_hdl ws_handle = ws_connection->get_handle();

    /** 通过 connection_ptr 注册回调
      *     这样注册的回调是独立于每一个 connection 的，如果想配置通用的回调
      *     可以通过 ws_client 进行配置
      *
      *     这些回调基本都只有一个 websocketpp::connection_hdl 作为参数，用
      *     与对当前连接进行控制，如果想要更灵活的调用可以使用 std::bind 或
      *     lambda 函数。
      */
    // 连接建立成功的回调
    ws_connection->set_open_handler([&](websocketpp::connection_hdl handle)
                                        -> void {
        std::cout << "Connected." << std::endl;
        // 通过 ws_client 以及 connection 的 handle 获取 connection_ptr
        websocketpp::client<websocketpp::config::asio_client>::connection_ptr
            connection = ws_client.get_con_from_hdl(handle);
        // 然后操作 connection_ptr 实现各种功能，比如这里输出服务器的名字
        std::cout << "Remote Server: "
                  << connection->get_response_header("Server") << std::endl;
    });
    // 连接失败的回调
    ws_connection->set_fail_handler([&](websocketpp::connection_hdl handle)
                                        -> void {
        std::cout << "Failed to connect" << std::endl;
        websocketpp::client<websocketpp::config::asio_client>::connection_ptr
            connection = ws_client.get_con_from_hdl(handle);
        std::cout << "Remote Server: "
                  << connection->get_response_header("Server") << std::endl;
    });
    // 连接关闭的回调
    ws_connection->set_close_handler([&](websocketpp::connection_hdl handle)
                                         -> void {
        std::cout << "Connection closed" << std::endl;
        websocketpp::client<websocketpp::config::asio_client>::connection_ptr
            connection = ws_client.get_con_from_hdl(handle);
        // 通过 connection_ptr 获取关闭的 status 以及 reason
        std::cout << "Close code: " << connection->get_remote_close_code()
                  << " ("
                  << websocketpp::close::status::get_string(
                         connection->get_remote_close_code())
                  << ")" << std::endl;
        std::cout << "Close reason: " << connection->get_remote_close_reason()
                  << std::endl;
    });
    // 接收消息的回调，这个回调除了 handle 还有一个 message_ptr ，用于获取消息
    ws_connection->set_message_handler(
        [&](websocketpp::connection_hdl handle,
            websocketpp::client<websocketpp::config::asio_client>::message_ptr
                message) -> void {
            std::cout << "Message received" << std::endl;
            // 获取消息的 opcode
            if (message->get_opcode() == websocketpp::frame::opcode::text) {
                // 是一个 UTF-8 的文本
                std::cout << "Text: " << message->get_payload() << std::endl;
            }
            else {
                // 并不是文本
                std::cout << "Binary: "
                          << websocketpp::utility::to_hex(
                                 message->get_payload())
                          << std::endl;
            }
        });

    /* 配置好了之后可以正式开始连接了 */
    ws_client.connect(ws_connection);
    // 为了避免发生奇怪的问题，小睡一会
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    /* 向服务端打个招呼 */
    ws_client.send(
        ws_handle, "hello!", websocketpp::frame::opcode::text, ws_error);
    if (ws_error) {
        std::cout << "打招呼失败了：" << ws_error.message() << std::endl;
    }
    // 为了避免发生奇怪的问题，小睡一会
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    /* 关闭连接 peacefully */
    ws_client.close(ws_handle, websocket::close::status::normal, "bye~");
    // 为了避免发生奇怪的问题，小睡一会
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    /* 关闭 client */
    // 停止服务
    ws_client.stop_perpetual();
    // 等待线程结束
    ws_thread.join();
    return 0;
}
```
