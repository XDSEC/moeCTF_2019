## 题解

~~社工题，能在网上搜到相关题目然后拼出来payload~~  
不建议新生在这道题上纠结

fl的正则表达式说明略

#### 先说`unserialize()`

php的`serialize`/`unserialize`函数用于将对象转化成一个字符串/转换回来，而同时不丢失其类型和结构信息，一般用于传输一个结构化的对象。这样的序列化/反序列化操作广泛存在于各种地方，建议深入**理解**其意义与原理。  
一般比较简便的做法是写一段php代码，构造出来这个对象，再调用`unserialize()`，其输出作为payload。见本目录下的文件"solve.php"。

#### 再说`__destruct()`

由于php的对象只在一次连接中存活，所以每次连接结束时都会销毁所有对象。  
在对象进行销毁时，会自动调用对象的`__destruct`函数。很多php应用程序的漏洞都是由于`__destruct`中写了一些危险的逻辑导致的。  
这种在对象的生存周期内被自动调用的函数被称作“魔法函数”，更详细的介绍请阅读[php参考手册](https://www.php.net/manual/en/language.oop5.magic.php)  

本题中`__destruct`明显包含了eval

#### 然后说`__destruct`中的正则表达式

相信熟悉正则表达式的人*Frank: 这是新生赛啊各位。。。扶额*一下子就能看出?R。它表示递归匹配整个正则表达式。  
题目中的表达式匹配的是形如"abc(def(ghi()))"这样的字符串。没反应过来的话再拿手在纸上写写画画。  

> 话说这是这个东西出现在LCTF，makerCTF后竟然成了moeCTF里头的知识点，我真的佛了 (Frank)

所以我们需要找到一系列函数，其中最里头的函数不能有参数，而且还要能够读文件。  
不出意料的话应该都是`implode(getallheaders())`/`current(getallheaders())`这样的组合。我们把它丢进`eval()`，就可以RCE了。  

#### 最后说`echo unserialize(...)`

echo一个对象的时候会调用对象的`__toString()`魔法函数，将其返回的字符串输出。  
然而本题中没有__toString()，于是正常情况下php会报错：

```
Recoverable fatal error: Object of class flag 
could not be converted to string
```

有人在瞎碰乱撞的过程中无意中将反序列化出的序列进行了以下修改：

```git
- O:4:"flag":1:{s:3:"c
+ O:4:"flag":2:{s:3:"c
```
便得到了flag。CVE-2016-7124解释了这一问题。

> 百度吧，看不明白马上就放下。水到渠成。

### 评论区：

Frank: 个人觉得这道题极不应该放在新生赛。但是既然都有人做出来了。。。哎。。。。佛了
