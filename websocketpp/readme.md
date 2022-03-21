# WebSocket++

1. [客户端示例教程](./tutorial-utility-client.md)

一个 C++ 的 WebSocket 库，好像微软的 [cpprestsdk](https://github.com/microsoft/cpprestsdk) 的 WebSocket 支持也是封装了这个库，所以拿来学学。其实一开始为了减少项目的依赖，学了三天的 [libwebsockets](https://libwebsockets.org/) ，可惜实在是太难用了:

```c++
while(lws_service(ws_context, 0) >= 0) {
    lws_callback_on_writable(wsi);
}
```

比如这段代码，是我从官方的一个 minimal example 和极其模糊的文档里学来的，这个循环可以不断调用我定义的 callback ，我可以在 callback 里接收、发送消息，然后官方告诉我说 callback 返回 `-1` 就可以关闭会话，然而在我的电脑 (ArchLinux ， libwebsockets 是用 pacman 安装的) 里这并不是 100% 会发生的事，有的时候（极少）返回 `-1` 可以让代码跳出上面的循环，然后去调用 lws_context_destroy 释放资源（我也不知道这是不是释放资源，官方的文档写的很模糊），有的时候（大多数时候）并不会这样，而是卡在循环里不出来，然后主线程走到头要结束程序了，这时这个循环所在的线程里 `lws_close_reason` 还没调用，一堆资源也没有释放，程序就这样结束了，服务器那边警告我刚才我整出了个 `abnormal closure` ， Valgrind 则告诉我刚才的一波操作泄露了将近 10Mib 的内存，还有 6Mib 多的内存是 still reachable 的，我只是写了个:

```c++
context_info.options = LWS_SERVER_OPTION_DO_SSL_GLOBAL_INIT;
```

让 libwebsockets 支持 SSL ，我寻思我这种程度的菜逼去封装 OpenSSL 也不至于整出这么多 still reachable 啊。哦对了，我如果要发送数据的话需要向它提供一个 `unsigned char*` 和 `size_t len` ，我寻思挺正常的，从 `std::string` 里 `copy` 一个出来就好了，简单写了一个、 `make` 、运行一气呵成，然后就是一个 `segmentation fault` ，我不理解， libwebsockets 自带的、牛逼的、带颜色的、无比详细的、默认启用的 logger 只打印了一堆我不 give 任何 fuck 的 shit ，完全没有给出任何有用信息，我以为是 `std::string` 的锅，直接搓了一个 `unsigned char*` 传进去就一切正常了，我以为我对了，但这个正常也是概率性的，有时还是会 `segmentation fault` ，我用了一下午翻它们的文档，终于找到了问题所在，它们规定我的 `unsigned char*` 前面必须有它们规定长度的多余空间，就像 `0000000000mydata` 这样，而且传入的 `unsigned char*` 必须从 `mydata` 开始，而不是从头开始，我不能接受，这样规定是能方便我还是能方便 libwebsockets ？

我不明白，可能我实在太菜逼了以至于我看不懂他们的文档和“minimal example（开篇定义一堆 struct ， callback 要放在一个奇妙的 struct 里，然后还把这个结构体放在了另一个 source file 里并美其名曰 plugin ，还要用 define 把它变成宏在主 souce file 里用）”，反正学 libwebsockets 这三天我是痛苦的，最后整出了个薛定谔的猫，my disappointment is immeasurable and my day is ruined。

这个库的 maintainer 在 Github Issue 里超级活跃，这一点我觉得还是很牛逼的，有这时间为啥不好好写写文档呢？
