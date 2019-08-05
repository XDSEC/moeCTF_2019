from zipfile import ZipFile
from collections import Counter

with ZipFile('chars.zip') as f:  # 这里咱直接读压缩包
    chars = f.read('chars.txt')  # 读取其中的chars.txt文件，返回类型是bytes

counter = Counter(chars)  # 标准库提供的计数器

# chars的类型为bytes，most_common函数会对其进行迭代，在Python中对bytes迭代会产生int
# 那这直接往bytes里丢一下
flag = bytes(tp[0] for tp in counter.most_common())

print(flag)
