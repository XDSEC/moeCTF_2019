print (''.join([chr(int(i)) for i in __import__('re').findall(r'[0-9]{1,3}',open('flag.txt').read())]))
