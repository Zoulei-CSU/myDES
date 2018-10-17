# 简介
[myDES]是一个C++开发的使用DES加密方式，加密和解密文件的示例工程。


# 使用方法
`
Usage: myDES -e/-d key [input-file] [output-file] [-s]
         The key must be 8 bits.
         -e: Encryption         -d: Decryption.
         -s: Keep quiet and do not output any information.
`  

`
Example: myDES -e ABCDEFGH input.txt output.txt.des -s
         myDES -d ABCDEFGH output.txt.des output.txt
`


# 加密文件结构的说明
1.加密后的文件，开头8个字节是miagc字节，固定为下面的值。可以用这8个字节判断是不是需要的加密文件。
```cpp
static char magic[9] = {'S', 'G', 'D', 'E', 28, 30, 'S', 'P', '\0'};
```
这个miagc字节仅判别功能，可以自由修改为你需要的值。  

2.之后的8个字节，是一个整型数字的二进制值，用来记录原始文件的长度（用N表示 ）。因为DES加密的缘故，加密后的文件可能比原始文件长几个字节。  

3.再之后的内容，即是原始文件经过DES加密后的二进制值。只要把这些内容读出来，二进制解密，再取前N个字节（见上一步说明），即是原始文件。
