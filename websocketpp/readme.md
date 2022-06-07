# WebSocket++

1. [客户端示例教程](./tutorial-utility-client.md)

一个 C++ 的 WebSocket 库，好像微软的 [cpprestsdk](https://github.com/microsoft/cpprestsdk) 的 WebSocket 支持也是封装了这个库，所以拿来学学。其实一开始为了减少项目的依赖，学了三天的 [libwebsockets](https://libwebsockets.org/) ，可惜实在是太难用了

---

重新看了看 libwebsockets ，其实设计的挺好的，只是我当时很着急再加上它文档太少，没有好好琢磨。各种看源码 + stackoverflow 后终于知道这个东西应该怎么用了，而且他的设计也确实不错（除了只接受一个 callback ，里面需要各种 switch + case ），可以看看[这一篇](../libwebsockets)。
