# 英国人&朝鲜人

系统基于“新式”的全局负载均衡器

~~假装是 Web 题的 DevOps 题~~

## 解法

出题核心是 EDNS Client Subnet ，是一个挺新的技术，用户可以发送指定网段来帮助 DNS 服务器确定自己的位置，从而优化访问速度。（这东西新到国内几乎没有公共 DNS 支持这个功能

有这么几个解法

1. 挂 VPN/连上指定区域内服务器查询/其它从远程浏览的方法
2. 全球 DNS 查询
3. 用户直接对权威DNS发起带 Edns Subnet 信息的查询
4. 找一个支持这个功能的 HTTP DNS

1和2是大部分人选择的做法
 
因为有 GeoDns 功能服务器在支持 Edns 的同时肯定会支持在不发送 Edns 信息的时候直接判断判断来源 IP。

但碰到朝鲜这种地方Emmm

~~找三胖嫖一个服务器~~ 这肯定不可能啊

那正解可以是

1.找到属于这个国家的 IP 段： Google上随便搜一下，比如[这里](https://lite.ip2location.com/korea-democratic-peoples-republic-of-ip-address-ranges)

2.```dig region.challenge.moectf.cn +trace +subnet=175.45.176.0```

3.丢进 hosts 或者直接对这个 IP 发请求

这里 +trace 是因为上面提到的国内没啥公共DNS支持这个功能，需要直连 MoeCTF-NS 服务器查询
（或者加上参数 @8.8.8.8， Google 的服务器是已经确定支持这个功能的

对于上面提到的第4种方法， Google 就有一个 [dns.google](https://dns.google) ，可指定 Edns Subnet 。
