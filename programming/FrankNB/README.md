主要考察对正则表达式的利用，构造出正则就和`w1nd牛逼`没什么区别了

有一些区别的就是文件名是随机字符串，我使用的是遍历每个文件夹下的文件，应该还有别的解法

```python
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
```

