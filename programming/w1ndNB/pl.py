import base64

x = 0

for i in range(1,151):
    filename = 'w1ndNiuBi' + '.\\' + str(i) + '\\' + str(i) + '.txt'
    with open(filename) as f:
        for line in f.readlines():
            if line == 'w1ndNiuBi\n':
                x += 1

print (x)
