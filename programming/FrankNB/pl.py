import os
import re
import hashlib

counter = 0
for i in range(500):
    bb = i+1
    filename = '.\\' + str(bb)
    for root,dirs,files in os.walk(filename):
        filename += '.\\' + files[0]
    f = open(filename)
    if f.readline() == 'FrankNB!\n':
        f.close()
        with open(filename) as f:
            for line in f.readlines():
                if re.match(r'[a-zA-Z][0-9]{3,5}[~!@#$%^&*()_+][a-zA-Z]{0,8}$',line) != None:
                    counter += 1

print (counter)
print ('moectf{'+hashlib.sha256(str(counter).encode()).hexdigest()+'}',sep='')
