import cv2 as cv
from PIL import Image
gif = cv.VideoCapture('20196518133241511.gif')
ret = True
i = 0
#while ret is True:
ret,frame = gif.read() # ret=True if it finds a frame else False. Since your gif contains only one frame, the next read() will give you ret=False
	#img = Image.fromarray(frame)
	#img = img.convert('RGB')
	#imgg = cv.imread(str(i)+'.png');
	#img.save(str(i)+".png")
	#print(frame.size())
img = Image.fromarray(frame).cols
#size = img.shape
#int (size)
#cv.imshow('input_image', img)
#cv.waitKey(0)
#cv.destroyAllWindows()
