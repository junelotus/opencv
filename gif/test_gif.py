import cv2 
from PIL import Image
import numpy as np

from PIL import ImageEnhance
gif = cv2.VideoCapture('20196518133241511.gif')
ret,frame = gif.read()
img = Image.fromarray(frame.astype('uint8')).convert('RGB')
enh_col = ImageEnhance.Color(img)
color = 1.5
image_colored = enh_col.enhance(color)
enh_con = ImageEnhance.Contrast(image_colored)
contrast = 1.5
image_colored = enh_con.enhance(contrast)

frame = np.array(image_colored)
cv2.imshow("img1.jpg",frame)
#frame.save(r'wode.png')
