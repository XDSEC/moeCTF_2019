本题考察了基础的网络编程，实际上还是比较简单的，我提供了两种解法

* 通过pwntools(较为简单)

```python
from pwn import *

p = remote('129.211.68.220',10000)

p.recvuntil('Have a try!\n')

a = ''
while a.find('moectf')==-1:
	a = p.recv()
	print(a)
	p.send(a)

print (a)
p.interactive()
```



* 通过socket(套接字)

```python
import socket

#connect to the server
s = socket.socket()
s.connect(('129.211.68.220',10000))

#recv welcome message
s.recv(2000)

#begin to repeat
while True:
    a = s.recv(200)
    if (a.decode()).find('moectf') == -1:
        s.sendall(a)
    else:
        print (a.decode())
        break
```

