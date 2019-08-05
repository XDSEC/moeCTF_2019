# SM4
```openssl enc -in flag.bmp -out flag.bmp.enc -e -sm4-ecb -K ????????????????????????????????```

## 解法
其实这题和SM4并没有什么关系，国密算法还是挺安全的。

观察命令 **-sm4-ecb** 即以SM4算法加密，ECB模式进行分组。

ECB用起来可得当心，这种图片加上文件头就可能看出图片内容了。

[CTF-Wiki的解释](https://ctf-wiki.github.io/ctf-wiki/crypto/blockcipher/mode/ecb-zh/)

## 加文件头

这题难度大概就在这，文件大小在 1048576*3+54 字节左右，54是bmp的文件头长度， 1048576=1024\*1024 即像素数，剩下的那些误差是加密填充产生的

本题提供了个最简单最经典的 BMP 文件，图片大小需要依靠经验得出（暴力凑也行），除此之外有挺多因素会干扰 BMP 文件大小：每行像素的填充、BMP 调色板和压缩，详细请参阅 Wikipedia。
