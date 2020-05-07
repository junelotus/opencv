# !/usr/bin/python3
# -- coding: utf-8 --
import sys
import os
import cv2
import argparse

if __name__ == '__main__':
    parse = argparse.ArgumentParser()
    parse.add_argument("-i", "--input", type = str, default = '', help = "the image file")
    
    data = vars(parse.parse_args())

    image = "59430_1.jpg"#data["input"]
    # if image == None:
    #     print("please set the input image!")
    #     sys.exit(0)
    # if not os.path.exists(image):
    #     print("cannot find the input image!")
    #     sys.exit(0)
    def compare(cnt1,cnt2):
        if cnt1.y < cnt2.y :
            return True
        if cnt1.y>cnt2.y:
            return False
        
        return cnt1.x<cnt2.x
    def listInLists(cnt,cntList):
        x,y,w,h  = cv2.boundingRect(cnt)
        for c in cntList:
            x1,y1,w1,h1 = cv2.boundingRect(c)
            if x==x1 and y==y1 and w==w1 and h==h1:
                return True
        return False        
    def takeSecond(cnt):
        x, y, w, h = cv2.boundingRect(cnt) 
        return x  

    def takeArea(cnt):
        x, y, w, h = cv2.boundingRect(cnt) 
        return w*h 
    def split_img(path,name):
            result =[]
            img = cv2.imread(path)
            #img = cv2.resize(img, (0, 0), fx=300/img.shape[1], fy=300/img.shape[0], interpolation=cv2.INTER_NEAREST)
            print(img.shape)
            
            img = cv2.cvtColor(img,cv2.COLOR_RGB2GRAY)
            
            _,img = cv2.threshold(img,170,255,0)
            kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (3, 3))
            img = cv2.dilate(img, kernel)
            img = cv2.erode(img, kernel)
            #cv2.imshow("img_gray",img)

            contours , hierarchy = cv2.findContours ( img , cv2.RETR_EXTERNAL , cv2.CHAIN_APPROX_SIMPLE )
            img2 =img
            print(len(contours))


            print("contours.size()=".format(len(contours)))
            i = 0
            big_cnt = contours[0]
            x_big, y_big, w_big, h_big = cv2.boundingRect(big_cnt)
            td = 0
            i=0
            list_contours = []

            contours.sort(key=takeArea,reverse=True)
            counter_contian = 0
            list_counter_contian =[]
            for cnt in contours:
                x, y, w, h = cv2.boundingRect(cnt)
                for cnt1 in contours:
                    x1,y1,w1,h1 = cv2.boundingRect(cnt1)
                    if w1*h1<100 or w1<10 or h1<10:
                        list_counter_contian.append(cnt1)
                        continue
                    if x == x1 and y ==y1 and w==w1 and h==h1:
                        continue
                    
                    
                    if x1 >x and x1<x+w or x1+w1 >x and x1+w1<x+w :
                        if y1 >y and y1<y+h or y1+h1 >y and y1+h1<y+h:
                            print(x,y,w,h)
                            print(x1,y1,w1,h1)
                            print('\n')
                            list_counter_contian.append(cnt)
                            break
                
            print("面积")    
            print(len(list_counter_contian))

            for cnt in list_counter_contian:
                x, y, w, h = cv2.boundingRect(cnt)
                print(x,y,w,h)    
            print("面积")
            
            
            contours.sort(key=takeSecond,reverse=False)

            print("list_counter_contian.size()={}".format(len(list_counter_contian)))
            print("name = {}".format(name))
            
            t = 0
            for cnt in contours:
                x, y, w, h = cv2.boundingRect(cnt) 
                if w*h<100 or w<10 or h<10:
                    continue    
                if listInLists(cnt,list_counter_contian) :
                    t+=1
                    continue
                else:    
                    print(x,y,w,h)   
                    #cv2.rectangle(img, (x,y), (x+w,y+h), (170,233,30), 2)
                    img1 = img[ y:y+h,x:x+w]
                    #img1 =(img1-127.5)/127.5
                    result.append('my/'+str(path.split('/')[2].split('.')[0])+'_'+str(name)+'.jpg')
                    #if os.path.exists(path.split('/')[1].split('.')[0]) == False:
                    #  os.makedirs(path.split('/')[1].split('.')[0])
                    print(str(path.split('/')))
                    cv2.imwrite('my/'+str(path.split('/')[2].split('.')[0])+'_'+str(name)+'.jpg', img1)#[x:x+h, y:y+w])
                    cv2.waitKey(5)
                    #if name == 28:
                    #   exit()
                    name+=1    
                t+=1
                
            #cv2.imshow("Contours",img)#img[x_big:x_big+w_big, y_big:y_big+h_big])
            cv2.waitKey(500)
            return name,result
    name = 0	
    split_img("./jpg/36790_1.jpg",name)
    new_image = 'my/36790_1_2.jpg'#'text-detection-ctpn/data/demo/006.jpg'#'my/59430_1_1.jpg'
    # # read the image and convert to gray
    # image = cv2.imread(image)
    # image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    # # resize
    # #image = cv2.resize(image, None, fx=2.0, fy=2.0, interpolation=cv2.INTER_CUBIC)
    # # find the threshold as 0.8 of the max grayscale value
    # threshold = 0
    # min_val, max_val, min_loc, max_loc = cv2.minMaxLoc(image)
    # threshold = int(max_val * 0.80)
    # # binary the image to the 0 or 255
    # cv2.threshold(image, threshold, 255, cv2.THRESH_BINARY, image)
    # # morph close
    # kernel = cv2.getStructuringElement(cv2.MORPH_RECT, (15, 15))
    # image = cv2.morphologyEx(image, cv2.MORPH_CLOSE, kernel)
    # # save the new image
    # cv2.imwrite(new_image, image)
    
    cmd = 'tesseract ' + new_image + ' temp --oem 3 --psm 10 --dpi 96 -c tessedit_char_whitelist=0123456789'
    os.system(cmd)
