from PIL import Image
import os


def extractPNG():
    os.chdir("C:\\Users\\logger\\Documents\\data\\programming\\ladum_dare_51\\image")
    img = Image.open("C:\\Users\\logger\\Documents\\data\\programming\\ladum_dare_51\\image\\chess.jpg")


    data = list(img.getdata())

    newImg = Image.new("RGBA", img.size)
    imgdata = [None] * img.size[0] * img.size[1]

    for i in range(len(data)):
        if data[i] == (0xff, 0xff, 0xff):
            imgdata[i] = (0x00, 0x00, 0x00, 0x00)
            continue
        lister = list(data[i])
        lister.append(0xff)
        imgdata[i] = tuple(lister)

    newImg.putdata(imgdata)
    newImg.save("chesspieces.png", "PNG")
    img.close()
    newImg.close()

class ImageDim:
    def __init__(self, x, y, w, h):
        self.x = x
        self.y = y
        self.w = w
        self.h = h

    def size(self):
        return (self.w, self.h)


def extractEachPiece():
    img = Image.open("C:\\Users\\logger\\Documents\\data\\programming\\ladum_dare_51\\image\\chesspieces.png")

    imgdim = ImageDim(870, 0, img.size[0], 460)
    imgdim.w -= imgdim.x
    newimg = Image.new(img.mode, imgdim.size())

    for y in range(imgdim.h):
        for x in range(imgdim.w):
            newimg.putpixel((x, y), img.getpixel((x + imgdim.x, y + imgdim.y)))
    newimg.show()

extractEachPiece()
