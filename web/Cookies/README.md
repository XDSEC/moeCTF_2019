## 题解

首先说明这并不是一道正常的xss题目，仅用来让新生了解到XSS的存在。  
使用phptrick绕过验证码(aabC9RqS)后随便输入一个用户名都能看到回显。  
于是可以尝试使用html标签，比如script
根据题目StealingCookies(这里有点脑洞。。)需要打印出document.cookie。  
这样也是为了让同学们大概了解一下cookie是啥。（饼干）  
所以用户名输个`<script>alert(document.cookie)</script>`便可以看到弹出的flag  
实在没有想到有什么更好的办法来表现xss是什么。。。  

> `<script></script>document.cookie`貌似也可以（逃