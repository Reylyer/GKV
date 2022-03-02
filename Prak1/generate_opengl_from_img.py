import skimage.io as io
import numpy
from skimage.transform import resize
from PIL import Image

file = 'hotlen.png'
img = Image.open(file)
# img = img.load()
#resize
img = resize(img,(32, 32), anti_aliasing=True)


img = numpy.array(img)
result = 'void wtf_img(){\n'

pix_temp = img[0][0]
result += f"\tglColor3ub({pix_temp[0]},{pix_temp[1]},{pix_temp[2]});\n"

y = 0
for line in img:
    x = 0
    for pixel in line:
        # print(pixel)
        equal = pix_temp == pixel
        if not equal.all() :
            pix_temp = pixel
            result += f"\tglColor4ub({pixel[0]},{pixel[1]},{pixel[2]}, {pixel[3]});\n"
        result += f"\tglRectf({x}, {y}, {x} + 1, {y} - 1);\n"
        x+= 1
    y-= 1

result += "}"

with open(str.partition(file, '.')[0] + '.cxx', 'w') as f:
    f.write(result)
