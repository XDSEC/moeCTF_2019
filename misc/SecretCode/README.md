原题：某一天s@d给出题人一串神秘代码 MTVVcjVnOWY3ZUh2bU5nQ2t1TW1vU0E 出题人拿到代码后，立刻就发现了s@d的隐私！ 嗯？你也想知道？不妨问一问出题人？ （简单的社工题）

解题步骤：首先对MTVVcjVnOWY3ZUh2bU5nQ2t1TW1vU0E进行处理，尝试后发现为base64加密字符串，得到

15Ur5g9f7eHvmNgCkuMmoSA

针对解密后的字符串没有什么想法，继续看题干发现这个题为社工题，且与出题人有很大关联。在moeCTF 2019官方群中找到出题人信息，查看其qq个人信息发现：

可疑句子为“世界的真理为5p21”，5p21是一个四个字符长度的字符串，配合上前面的15Ur5g9f7eHvmNgCkuMmoSA。

这里需要一点点的脑洞，当然在其他的misc题目中已经透露过这样的思想，所以也不算啥脑洞了（笑

15Ur5g9f7eHvmNgCkuMmoSA为百度云分享链接url后面部分代码，5p21即为密码。下载得到flag.jpg。使用16进制文本查看器在文件最后发现flag。