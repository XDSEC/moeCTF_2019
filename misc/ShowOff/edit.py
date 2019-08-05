from PIL import Image, ImageDraw


class Picture:
    def __init__(self, path):
        self.im = Image.open(path)
        self.draw = ImageDraw.Draw(self.im)
        self.width, self.height = self.im.size

    @staticmethod
    def preprocess(data):
        ret = ''
        for i in data:
            temp = bin(i)[2:]
            ret += (8-len(temp))*'0'+temp
        return ret

    def write(self, bit, data):
        """
        :param bit ranges from 0-7
        """
        index = 0
        data = Picture.preprocess(data)
        for i in range(self.width):
            for j in range(self.height):
                p = list(self.im.getpixel((i, j)))
                for k in range(3):
                    if index >= len(data):
                        return
                    if data[index] == '1':
                        p[k] |= 1 << bit
                    else:
                        p[k] &= ~(1 << bit)
                    index += 1
                    bit = (bit+1) % 8
                self.draw.point((i, j), fill=tuple(p))
        print('write incomplete')
        print(f'{index}/{len(data)}')

    def read(self, bit):
        # implement this
        # 请实现这一函数
        pass


with open('flag.jpg', 'rb') as f:
    data = f.read()
pic = Picture('qr.jpg')
pic.write(5, data)
pic.im.save('output.png', 'PNG')
