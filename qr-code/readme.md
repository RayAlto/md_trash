# QR 码

> - [QR Code Tutorial - Thonky.com](https://www.thonky.com/qr-code-tutorial/)

一种特殊的条形码，有四种标准化的编码模式：数字、字母数字、二进制、日文 (Shift JIS) 。

## 基本信息

尺寸也是版本， QR 码最小 21 x 21 像素，就是版本 1 ， 25 x 25 像素就是版本 2 ，最大到 177 x 177 像素，版本 40 。

QR 码使用里德-所罗门码实现纠错，过程中会产生额外的 bytes 用于错误纠正。有四个等级：

1. `L`: 7%
1. `M`: 15% ，常用
1. `Q`: 25%
1. `H`: 30%

容错等级越低、尺寸越大，能保存的数据越多。

## 生成 QR 码

1. [数据分析](./01.data-analysis.md "数据分析")
2. [数据编码](./02.data-encoding.md "数据编码")
3. [生成纠错码](./03.error-correction-coding.md "生成纠错码")
