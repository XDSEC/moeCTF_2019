---
title: moeCTF 2019 题解
date: 2019-09-06 18:23
tags:
	- CTF
	- 信息安全
categories: CTF
Author: Reverier
---

# 前言

好了,本蒟蒻要开始写题解了…

等到比赛结束了才放出噢!

<!--more-->

# 题解

## Sign In

### 你是西电新生吗?

签到题, 加入考试群, 在公告里面就可以发现`flag`, 复制, 提交, 一百分到手~

## Reverse

### Introducing RE

这道题... 就是教你怎么用`IDA`的..

在网上找来的`IDA`资源, ,然后安装,打开,发现了这么几句:

```assembly
mov     dword ptr [esp], offset aWelcomeToTheMo ; "Welcome to the MoeCTF!"
call    puts
mov     dword ptr [esp+17h], 63656F6Dh
mov     dword ptr [esp+1Bh], 447B6674h
mov     dword ptr [esp+1Fh], 6F595F30h
mov     dword ptr [esp+23h], 326B5F75h
mov     dword ptr [esp+27h], 495F776Fh
mov     dword ptr [esp+2Bh], 7D3F4144h
mov     byte ptr [esp+2Fh], 0
lea     eax, [esp+30h+var_19]
mov     [esp], eax      ; char *
call    sub_401500
```



然后找了个16进制转ASCII的网站, 复制第三行的 `63 65 6F 6D` 进去, 发现解出来是 `ceom` 

啊嘞?反过来不就是 `moec` 么?

按照这个思路, 挨个复制然后反过来输出, 就把 `flag` 找到了.

### Moe RE

这道题我本来是第二题做的,, 后来发现竟然比我想象中的难...

下载了`re`, 发现打不开, 就扔进`Windows`的`Linux`子系统里, 发现依旧打不开, 啊嘞? 什么情况? 不行我重启到`Arch Linux`试试? 算了我懒得费那个神... 直接扔进IDA, 发现汇编读不懂, 就按了下F5, 得到了以下伪代码:

```c
int __cdecl main(int argc, const char **argv, const char **envp)
{                   // 注释是后来自己添加的
  int v3; // eax
  int result; // eax
  int j; // [rsp+10h] [rbp-A0h]
  int i; // [rsp+14h] [rbp-9Ch]
  int v7; // [rsp+18h] [rbp-98h]
  __int64 v8; // [rsp+20h] [rbp-90h]
  char v9[104]; // [rsp+40h] [rbp-70h]
  __int64 v10; // [rsp+A8h] [rbp-8h]

  scanf("%s", v9, envp);   // 获取输入 v9
  v3 = strlen(v9);         // 获取输入长度
  v7 = v3;                 // 现在v3 == v7,都是长度
  strcpy((char *)&v8, "abcdefghijklmnopqrstuvwxyz"); // v8 好像是个 table
  for ( i = 0; i < v3; ++i ) 
      //遍历输入, 然后把v9里每个字符和table的第i个字符进行异或运算...
    v9[i] ^= *((_BYTE *)&v8 + i % 26); //*((_BYTE ... % 26)这句就相当于v8[i % 26]
  for ( j = 0; j < v7; ++j ) //输出v9里各个字符的数字
    printf("%d,", (unsigned int)v9[j]);
  result = 0;
  if ( __stack_chk_guard == v10 )
    result = 0;
  return result;
}
```

小小的研究一下源代码, 发现是个简单的算法, 具体如代码注释里写的那样, 于是写一个小程序破解之:

```C++
#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
    int x;
    int i = 0;
    char v[27] = "abcdefghijklmnopqrstuvwxyz";
    while (scanf("%d,", x))
    {
        char result = int(v[i % 26]) ^ x;
        cout << result << endl;
        i++;
    }
}
```

差不多就是把题目反着写了一遍, 然后运行, 把题目给的数字串输入进去,回车出`flag`.

### .pyc

啊嘞? `Python`难道不是解释型语言么??? ( 我见识太少了 [ 抱头痛哭 ] 

按照Bing上搜到的说法, 我就先装了个反编译`tool`:

```bash
$ pip install uncompyle
```

然后... 

```bash
$ uncompyle6 ./test.cpython-37.pyc > ./test.cpython-37.py
```

再然后就得到了以下代码, 官方说`uncompyle`只支持`Python2.x`, 所以搞出来的有bug, 不过差不多能理解:

```python
# uncompyle6 version 3.4.0
# Python bytecode 3.7 (3394)
# Decompiled from: Python 3.7.4 (tags/v3.7.4:e09359112e, Jul  8 2019, 20:34:20) [MSC v.1916 64 bit (AMD64)]
# Embedded file name: test.py
# Size of source mod 2**32: 294 bytes
from binascii import b2a_hex
from base64 import b32encode
x = input
y = print
if b2a_hex(b32encode(x().encode())).decode() == '4e5658574b5933554d5a3558413452544d4d59473234444a4e525557345a5a4e4b4234574758334447525846364d44514f51595732324c324d55575647344254474e5348323d3d3d':
    y('congrats')
# okay decompiling C:\\users\rever\Downloads\test.cpython-37.pyc
```

看见了一大串hex, 于是找了个网站转换之:

```
NVXWKY3UMZ5XA4RTMMYG24DJNRUW4ZZNKB4WGX3DGRXF6MDQOQYW22L2MUWVG4BTGNSH2===
```

根据源代码, 这是一份`base32`加密的玩意儿, 于是再找个网站解密得到`flag`:

```
moectf{pr3c0mpiling-Pyc_c4n_0pt1mize-Sp33d}
```

### Easy Shell

这个我说什么好咧.. 就是百度找了个`upx tool`,然后把题上给的`exe`扔了进去, 再把吐出来的东西扔进`IDA`... 发现这么一段:

```assembly
mov     dword ptr [esp], offset aWelcomeToTheMo ; "Welcome to the MoeCTF!"
call    puts
mov     dword ptr [esp+11h], 63656F6Dh
mov     dword ptr [esp+15h], 757B6674h
mov     dword ptr [esp+19h], 315F7870h
mov     dword ptr [esp+1Dh], 5F615F73h
mov     dword ptr [esp+21h], 646E314Bh
mov     dword ptr [esp+25h], 5F46305Fh
mov     dword ptr [esp+29h], 31326873h
mov     word ptr [esp+2Dh], 7D4Ch
mov     byte ptr [esp+2Fh], 0
lea     eax, [esp+30h+var_1F]
```

看到那个`63 65 6F 6D`我就明白了, 和`IntroducingRE`相同解法, 得到`flag`.

### Easy Debugger

这题是告诉你怎么用调试器的... 我懒, 就扔进`Visual Studio`开了个调试, 然后`flag`就自己蹦出来了... 没什么技术含量, 对吧...

### Easy Go

从这题开始, 我知道了, 所有写着Easy的题, 都是骗人的🙂一点都不Easy... 可能我菜是很大的原因吧……

还是相同的套路, 下载后扔进`IDA`, 然后看见了浩如烟海的函数... ( woc要不要这么刺激

费尽千辛万苦找到了main_main函数, 打开后看了眼汇编发现头疼, 果断F5:

```C++
__int64 __fastcall main_main(__int64 a1, __int64 a2, 
                             __int64 a3, __int64 a4, __int64 a5, __int64 a6)
{
  /* 一大堆变量声明,节省篇幅就不看了 */

  /* 对解题没什么用的函数 */
  fmt_Fscanln(a1, a2, (__int64)&v23, (__int64)&unk_4AAF60, v7, v8, 
              (__int64)&go_itab__os_File_io_Reader, os_Stdin);
  if ( *v19 == 1107LL )
  {
    runtime_convTstring(a1, a2, v9);
    *(_QWORD *)&v22 = &unk_4B0720;
    *((_QWORD *)&v22 + 1) = &v23;
    fmt_Fprintln(
      a1,
      a2,
      v12,
      (__int64)&go_itab__os_File_io_Writer,
      v13,
      v14,
      (__int64)&go_itab__os_File_io_Writer,
      os_Stdout);
  }
/* 后面一个else一个return,都不是重点 */
}
```

一不小心看到了代码里有一个`Fscanln`, 想着这肯定是读取输入, 得了, 分析一下, 不用再找`flag`了, 然后发现`if`语句里比较了`v19`和`1107LL`, 果断打开题目给的`exe`, 然后输入`1107`, 成功拿到`flag`! `flag: moectf{G0_1Anguage_1s_1nT3r3st1ng}`

### Java RE

给大佬递咖啡~ 诶,劳资咖啡咧, 好像丢了…

这道题, 用JD-GUI反编译了一下, 得到了一份狠长的代码:

```java
package qqq;

import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

public class Box implements ActionListener {
    /* 一堆变量声明 */
    public static boolean CHECK(int input) {
        if (input > 10000000 && input < 99999999) {
            int v7 = 1;
            int v8 = 10000000;
            int v3 = 1;
            if (Math.abs(input / 1000 % 100 - 80) == 3 && 
                input % 1000 % 927 == 0) {
                int v5 = 0;
                while (v5 < 4) {
                    if (input / v7 % 10 != input / v8 % 10) {
                        v3 = 0;
                        break;
                    }
                    v7 *= 10;
                    v8 /= 10;
                    v5++;
                }
                if (v3 != 1) {
                    return false;
                }
                if (v3 == 1) {
                    return true;
                }
            }
        }
        return false;
    }
    public Box() {
        /* UI设置, 对题目没什么用, 为省篇幅不列出了 */
    }
    public static void main(String[] args) {
    }
    public void actionPerformed(ActionEvent e) {
        /* 一些废话, 一堆if, 省篇幅就不粘贴进来了 */
        if (e.getSource() == this.bt) {
            if (CHECK(Integer.parseInt(this.a))) {
                this.tx.setText("moectf{" + (char) (Integer.parseInt(this.a) / 
                                                    1000000)
                        + (char) (Integer.parseInt(this.a) / 10000 % 100)
                        + (char) (Integer.parseInt(this.a) / 100 % 100) + 
                                "_he}");
            } else {
                this.tx.setText("clear and try again!");
            }
        }
        /* 和解题无关的处理 */
    }
}
```

我把源代码精简了一下, 以便看得更清楚点.

既然是一个GUI程序, 开始运行当然不能找`main`了.. 注意到题里有个`actionPerformed`, 好, 就从这个函数开始吧.. 然后在最后面看见了CHECK, 再调转头去看CHECK, 发现是一个检测输入的函数.

根据`if (input > 10000000 && input < 99999999)`知道输入是一个八位数, 接着看`if (Math.abs(input / 1000 % 100 - 80) == 3 && input % 1000 % 927 == 0)`知道了中间两位是83或者77 ( 第一次做的时候没看见abs函数,浪费了n久最后发现差点气得摔键盘 ) 最后3位是927.

```java
while (v5 < 4) {
    if (input / v7 % 10 != input / v8 % 10) {
        v3 = 0;
        break;
    }                
    v7 *= 10;         
    v8 /= 10;         
    v5++;               
}
```

这个循环是用来判断回文数字的, 我们已经知道了八位数的后五位是77927, 对称过去就是72977927.

然后回到`actionPerformed`函数, 发现这么几句:

```java
if (CHECK(Integer.parseInt(this.a))) {
    this.tx.setText("moectf{" + (char) (Integer.parseInt(this.a) / 1000000)
        + (char) (Integer.parseInt(this.a) / 10000 % 100)
        + (char) (Integer.parseInt(this.a) / 100 % 100) + "_he}");            
}
```

这个提取出来了72977927的前六位72, 97, 79并用ASCII解码, 然后把字符串拼起来..

出于懒, 写一小程序, 解之:

```C++
#include <iostream>
using namespace std;
int main() {
    char a = 72;
    char b = 97, c = 79;
    cout << "moectf{" << a << b << c << "_he}" << endl;
    return 0;
}
```

咖啡真好喝~

### Mine Sweep

这道题没什么好说的...我扫雷通关了...真逆向的话, 我还没有试过. ( 逃…

### Easy RE

有了对上面的Easy的体验我丝毫不敢觉得这题狠easy...果不其然, 扔进`IDA`之后我一脸蒙圈, 这是个什么玩意儿啊...

不管了, 找到了`main`, 然后F5, 得到以下东东:

```C
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  /* 变量声明 */
  v11 = 0;
  sub_4011E0(a1, a2, a3);
  v10 = 1;
  v4 = 4194587627529708148LL;
  v5 = 653654411009211005LL;
  v6 = 4502494060534902393LL;
  v7 = 1048127506;
  v8 = 12340;
  v9 = 77;
  printf(&byte_4040B0);
  sub_401270(&v4);
  sub_4012A0();
  return 0LL;
}
```

啊嘞? 这画风怎么这么奇怪? 我看了眼题目描述, 得, `AntiAntiDebug`我一准儿是不会了, 那就解码吧...

顺着函数找了好久

```C
signed __int64 __fastcall sub_401270(_BYTE *a1)
{
  *a1 = 109;
  sub_401240(byte_404080);
  return 5LL;
}
```

```C
int sub_4012A0()
{
  return printf(&byte_40409F);
}
```

这是`main`里面提到的两个函数, 分别看了下, 一个指向`byte_404080`, 一个指向`byte_40409F`

本以为是那些常用的编码的decode, 结果发现根本没有这些字串...于是, 我想到了`Moe RE`...

先找到了`byte_404080`, 在长下面这样:

```assembly
.data:404080 byte_404080     db 74h, 22h, 28h, 2Eh, 39h, 2Bh, 36h, 3Ah, 7Dh, 3Ah, 12h
.data:404080                                         ; DATA XREF: sub_401270+8↑o
.data:404080                                         ; sub_401360+96↑r ...
.data:404080                 db 3Eh, 39h, 3Fh, 12h, 9, 79h, 2Eh, 7Dh, 29h, 7Eh, 12h
.data:404080                 db 7Ch, 3Eh, 12h, 28h, 79h, 3Eh, 34h, 30h, 4Dh
```

按照`MoeRE`的思想, 我想着找个数来挨个异或一下试试..然后写了个小程序:

```C
#include <stdio.h>

int main(void)
{
    int v404080[] = {
        0x74, 0x22, 0x28, 0x2E, 0x39, 0x2B, 0x36, 0x3A, 0x7D, 0x3A,
        0x12, 0x3E, 0x39, 0x3F, 0x12, 0x09, 0x79, 0x2E, 0x7D, 0x29, 
        0x7E, 0x12, 0x7C, 0x3E, 0x12, 0x28, 0x79, 0x3E, 0x34, 0x30, 0x4D
    };
    int key = 77;
    int i = 0;
    int b;
    do{
        printf("%x", v404080[i] ^ key);
        i++;
        b = (i < 30);
    } while (b);
    return 0;
}
```

第一次试的时候, `key`用的是 `a1` 的 `109` , 然后发现不对...? 后来看了一眼`main`里面的`v4~v9`, 感觉太大的数怎么也不可能当`key`, 就拿`77`试了试... 然后运行了下`flag`就出来了...?

### Algorithm Task

这道题一看文件名叫hard就知道肯定不简单...

扔进`IDA`, 然后看到了一副宏伟壮观的程序跳转画面……

果断找到`main`函数按F5, 然后看见了`Decompiling`窗口卡了半天, 最后出来了下面的代码:

```C
__int64 __fastcall main(__int64 a1, char **a2, char **a3)
{
  /* 200多个变量声明 */
  v186 = 0;
  v184 = 0;
  v187 = 0;
  v175 = 1093207085;
  /* 5个嵌套的 while(1) */
              
             /* 一大堆不知所以的计算过程 */
             /* 还有仨Wrong Flag的判定 */ 
      
    if ( v175 == -866985480 )
    {
      a2 = (char **)"dcba3261b6ef0d77";
      v107 = strncmp(s1, "dcba3261b6ef0d77", 0x10uLL);
      v108 = 1750495256; // 找到第一个字符串, 盲猜是MD5加密
      if ( v107 )
        v108 = 402522278;
      v175 = v108;
    }
    // 一大堆else if,并不是很能看懂在干什么
    else if ( v175 == 184885918 )
    {
      puts("Please input the flag:\n"); // 然后看见了输入
      a2 = (char **)&s2;
      __isoc99_scanf("%42s", &s2);
      v188 = strncmp("moectf{", &s2, 7uLL) != 0;// 前缀不参与
      /* 另一大堆不明所以的加密 */
    else if ( v175 == 233838060 )
    {
      a2 = (char **)sub_630390(&v183, a2, a3);
      v189 = strcmp((const char *)(unsigned int)"X1I0X0YxYWdfWTB1XzRyZV9TdHIwbmd9", (const char *)a2) != 0;
      a3 = (char **)0xFFFFFFFFLL;
      /* 又是浩如烟海的看不懂的加密过程... */
      }
    }
  }
  getchar();
  return 0LL;
}
```

在源代码中看见了`dcba3261b6ef0d77`和`X1I0X0YxYWdfWTB1XzRyZV9TdHIwbmd9`两串可疑的东东, 前面那串要么是`MD5`要么是`SHA1`, 后面那串肯定是`Base`系列的, 根据题目给的信息, 本题仅用了两种常见算法, 基本可以确定把俩解出来的字符串拼起来前面加上`moectf{`就OK了.

在网上找个工具成功解出`flag`: `moectf{enj0y_R4_F1ag_Y0u_4re_Str0ng}`

### Easy C++

由于得到了我大哥的帮助, 我算是成功的解出来了这道题.. 由于写WP的环境换到了Linux, 就简单的讲一下这道题的思路吧.. 

这道题的`flag`: `moectf{CPP_BaSE64_CaeS@r_1S_s0_eaaaasy}`

做题思路: 经过我大哥`Apache553`的努力, 把IDA中所有的函数全部识别了出来, 这道题才得以破解. 用`OllyDebug`调试过程中找到字符串比较的函数的汇编代码然后跟进, 可以在堆栈中发现一串base64, 应该是对应的密文. 通过`Apache553`的工程文件大概得知这是使用移位的方式构建了一个新的`table`, 于是写脚本循环构建`table`, 最终将`flag`爆破了出来. ( 我挺想写详细过程的, 但是Windows找不到显卡了开不了机, 就只能先凑合了... )

## Programming

### Easy PPC

读了下题目给的代码, 大概懂了意思之后, 写了一段小程序, 读取文件, 然后把数字提取出来:

```c++
#include <iostream>
using namespace std;

int main(){
    freopen("flag.txt", "r", stdin);
    char x;
    while(cin >> x)
        if(isdigit(x)) cout << x;
    return 0;
}
```

得到了这么一串数字: `109111101991161021231128911610448110957811184956511097994811010064125`

然后工具人基因觉醒, 手动分类, 分成`ASCII`应该有的样子:

`109 111 101 99 116 102 123 112 89 116 104 48 110 95 78 111 84 95 65 110 97 99 48 110 100 64 125`

然后再写一个程序:

```c++
#include <iostream>
using namespace std;

int x;
int main(){
    while(cin >> x){
        putchar(x);
    }
}
```

就是无脑把`x`当成`char`来输出..

把刚分好类的数字粘贴进去, 最后得到`flag`: `moectf{pYth0n_NoT_Anac0nd@}`

### w1nd牛逼！

拿到这题, 面无表情的解压, 面无表情的用`Visual Studio Code`打开文件夹, 面无表情的点开在文件中搜索, 面无表情的输入`w1ndNiuBi`, 面无表情的打开全字匹配的开关, 面无表情的把总数扔进在线base64编码, 得到结果`moectf{NjMyNA==}`, 面无表情的提交... ( 好没意思的题 ( 溜了溜了

### A Template Problem

这个题看着只有一百分我却写了好久好久… 仿佛又回到了以前写NOIP却怎么也写不出来只能百度求助而对着求助来的代码不知所措的年代😭

这题要用到KMP算法...什么是KMP算法咧? 就是一个快速的模式串匹配算法...

啥又是模式串匹配?

模式串匹配, 就是给定一个需要处理的字符串 ( 会超级超级长 ) 和一个需要在文本串中搜索的模式串 ( 理论上长度应该远远小于需要处理的字符串, 否则没法玩了... ) , 查询在该文本串中, 给出的模式串是否出现, 出现的次数, 出现的位置等等等问题.

为啥要叫KMP?

> 因为有三位伟大的科学家共同设计完成……分别是`D.E.Knuth` \& `J.H.Morris` & `V.R.Pratt`

然而我并不需要知道他们都是谁谁谁...只需要知道这是个很流批的算法就好了..

从洛谷学来的:

> 首先要理解，朴素的单模式串匹配大概就是枚举每一个文本串元素，然后从这一位开始不断向后比较，每次比较失败之后都要从头开始重新比对，大概期望时间复杂度在 θ(n+m) 左右，对于一般的弱数据还是阔以跑的了滴。但是其实是可以被卡成O(nm)的。emmmm并且还是比较容易卡的。
>
> 而 KMP的精髓在于，对于每次失配之后，我都不会从头重新开始枚举，而是根据我已经得知的数据，从某个特定的位置开始匹配；而对于模式串的每一位，都有**唯一**的“特定变化位置”，这个在失配之后的特定变化位置可以帮助我们利用已有的数据不用从头匹配，从而节约时间。
>
> 比如我们考虑一组样例：
>
> ```cpp
> 模式串：abcab
> 文本串：abcacababcab
> ```
>
> 首先，前四位按位匹配成功，遇到第五位不同，而这时，我们选择将abcab向右移三位，或者可以直接理解为移动到模式串中与失配字符相同的那一位。可以简单地理解为，我们将两个已经遍历过的模式串字符重合，导致我们可以不用一位一位地移动，而是根据相同的字符来实现快速移动。
>
> ```cpp
> 模式串：   abcab
> 文本串：abcacababcab
> ```
>
> 但有时不光只会有单个字符重复：
>
> ```cpp
> 模式串：abcabc
> 文本串：abcabdababcabc
> ```
>
> 当我们发现在第六位失配时，我们可以将模式串的第一二位移动到第四五位，因为它们相同 .
>
> ```cpp
> 模式串：   abcabc
> 文本串：abcabdababcabc
> ```
>
> 那么现在已经很明了了， KMP 的重头戏就在于用失配数组来确定当某一位失配时，我们可以将前一位跳跃到之前匹配过的某一位。而此处有几个先决条件需要理解：
>
> 1、**我们的失配数组应当建立在模式串意义下，而不是文本串意义下**。因为显然模式串要更加灵活，在失配后换位时，更灵活简便地处理。
>
> 2、如何确定位置呢？
>
> 首先我们要明白，基于先决条件11而言，我们在预处理时应当考虑当**模式串**的第 i位失配时，应当跳转到哪里.因为在文本串中，之前匹配过的所有字符已经没有用了——都是匹配完成或者已经失配的，所以我们的 kmp 数组（即是用于确定失配后变化位置的数组，下同）应当记录的是：
>
> **在模式串 str1 中，对于每一位 str1[i],它的 kmp 数组应当是记录一个位置 j, j ≤ i 并且满足 str1[i]=str1[j] 并且在 j != 1 时理应满足 str1[1] 至 str1[j - 1] 分别与 str[i - j + 1] ~str1[i - 1] 按位相等**
>
> 上述即为移位法则
>
> 3、从前缀后缀来解释 `KMP` :
>
> 首先解释前后缀(因为太简单就不解释了 )：
>
> ```cpp
> 给定串：ABCABA
> 前缀：A,AB,ABC,ABCA,ABCAB,ABCABA
> 后缀：A,BA,ABA,CABA,BCABA,ABCABA
> ```
>
> 其实刚才的移位法则就是对于模式串的每个前缀而言，用 `kmp` 数组记录到它为止的**模式串前缀的真前缀和真后缀最大相同的位置**（注意，这个地方没有写错，是真的有嵌套）。然而这个地方我们要考虑“**模式串前缀**的前缀和后缀最大相同的位置”原因在于，我们需要用到 `kmp`数组换位时，当且仅当未完全匹配。所以我们的操作只是针对模式串的前缀−−毕竟是失配函数，失配之后只有可能是某个部分前缀需要“快速移动”。所以这就可以解释 `KMP`中前后缀应用的一个特点：
>
> `KMP`中前后缀不包括模式串本身,即**只考虑真前缀和真后缀**,因为模式串本身需要整体考虑，当且仅当匹配完整个串之后；而匹配完整个串不就完成匹配了吗...

这个我觉得很详细了...那怎么根据`KMP`算法写代码呢..? ( 我觉得编程题的WP最难写, 还要写`TreeDistance`... )

先把代码贴出来:

```c++
#include <stdio.h>
#include <string.h>
char S[1000000]="",T[1000000]="";
int next[100000];
void Next(char*T,int *next){
    memset(next,0,strlen(T));   // 初始化动态数组,将其长度设置为0
    int size = strlen(T);       // 把next数组的长度扩展到和T的长度一致
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < strlen(T); i++)
    {
        while (j > -1 && T[j + 1] != T[i])
            j = next[j];
        if (T[j + 1] == T[i])
            j++;
        next[i] = j;
    }
}
int KMP(char * S,char * T,int i){
    int cnt = 0;    // count的缩写
    Next(T, next);
    int j = -1;
    int slen = strlen(S);
    int tlen = strlen(T);
    for (int i = 0; i < slen; ++i)
    {
        while (j > -1 && T[j + 1] != S[i])
            j = next[j];
        if (T[j + 1] == S[i])
            ++j;
        if (j == tlen - 1)
        {
            printf("%d ",i - tlen + 2);
            ++cnt;
            j = next[j];
        }
    }
}

int main() {
	scanf("%s",S);
	scanf("%s",T);
    KMP(S,T,1);
    //printf("%d ",i);
	//system("pause");
    return 0;
}
```

woc... 我不想写了... 代码原理已经放出来了,, 接下来的看代码吧... 

### Perfect Repeater

如果我能做出来我再写... 我还做不出来

### Frank NB!

我写这道题的时候... 差点就当了工具人... 不过还好有工具…. Frank NB! Visual Studio Code NB!

下载完题目给的压缩包, 然后解压, 然后进入文件夹, 然后右键在 V S Code 中打开, 然后点击左侧的放大镜, 然后输入 `^[a-zA-Z][0-9]{3,5}[~!@#$%^&*()_+][A-Za-z]{0,8}$`, 然后回车搜索…

WD**D咋不对啊..?!

噢噢还得排除一下`FrankNB?`的文件...

工具人基因觉醒!

手动删掉了所有`FrankNB?`之后, 终于获取了正确的数, 然后`SHA256`算一遍之后拿到`flag`…

### Random Encode

这题读了读代码, 发现还真就是随机加密...

```python
from random import Random
from base64 import *
from flag import flag

r = Random()
EncoderSet = [a85encode,b16encode,b32encode,b64encode,b85encode]

for i in range(r.randrange(30,35)):
    Encoder = r.choice(EncoderSet)
    flag = r.choice(EncoderSet)(str(EncoderSet.index(Encoder)).encode()) + \
            b'w1ndNB' + Encoder(flag)

with open('secret.txt','wb') as out:
    out.write(flag)
```

发现脚本应该是把正确的`flag`随机选加密方式加密了30多层, 然后就产生了一个40多MB的大家伙... 我忽然产生了一个想法, 既然有随机加密算法选择的提示, 那我何不把每种算法的提示头都算出来, 然后每解密一次, 就读个头然后查表, 对应解密呢?

然后就有了一个小脚本:

```python
from random import Random
from base64 import *

r = Random()
EncoderSet = [a85encode,b16encode,b32encode,b64encode,b85encode]
for i in EncoderSet:
    print(r.choice(EncoderSet)(str(EncoderSet.index(i)).encode()))
```

然后运行这个脚本N次之后, 统计得出所有加密方式可能出现的文件头:

```python
a85 = [b'Fa', b'0E', b'MA==', b'30', b'GA======']
b16 = [b'F#', b'0`', b'MQ==', b'31', b'GE======']
b32 = [b'G5', b'1&', b'Mg==', b'32', b'GI======']
b64 = [b'GX', b'1B', b'Mw==', b'33', b'GM======']
b85 = [b'Gy', b'1]', b'NA==', b'34', b'GQ======']
```

然后写了个脚本:

```python
from base64 import *

a85 = [b'Fa', b'0E', b'MA==', b'30', b'GA======']
b16 = [b'F#', b'0`', b'MQ==', b'31', b'GE======']
b32 = [b'G5', b'1&', b'Mg==', b'32', b'GI======']
b64 = [b'GX', b'1B', b'Mw==', b'33', b'GM======']
b85 = [b'Gy', b'1]', b'NA==', b'34', b'GQ======']

EncoderSet = [a85decode, b16decode, b32decode, b64decode, b85decode]
point = 0

while point != -1:
    f = open('.\\secret.txt', 'rb')

    s = f.read()
    point = -1
    n = s.find(b'w1ndNB')
    print(s[0:n])
    x = s[0:n]
    if s[0:n] in a85:
        point = 0
    if s[0:n] in b16:
        point = 1
    if s[0:n] in b32:
        point = 2
    if s[0:n] in b64:
        point = 3
    if s[0:n] in b85:
        point = 4
    else:
        point = -1
        print('ERROR OR SUCCESS!')
        exit()
    with open('secret.txt','w') as out:
        out.write(EncoderSet[point](s[n+6:]).decode())

```

然后!!! 我就迷茫了... 无论如何都匹配不上.. 循环只执行一遍不做任何处理就会退出..

于是... 怎么能放弃呢?!

我就改动了一下, 把循环去掉, 然后人眼识别, 手动修改解码方式和位置... 手撕了三十一层, 得到`flag`.

### Tree Distance

想让我写算法解释吗? 不可能的... 我还想多活几年... 我把代码放出来吧... 

算法是倍增求LCA, 可以百度了解一下.

( 其实本题最开始是网络版的, 网络版数据简单得多并且没有时间限制, 可惜我不会网络编程, 于是就走上了OJ这条不归之路 T_T , 数据太坑人了 )

```C++
// 再过不了我就换地方重写QAQ
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 5e5;
const int maxm = 8e5;
struct node {
    int to, next, w;
} edges[maxm];
int head[maxn], cnt, dp[maxn][20], dep[maxn], dist[maxn];

void addedge(int u, int v, int w) {
    edges[cnt].to = v;
    edges[cnt + 1].to = u;
    edges[cnt].w = edges[cnt + 1].w = w;
    edges[cnt].next = head[u];
    edges[cnt + 1].next = head[v];
    head[u] = cnt++;
    head[v] = cnt++;
}

void dfs(int s, int x) {
    dep[s] = dep[x] + 1;
    dp[s][0] = x;
    int t;
    for (int i = 1; (1 << i) <= dep[s]; i++)
        dp[s][i] = dp[dp[s][i - 1]][i - 1];
    for (int i = head[s]; i != -1; i = edges[i].next) {
        t = edges[i].to;
        if (t == x) continue;
        dist[t] = dist[s] + edges[i].w;
        dfs(t, s);
    }
}

int LCA(int u, int v) {
    if (dep[v] > dep[u])
        u ^= v ^= u ^= v;
    for (int i = 20; i >= 0; i--) {
        if ((1 << i) <= (dep[u] - dep[v])) {
            u = dp[u][i];
        }
    }
    if (u == v) return u;
    for (int i = 20; i >= 0; i--) {
        if ((1 << i) <= dep[u] && (dp[u][i] != dp[v][i])) {
            u = dp[u][i];
            v = dp[v][i];
        }
    }
    return dp[u][0];
}

int WDNMD(int u, int v) {
    int z = LCA(u, v);
    return dist[u] - 2 * dist[z] + dist[v];
}

int main() {
    int n, m, u, v, w;
    scanf("%d%d", &n, &m);
    cnt = 0;
    memset(head, -1, sizeof(head));
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &u, &v, &w);
        addedge(u, v, w); // 强行无向...
    }
    dep[1] = 0;
    dp[1][0] = 1;
    dfs(1, 1);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &u, &v);
        printf("%d\n", WDNMD(u, v));
    }
    return 0;
}
```

### F1@g‘s diamond

代码一扔我就溜~

算法是线段树, 区间维护.

```C++
#include<cstdio>
#include <cstring>
#include<iostream>

using namespace std;
typedef long long LL;
const int INF = 1e9 + 7, MAXN = 5e5 + 10, MAXNODE = MAXN << 2, MAXM = 1e5 + 10;
int N, M;
LL tmp[MAXN];

struct node {
    LL sum, maxl, maxr, maxv;

    node() {
        sum = maxl = maxr = maxv = 0;
    }
} A[MAXNODE];

inline void push_up(int x) {
    A[x].sum = A[x << 1].sum + A[x << 1 | 1].sum;
    A[x].maxl = max(A[x << 1].maxl, A[x << 1].sum + A[x << 1 | 1].maxl);
    A[x].maxv = max(A[x << 1].maxr + A[x << 1 | 1].maxl, max(A[x << 1].maxv, A[x << 1 | 1].maxv));
    A[x].maxr = max(A[x << 1 | 1].maxr, A[x << 1].maxr + A[x << 1 | 1].sum);
}

void init(int x, int l, int r) {
    if (l == r) {
        A[x].sum = A[x].maxl = A[x].maxr = A[x].maxv = tmp[l];
        return;
    }
    int mid = (l + r) >> 1;
    init(x << 1, l, mid);
    init(x << 1 | 1, mid + 1, r);
    push_up(x);
}

void update(int x, int l, int r, int q, LL c) {
    if (l == r) {
        if (l == q)
            A[x].sum = A[x].maxl = A[x].maxr = A[x].maxv = c;
        return;
    }
    int mid = (l + r) >> 1;
    if (q <= mid)
        update(x << 1, l, mid, q, c);
    else
        update(x << 1 | 1, mid + 1, r, q, c);
    push_up(x);
}

node query(int x, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
        return A[x];
    }
    int mid = (l + r) >> 1;
    if (qr <= mid)
        return query(x << 1, l, mid, ql, qr);
    if (ql > mid)
        return query(x << 1 | 1, mid + 1, r, ql, qr);
    node left = query(x << 1, l, mid, ql, qr), right = query(x << 1 | 1, mid + 1, r, ql, qr), ret;
    ret.maxv = max(left.maxr + right.maxl, max(left.maxv, right.maxv));
    ret.maxl = max(left.maxl, left.sum + right.maxl);
    ret.maxr = max(right.maxr, left.maxr + right.sum);
    return ret;
}

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 1; i <= N; i++)
        scanf("%lld", tmp + i);
    init(1, 1, N);
    int ii, jj, kk;
    LL ll;
    for (int i = 1; i <= M; i++) {
        ii = 1;
        if (ii == 1) {
            scanf("%d%d", &jj, &kk);
            if (jj > kk)
                swap(jj, kk);
            printf("%lld\n", query(1, 1, N, jj, kk).maxv);
        } else {
            scanf("%d%lld", &jj, &ll);
            update(1, 1, N, jj, ll);
        }
    }
    return 0;
}
```

## Crypto

### Pigpen Cipher

这个是猪圈密码, 从必应上可以搜到猪圈密码的密码表, 对着破解就可以了.

### Rail fence cipher

```
mthAf2p_anf@ccta}ofEi3_hl_d_sar0pe{_Lncesk_cslyghctr_c12_i0li_pry
```

栅栏密码, 必应了解了一下, 发现分组, 然后就找了一下o, 通过o的判断发现分组的奥妙:

```
mthAf2p_anf@ccta}
ofEi3_hl_d_sar0p
e{_Lncesk_cslygh
ctr_c12_i0li_pry
```

然后竖着读就可以找到`flag`啦. `flag`: `moectf{thE_rAiL_f3nc2_c1phe2_ls_a_kind_0f_cl@ssical_crypt0graphy}`

### Bacon’s Cipher

```
AqCEclcIZQjbecyOhgXSwOdveKjpYyaeknUkyokazpyUnhFDSmvQEvCdmoFsfAvfyvTQFWkyBNIojUddNbtmT
```

这道题居然是以大小写来隐藏信息的!!!

然后就有了下面这个程序:

```c++
#include <iostream>
#include <cctype>
using namespace std;
int main () {
    char x;
    while(cin >> x) {
        if(isupper(x)) cout << 0;
        else cout << 1;
    }
}
```

运行一下, 得到了一串二进制: `0100111000111110110010111011011111011111111011000110010111011011110000110001101101110`

手动分割一下:

`01001 11000 11111 01100 10111 01101 11110 11111 11101 10001 10010 11101 10111 10000 11000 11011 01110`

发现解密的不对! `11111`太夸张了...然后改一下代码,

```c++
#include <iostream>
#include <cctype>
using namespace std;
int main () {
    char x;
    while(cin >> x) {
        if(isupper(x)) cout << 1;
        else cout << 0;
    }
}
```

再运行, 得到了另一串二进制 ( 其实就是上面的结果的按位非运算 )

`10110 00111 00000 10011 01000 10010 00001 00000 00010 01110 01101 00010 01000 01111 00111 00100 10001`, 对着字母序号表解出`flag`.

### Frequency analysis?

一看题目, 频率分析啊... 我不能当工具人! 于是写一程序:

```c++
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

int main()
{
    freopen(".\\chars.txt", "r", stdin);
    freopen(".\\frequentre.txt", "w", stdout);
    map<char, int> sign;
    string input;
    string types;
    cin >> input;
    for(int i = 0; i < input.length(); i++)
    {
        if (types.find(input[i])==string::npos)
            types += input[i];
        sign[input[i]]++;
    }
    sort(types.begin(), types.end());
    double total = input.length();
    double frequent;

    for (int i = 0; i < types.length(); i++)
    {
        frequent = double(sign[types[i]]) / total;
        cout << types[i] << ": " << frequent << "%\n";
    }
    return 0;
}
```

然后打开结果的文件, 再复制拖到`Excel`里面, 然后根据频率大小排序, 然后从上往下读就得到`flag`了...

### MD5

必应, 找一网站, 复制粘贴, 查询之, 得`flag`.

### Columnar Transposition

>维基百科对列移位密码的解释如下:
>
>#### Columnar transposition
>
>In a columnar transposition, the message is written out in rows of a fixed length, and then read out again column by column, and the columns are chosen in some scrambled order. Both the width of the rows and the permutation of the columns are usually defined by a keyword. For example, the keyword `ZEBRAS` is of length 6 (so the rows are of length 6), and the permutation is defined by the alphabetical order of the letters in the keyword. In this case, the order would be "6 3 2 4 1 5".
>
>In a regular columnar transposition cipher, any spare spaces are filled with nulls; in an irregular columnar transposition cipher, the spaces are left blank. Finally, the message is read off in columns, in the order specified by the keyword. For example, suppose we use the keyword `ZEBRAS` and the message `WE ARE DISCOVERED. FLEE AT ONCE`. In a regular columnar transposition, we write this into the grid as follows:
>
>```
>6 3 2 4 1 5
>W E A R E D
>I S C O V E 
>R E D F L E 
>E A T O N C 
>E Q K J E U 
>```
>
>providing five nulls (`QKJEU`), these letters can be randomly selected as they just fill out the incomplete columns and are not part of the message. The ciphertext is then read off as:
>
>```
>EVLNE ACDTK ESEAQ ROFOJ DEECU WIREE
>```
>
>In the irregular case, the columns are not completed by nulls:
>
>```
>6 3 2 4 1 5
>W E A R E D 
>I S C O V E 
>R E D F L E 
>E A T O N C 
>E 
>```
>
>This results in the following ciphertext:
>
>```
>EVLNA CDTES EAROF ODEEC WIREE
>```
>
>To decipher it, the recipient has to work out the column lengths by dividing the message length by the key length. Then he can write the message out in columns again, then re-order the columns by reforming the key word.
>
>In a variation, the message is blocked into segments that are the key length long and to each segment the same permutation (given by the key) is applied. This is equivalent to a columnar transposition where the read-out is by rows instead of columns.
>
>Columnar transposition continued to be used for serious purposes as a component of more complex ciphers at least into the 1950s.

不过这题有很大的坑... 就是解密顺序和加密是反着来的.. 我之前搞了好久都搞不出来... 按照Wiki分组重排, 成功拿到`flag`.

### Easy RSA

这道题我研究了好久... 最后在线分解大数找到p和q, 然后bing搜来的脚本修改一下跑一遍就过了...

```python
#coding=utf-8
import math
import sys
from Crypto.PublicKey import RSA
arsa=RSA.generate(1024)
arsa.p=296173636181072725338746212384476813557
arsa.q=336771668019607304680919844592337860739
arsa.e=65537
arsa.n=arsa.p*arsa.q
Fn=long((arsa.p-1)*(arsa.q-1))
i=1
while(True):
    x=(Fn*i)+1
    if(x%arsa.e==0):
           arsa.d=x/arsa.e
           break
    i=i+1
private=open('private.pem','w')
private.write(arsa.exportKey())
private.close()
```

拿到私钥之后, 随便用个什么方法, openssl也好, 在线解密也好, 反正就出来了.

### Hill Cipher

这题我真的是写到地老天荒...

拿到题之后先找了无数个网站发现解不了, 就自己研究了一下, 发现矩阵求逆然后和密文求点积, 于是我就打开微软的`Mathematics`算了一年得到了输出, 然后写一程序手动输入弄出`flag`...

具体情况呢, 就是题目给了个矩阵密钥, 先求逆, 然后存下来和分好组的密文挨个求点积, 最后输出结果时, 把小数部分直接舍掉就行了, 然后输入下面的程序里开始查表.

```c++
#include <iostream>
using namespace std;

int main(){
    string table = "abijklQRSTUVWXmnop@#$%wxyzABCDcdefghEFGHI&*()_+JKLMNOPYZ01234qrstuv56789!^-=";
    while(true){
        double y;
        cin >> y;
        int x = int(y);
        x %= table.length();
        if(x <= 0)
            x += table.length();
        cout << table[x];
    }
}
// 算出来的明文长这样, 注意要竖着输进去
// 49 0  5  7  8  56 57 28
// 57 62 34 0  45 52 33 65
// 15 45 58 45 63 45 33 49
// 58 26 1  57 16 29 2  64
```

`flag`: `moectf{L1n2ar_Alg2bRa_1S_so0O_D1ffiCuLt}`

## Web

### GET

浏览器打开`http://39.108.11.206:10002/?a`拿到`flag`.

### POST

去网上找了个叫`HackBar`的东西, 然后就`post`了...

不过后来用脚本的办法, 拓展性高一点:

```python
import requests
datas = {'a'}
r = requests.post("http://39.108.11.206:10001/", data=datas)
print(r.text)
print(r.status_code)
```

### Introducing Web

打开网页, 然后按F12, 然后..就没有然后了..

### Easy Limitation

打开网页, 保存到本地, 打开HTML, 把下面这句:

```html
<input class="form-control" type="text" name="key" maxlength="14" placeholder="只需要输入msc_1s_Gre@t即可获取flag">
```

里的`maxlength`改成15或者更大的数, 然后本地浏览器打开改好的html, 输入, 提交, 拿到`flag`.

### Procotol

从php的官方文档里读了好久...然后拼出来这么一句:

```
http://39.108.11.206:10003/?file=php://filter/read=convert.base64-encode/resource=./index.php
```

浏览器打开后能看到一串`base64`串, 复制下来解码:

```php+HTML
<?php
error_reporting(0);
echo '<p>the flag was put in the index.php, can you get it?</p>';


$file=$_GET['file'];
include($file);
//moectf{YoU_g0t_f1@g}
?>
```

然后就拿到`flag`了...

说来这种把源码换成`base64`再输出防止被执行的方法真骚啊..

### Restrictions

搜索引擎会读取站点下的`robots.txt`来判断爬取哪些页面. 然后我们打开`https://moectf.cn/robots.txt`, 发现提示有什么脚本被执行了删掉了`flag`...

打开设置禁用JS脚本, 刷新网页, F12, 在源代码里看见`flag`...

### 是时候展示十八年单身的手速了

这道题要用到`WireShark`...然后点开WireShark, 打开端口然后刷新页面, 然后在捕获的列表里面找一个HTTP 302, 然后双击查看详细信息, 就能找到`flag`了.

### 英国人

这道题很秀…. 用`nslookuptool`的在线查询网站可以查到`region.challenge.moectf.cn`的全球`dns`信息, 然后找到了域名在英国被解析的地址, 然后修改一下`hosts`, 唱跳rap篮球+F5, 就拿到`flag`了.

### Amazing_Eval

了解了一下`eval()`函数..

然后打开`http://39.108.11.206:10006/?cmd=‘echo “$flag”’`就好了.

### 今天你备份了嘛

这道题上网必应了一下, 然后打开`http://39.108.11.206:10011/index.php.swp`, 就拿到`flag`了.

### PHP 弱类型

我真的想吐槽PHP不愧是被骂成全世界最懒烂的语言...

`http://39.108.11.206:10005/?a="0”`

php判断相等时, 字符串会被解释成0. 打开上面网址拿到`flag`.

### PHP_md5()

哇塞php是真的不安全...必应了一下php的MD5漏洞, 然后打开`http://39.108.11.206:10007/?username=240610708&passwd=QNKCDZO`, 就拿到了`flag`: `moectf{You_UnderStAnd_mD5_betTer!}`

这是因为`240610708`和`QNKCDZO`的MD5()计算结果竟然是一样的!

### 神奇的正则表达式

小小学了下正则表达式, 然后改了一下之前post用的脚本:

```python
import requests
datas = {'key':"aflagdddd/6/:skey"}
r = requests.post("http://39.108.11.206:10009/", data=datas)
print(r.text)
print(r.status_code)
```

成功通过.

### 头

这题真的狠...算了要文明...

用`curl`连试了好几次终于过了:

```bash
$ curl --header "Cookie: login=true" --header "User-Agent: PowerPC" --header "Accept: application/flag" -v -i http://47.101.32.101:10010/
```

就是按照网页的提示改HTTP请求头就好了.

`flag`: `moectf{M0m_I_c4n_m0dify_HTTP_H3aders!}`

这个`flag`写的也让人很想吐槽....

### stronger_php

这个竟然判断md5==sha1…....

用数组绕过, 浏览器打开`http://39.108.11.206:10008/?a[]&b[]=123123`

得到`flag`: `moectf{Y0u_can_st1ll_defeat_m3}`

### 终极HTTP请求头

我!!!!! 想杀人...

先挂出来我的狗血历程🙃:

```bash
## 上面省略2232行尝试的代码
rever@DS-10001-RX MINGW64 ~
$ curl --header "Referer: www.xidian.edu.cn" --header "User-Agent: moectf_browser" --header "X-Forwarded-For: 127.0.0.1" --header "Cookie: xduer" --header "Accept: PHP" --header "Accept-Encoding: UTF-8" --header "Accept-Language: zh-CN" -v -i http://39.108.11.206:10012/
*   Trying 39.108.11.206...
* TCP_NODELAY set
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
  0     0    0     0    0     0      0      0 --:--:-- --:--:-- --:--:--     0* Connected to 39.108.11.206 (39.108.11.206) port 10012 (#0)
> GET / HTTP/1.1
> Host: 39.108.11.206:10012
> Referer: www.xidian.edu.cn
> User-Agent: moectf_browser
> X-Forwarded-For: 127.0.0.1
> Cookie: xduer
> Accept: PHP
> Accept-Encoding: UTF-8
> Accept-Language: zh-CN
>
< HTTP/1.1 200 OK
< Date: Fri, 06 Sep 2019 14:41:00 GMT
< Server: Apache/2.4.7 (Ubuntu)
< X-Powered-By: PHP/5.5.9-1ubuntu4.14
< Vary: Accept-Encoding
< Content-Length: 443
< Content-Type: text/html
<
{ [443 bytes data]
100   443  100   443    0     0   3141      0 --:--:-- --:--:-- --:--:--  3141HTTP/1.1 200 OK
Date: Fri, 06 Sep 2019 14:41:00 GMT
Server: Apache/2.4.7 (Ubuntu)
X-Powered-By: PHP/5.5.9-1ubuntu4.14
Vary: Accept-Encoding
Content-Length: 443
Content-Type: text/html

First of all, you must come from XiDian University<br>Second, you have to use moectf_browser<br>Third, you have to visit from the localhost<br>Fourth, your identity must be xduer<br>Fifth, client can only accept PHP documents<br>Sixth, we only allow UTF-8 encoding<br>Finally, we are only allowed to use Chinese.<br>Congratulations on having a good understanding of HTTP HEADERS and finally getting flag:<br>moectf{Reward_y0u_For_per3everAnce}
* Connection #0 to host 39.108.11.206 left intact
```

试到最后一步看见`flag`里的那个`perseverance`我当时就想从四楼跳下去...

### 朝鲜人

朝鲜人! wd**d, 我去哪儿找朝鲜dns啊QAQ

必应了好久找到一个阿里云的EDNS-CLIENT-SUBNET的使用介绍, 在我的`Open SUSE Tumbleweed`中运行如下:

```bash
$ wget ftp://ftp.isc.org/isc/bind9/9.9.3/bind-9.9.3.tar.gz
$ tar xf bind-9.9.3.tar.gz
$ cd bind-9.9.3
$ wget http://wilmer.gaa.st/edns-client-subnet/bind-9.9.3-dig-edns-client-subnet-iana.diff 
$ yum -y install patch
$ patch -p0 < bind-9.9.3-dig-edns-client-subnet-iana.diff
$ ./configure --without-openssl
$ make
```

然后终端执行:

```bash
$ /bin/dig/dig @8.8.8.8 region.challenge.moectf.cn +client=175.45.176.68
```

`edns`其实就是查询`dns`服务器的时候手动告知`dns`你是哪里的人, 然后`dns`就会返回一个你该访问的地址. 得到朝鲜解析的IP之后, 老方法修改`hosts`, 就得到了朝鲜人的`flag`.

从企鹅大佬的博客上找到了关于edns的详细解释, 现在很不要脸的引用过来:

>#### *1、什么是EDNS？*
>
>​    EDNS就是在遵循已有的DNS消息格式的基础上增加一些字段，来支持更多的DNS请求业务。
>
>需要注意的是，像DNS服务器这样一个大型且广泛应用的系统软件，新增加扩展协议的时候一定要考虑到向后兼容性(backward compatibility)，即你增加了你这个特性的消息传输给未支持该特性的服务器时，后者依然能正确处理。
>
>#### 2、为什么要有 EDNS？
>
>​    RFC2671中指出EDNS被提出来的几个理由：
>
>​        1）DNS协议头部的第二个16字节中都已经被用的差不多了，需要添加新的返回类型(RCODE)和标记(FLAGS)来支持其他需求；
>
>​        2）只为标示domain类型的标签分配了两位，现在已经用掉了两位（00标示字符串类型，11表示压缩类型），后面如果有更多的标签类型则无法支持；
>
>​        3）当初DNS协议中设计的用UDP包传输时包大小限制为512字节，现在很多主机已经具备重组大数据包的能力，所以要有一种机制来允许DNS请求方通知DNS服务器让其返回大包；
>
>​        以后我们会看到，DNSSEC机制和edns-client-subnet机制等都需要有EDNS的支持。
>
>#### *3、EDNS 的内容是什么？*
>
>​        怎样在DNS消息协议的基础上再增加一些字段呢？为了保持向后兼容性，更改已有的DNS协议格式是不可能的，所以只能在DNS协议的数据部分中做文章。
>
>​        所以，EDNS中引入了一种新的伪资源记录OPT（Resource Record），之所以叫做伪资源记录是因为它不包含任何DNS数据，OPT RR不能被cache、不能被转发、不能被存储在zone文件中。OPT被放在DNS通信双方（requestor和responsor）DNS消息的Additional data区域中。
>
>转自 赤道企鹅™的博客

### Dynamic

这道题是考思维定势的... 

```php+HTML
<?php
highlight_file(__FILE__);
error_reporting(0);
$blacklist = ["system", "ini_set", "exec", "scandir", "shell_exec", "proc_open", "error_log", "ini_alter", "ini_set", "pfsockopen", "readfile", "echo", "file_get_contents", "readlink", "symlink", "popen", "fopen", "file", "fpassthru"];
$blacklist = array_merge($blacklist, get_defined_functions()['internal']);
foreach($blacklist as $i){
    if(stristr($_GET[cmd], $i)!==false){
        die('hack');
    }
}
eval($_GET[cmd]);
```

打开题目的代码长这样, 能看到`blacklist`里面禁用了好多用来输出和操作文件的函数... 怎么办? 于是我研究了好久`PHP`的漏洞, 包括`stristr()`的漏洞, 最后除了发现`print()`函数还能用之外什么都做不了...

但是咧, 经过大哥的点拨, 我明白了, `PHP`的函数不能用, 但是我们可以用`Linux`的指令呀!!!

于是我们分析代码, 发现首先是没有除了`cmd`之外的变量供我们使用的, 所以我们需要构建一个新的变量. 这新的变量的名字我们暂且叫`str`好了, 反正也没有什么关系.. ( 因为我大哥这么取的名字 ) 

接下来我们要读取这个`str`里的东西, 然后`print`出来. 最后跟上`id`的内容..

但是怎么调用`Linux`的函数呢.?

这要提到`PHP`里面又一个神奇的东西: 反引号: '`'. 

`PHP`会把包含在反引号里面的东西当成`Shell`指令执行.

所以, 我们就可以快乐的构建一句话木马啦!

Like this:

```php
?cmd=$str=$_GET[id];print%20`$str`;&id=ls
```

这样我们就可以调用`ls`指令来查看服务器当前文件夹里都有些什么东东..

然后我们看见了两个文件, 一个是`4f5f6c3be6ab7cc59dabf9ff7f2b248a
` 另一个是`index.php`..

`flag`自然不可能存在`index.php`里啦, 我们用`Linux`里的`cat`指令来查看那个乱码文件里是些什么东西:

```php
?cmd=$str=$_GET[id];print%20`$str`;&id=cat+4f5f6c3be6ab7cc59dabf9ff7f2b248a
```

然后就拿到`flag`啦...

`flag`: `moectf{PLEASE_USE_disable_function!!!!!!}`

## Android

### Android_Signin

手机下载, 打开, 拿flag.

### ClickIt

我教你们物理做法! 

首先准备一个2.8V电动机, 然后找到一根棉签, 可以通过导线或者锡箔的方法让其可以被手机电容屏识别, 然后放在一个支架上. 

电动机接好电源后, 在一段放置一个拨片,让其每转一圈拨片都会拨一下棉签, 最后把手机放在棉签头下面, 打开开关, 睡觉.

第二天早上起来就可以交`flag`了.

## DevOps

### SNI

这道题拿火狐打开可以发现证书只适用于`*.sspirits.top`, 于是修改`hosts`文件再修改HTTP请求头的Host, 然后就拿到了`flag` ( 但是我重新做的时候发现不对了... 我也很疑惑 )

### SNI++

这道题好像很好做..题目的地址: `176.9.166.200`

我使用了`nslookup`, 然后反查到了域名:

```bash
200.166.9.176.in-addr.arpa      name = vps.stockservers.com.
```

然后修改`hosts`文件, 

```bash
176.9.166.200 vps.stockservers.com
```

然后刷新网络再用火狐打开, 看到证书不匹配的安全警告点击跳过, 然后就拿到了`flag`.

## MISC

### 世界辣么大

就把程序拉开就行了, 程序窗口大小可变.

### Easy base64

扔进在线解密网站里.

### 网线大鲨鱼

拿`WireShark`打开, 然后导出数据, 在文件名那里就可以看见`flag`.

### 你的脑洞够大吗

这道题!!!

先下载程序, 打开后去哪里找key, 然后给了一串数字, 说网络情缘一线牵. 

网络情缘一线牵想到了QQ号, 然后打开QQ添加好友, 然后在主页照片墙看见另一个大佬的QQ号, 开了一堆会员.. 把QQ复制下来粘贴进key里面, 发现不对. 搜索这个人的QQ, 发现没有什么信息, 只有个人说明上有俩网址, 是吃鸡透视外挂的网址. 于是回到最开始的QQ账号, 点击添加好友, 在验证问题上看到了XDSEC的大佬ID, 明白这肯定是Key, 复制下来放进Key, 点了一下提示百朵云中定有不一样的颜色, 于是打开百度云, 把输入框里产生的那串乱码粘贴到百度网盘分享地址里, 然后打开发现需要提取码. 想起来题目上给的提取码 `2m54` , 输进去, 果然是对的. 下载得到一个压缩包.解压后发现一个脚本和一个txt, 提示说多一个1也算失误. 然后打开脚本字串去掉开头的1, 剩下扔进base64, 解出得到`flag`. ( 这是我做过最像黑客的一道题, 确实很考脑洞但是很好玩, 富有挑战性. )

### 被伪加密的文档

说来巧, 前几天下载注册机, 然后一不小心给电脑上装了360全家桶, 然后删软件时没删完, 不小心留了个360压缩... 然后做这题的时候压缩包就直接正常解压了!

然后就拿到`flag`了... 从那以后我觉得360压缩就留在电脑里吧...

正常做法是修改zip文件的hex码, 然后把标识是否加密的那个位给改过来.

### 修复&分离

用PS打开图片发现前半个`flag`, 然后拖进`Linux`用`binwalk`跑了一下发现有压缩包后缀, 就强行改成`zip`打开, 里面有一`txt`, 解压得到后半个`flag`.

### Keyboard

这道题不用题解了吧... 就跟着文件里的按键顺序按一遍就好了....

### 恼人的Aliga

爱酱是真的漂亮!

好吧这不是重点... 重点就是... 你选中图片最下面没有`aliga`部分, 然后拉伸变形可以得到一个条形码..但是咧, 条形码扫不出来... 后来分析一下发现边界是白条, 这显然不是条形码应该有的样子, 就处理成反相然后拿微信扫一扫获取`flag`.

### Secret Code

这个题嘛..也是社工, 我还买了hint...

把代码`base64`解密得到一串乱码, 加上从囧姐姐的主页看见的酷似提取码的东西, 于是再度打开百度云... 然后看见了帅气的PWN爷s@d. 拖进`WinHex`, 搜索`moectf`找到`flag`.

### Base64?

哇塞这道题是真的做了很久很久...

其实是考的是Base64的原理, 上网`bing`了一下, 大致就是把字符变成二进制串然后重新分组重新断句, 就很神奇...

先给`table`编号, 

```
00000000 x
00000001 y
00000010 U
00000011 V
00000100 z
00000101 A
00000110 B
00000111 C
00001000 D
00001001 E
00001010 F
00001011 G
00001100 H
00001101 I
00001110 J
00001111 K
00010000 L
00010001 M
00010010 N
00010011 O
00010100 a
00010101 b
00010110 c
00010111 d
00011000 e
00011001 f
00011010 g
00011011 h
00011100 i
00011101 j
00011110 k
00011111 l
00100000 m
00100001 W
00100010 X
00100011 Y
00100100 Z
00100101 0
00100110 1 
00100111 2
00101000 3 
00101001 4
00101010 5
00101011 6
00101100 7
00101101 8
00101110 9
00101111 P
00110000 Q
00110001 R
00110010 S
00110011 T
00110100 n
00110101 o
00110110 p
00110111 q
00111000 r
00111001 s
00111010 t
00111011 u
00111100 v
00111101 w
```

编好之后, 就可以通过查表的方式把密文翻译成二进制形式, 然后把每一段二进制的前两位0给去掉, 重新按照八位分组, 对照ASCII表就可以翻译出来. 这道题是在火车上写的, 就纯手撕了... 没有代码.. 不过查表和重新拼接的代码实现应该不怎么难...

### AiAiAi

作为第一个做出来这道题的人! 我要好好骄傲一会儿!

这道题其实就是音频隐写. 从`Ardour`的频谱上可以很清楚的看见尾部有东西..

于是放大了看, 发现一些酷似莫尔斯电码的东西, 解码提交.

### Osu Master

就把这题玩过去就行了..

画的轨迹就是`flag`.

### s@d的嘲讽表情

这道题.. 

反正我PWN爷最帅呗...

下载了图片拿`stegsolve`打开, 提取数据选择`RGB`的最低位, `LSB First`, 然后方式选择`BGR`, 点击`Preview`, 就可以看见`flag`了...

### Kokoro

这题需要一个男朋友 ( BF )🙃

BF就是`BrainFuck`啦....想什么呢

打开文件之后手动展开, 如果是 20. ,展开之后就是20个 . ,以此类推, 全部展开了扔进Ook! 编码解码器里解出来`flag`.

### Show Off 

最后一题了QAQ

写完睡觉!

这道题我擦二维码擦了一下午才擦干净...

然后就想方设法地实现这个函数了…

最后借鉴了大佬的作品, 才勉强把这题弄出来..

用`stegsolve`打开二维码进行频率分析可以得到代码里的`dic`, 然后

```python
def read(self, bit):
    # implement this
    # 请实现这一函数
    index = 0
    data = ''
    dic = [0x00, 0xff, 0x3f, 0xbf, 0xfe, 0x01, 0x40, 0xc0, 0xcf, 0xbe, 0x2f, 0x3e, 0x0f, 0x6f,
           0xef, 0x9f, 0x5f, 0x8f, 0xee, 0x30, 0x2e, 0x90, 0x70, 0x60, 0x8e, 0xd0, 0x9e, 0xce]
    for i in range(self.width):
        print(i)
        for j in range(self.height):
            p = list(self.im.getpixel((i, j)))
            ifx = info.get(i*10000+j)
            if ifx != None:
                for k in range(3):
                    if ifx | (1 << bit) == p[k]:
                        data += '1'
                    elif ifx & ~(1 << bit) == p[k]:
                        data += '0'
                    else:
                        print("ERROR!", i, j, k, ifx, p, bit)
                        px = 0
                        for color in dic:
                            if color | (1 << bit) == p[k]:
                                data += '1'
                                px = 1
                                break
                            if color & ~(1 << bit) == p[k]:
                                data += '0'
                                px = 1
                                break
                            if px == 0:
                                print("not sel")
                                exit()
                        bit = (bit+1) % 8
            else:
                for k in range(3):
                    px = 0
                    for color in dic:
                        if color | (1 << bit) == p[k]:
                            data += '1'
                            bit = (bit+1) % 8
                            px = 1
                            break
                        if color & ~(1 << bit) == p[k]:
                            data += '0'
                            bit = (bit+1) % 8
                            px = 1
                            break
                        if px == 0:
                            print("not sel")
                            exit()
    dat = bytearray()
    for i in range(int((len(data)-len(data) % 8)/8)):
        inx = int(data[i*8:i*8+8], 2)
        dat.append(inx)
    with open('flag1.jpg', 'wb') as f:
        f.write(dat)
```

然后把生成的图片拖进`WinHex`里, 就能看见`flag`了.

## PWN

### 欢迎来到pwn的世界

这道题要用`nc`, 我就复制粘贴进了终端, 然后回车, 提示不要输入太多字母, 然后我百度了好久也没弄懂`PWN`为何物,于是.. 在某个月黑风高的夜晚我绝望的脸滚键盘, 滚了好多输入, 然后就看见`flag`蹦了出来... 后面还跟了一个栈溢出的提示...

WD**D, `pwn`是这么玩的啊!

### pwn1

这道题入门了分析起来就很简单, 把题目给的程序扔进`IDA`, 我们发现输入的漏洞在`puts()`函数, 如果输入过长它会覆盖后面的内容.. 经过查数, 当输入长度为120个`A`时会溢出到一个函数跳转的地方, 再看`IDA`, 我们用`pwntools`封装一下打印`flag`的函数地址`0x00000000004006B6`, 把封装好的数据包传给服务器, 完事!

说的不专业不准确就饶了我吧... 我想睡觉...

# 结束

wdnmd! 我终于写完了!

可以睡觉了…