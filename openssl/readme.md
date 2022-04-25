# OpenSSL

顾名思义，一个 Open 的 SSL 库

> 千万不要用 `std::string` 保存生成的 byte data ，写 OpenSSL 的 01 - 05 的时候没有注意这个问题，以后不会再用 `std::string` 了，如果是 byte array 以后都会用 `std::vector<unsigned char>` 了
