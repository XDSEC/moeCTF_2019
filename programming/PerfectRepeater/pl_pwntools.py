from pwn import *

p = remote('Server address',Port)

p.recvuntil('Have a try!\n')

a = ''
while a.find('moectf')==-1:
	a = p.recv()
	print(a)
	p.send(a)

print (a)
p.interactive()
