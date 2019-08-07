import socket

#connect to the server
s = socket.socket()
s.connect(('Server address',port))

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
