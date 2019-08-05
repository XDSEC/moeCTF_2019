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
