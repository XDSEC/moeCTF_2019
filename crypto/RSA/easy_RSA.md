# 提取N，e
使用openssl提取N，e
```
root@kali:~/桌面# openssl rsa -pubin -text -modulus -in public.pem
RSA Public-Key: (256 bit)
Modulus:
    00:dc:84:79:8f:78:6d:6d:ab:33:14:46:3e:2c:5f:
    27:cd:0d:c4:8a:0f:97:13:da:fc:f9:18:02:eb:bc:
    b7:1d:5f
Exponent: 65537 (0x10001)
Modulus=DC84798F786D6DAB3314463E2C5F27CD0DC48A0F9713DAFCF91802EBBCB71D5F
writing RSA key
-----BEGIN PUBLIC KEY-----
MDwwDQYJKoZIhvcNAQEBBQADKwAwKAIhANyEeY94bW2rMxRGPixfJ80NxIoPlxPa
/PkYAuu8tx1fAgMBAAE=
-----END PUBLIC KEY-----
```
可以看出N：DC84798F786D6DAB3314463E2C5F27CD0DC48A0F9713DAFCF91802EBBCB71D5F  
e: 65537

# 分解N
将N转化为十进制数:99742889480132178464693625265991467727088330702125690789109469022100733238623  
使用软件yafu分解N.可得：
```
p:336771668019607304680919844592337860739
q:296173636181072725338746212384476813557
```

# 解密
用了一个python脚本来解密。
``` python
import gmpy2

p = 336771668019607304680919844592337860739
q = 296173636181072725338746212384476813557
e = 65537

f = int(open('flag.enc', 'rb').read().encode('hex'), 16)
print f
n = p * q
fn = (p - 1) * (q - 1)
d = gmpy2.invert(e, fn)
h = hex(gmpy2.powmod(f, d, n))[2:]
if len(h) % 2 == 1:
    h = '0' + h
s = h.decode('hex')
print s
```



