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
