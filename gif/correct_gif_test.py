from PIL import Image ,ImageSequence
gif  = Image.open(r'20196518133241511.gif')
for i,frame in enumerate(ImageSequence.Iterator(gif),1):
	frame.save(r'output/%d.png'%i)
