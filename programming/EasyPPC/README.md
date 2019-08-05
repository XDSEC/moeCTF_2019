简单的python使用，不太擅长文件读写的可以直接把flag.txt里面的字符串复制出来(不过编辑器会卡爆233)，我写的脚本比较简洁，只有一行233(故意的)

```python
print (''.join([chr(int(i)) for i in __import__('re').findall(r'[0-9]{1,3}',open('flag.txt').read())]))
```

