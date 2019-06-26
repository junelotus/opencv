# opencv
learning opencv
## Bilinear: 
从dest图像计算出原图像对应的坐标，此坐标很大概率上是浮点数，取这个浮点坐标最近的四联通坐标（x1,y1）(x1,y2)(x2,y1)(x2,y2)
作出以下两步运算，f(x,y)即为dest上（x,y）点的坐标：
1 f(x,y1)  = (x2-x)/(x2-x1)*f(x1,y1) +(x-x1)/(x2-x1)*f(x2,y1)
  f(x,y2) =  (x2-x)/(x2-x1)*f(x1,y2) +(x-x1)/(x2-x1)*f(x2,y2)
2 f(x,y) = (y2-y)/(y2-y1)*f(x,y1) + (y-y1)/(y2-y1)*f(x,y2)，其中x 和y均作为浮点是来使用。
上述两部计算可以简化为一个公式  ：
 f(x,y) = (1/((x2-x1)*(y2-y1)))/(f(x1,y1)*(x2-x)*(y2-y) + f(x2,y1) *(x-x1)*(y2-y) + f(x1,y2) *(x2-x)*(y-y1) + f(x2,y2)*(x-x1)*(y-y1))
### 我觉得并没有图像中心不对其，而导致有些像素无法加入运算的问题。
### 距离图像
使用掩模（对称的距离矩阵）mask扫描二值图像dest两遍，从左上角到右下角，再从右下角到左上角，更新二值图像的value用：
if(min>mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj) ))
           min=mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj));
### threshold函数
   threshold(imgGray,imgGray,20,255,CV_THRESH_BINARY);
/*threshold 函数将图像二值化，第五个参数为THRESH_BINARY 或THRESH_BINARY_INV时，第四个参数表示用来设置前景区域的值*/
### point 
  point.y 行的值
  point.x 列的值

## 椒盐噪声
在图像上随机黑白点的噪声
## CV_32FU3
每个像素值在0.0到1.0之间，尺度因子为１。
## cv_32F和cv_32FU1之间的区别
CV_32F is defined as:

 #define CV_32F  5

while CV_32FC1 is defined as:

#define CV_CN_SHIFT   3
#define CV_DEPTH_MAX  (1 << CV_CN_SHIFT)／／８
#define CV_MAT_DEPTH_MASK       (CV_DEPTH_MAX - 1)／／７
#define CV_MAT_DEPTH(flags)     ((flags) & CV_MAT_DEPTH_MASK)　／／掩码７
#define CV_MAKETYPE(depth,cn) (CV_MAT_DEPTH(depth) + (((cn)-1) << CV_CN_SHIFT))　５＋（０<<3）=5

#define CV_32FC1 CV_MAKETYPE(CV_32F,1)


#include <opencv2\opencv.hpp>
#include <iostream>
int main()
{
    std::cout <<  CV_32F << std::endl;／／５
    std::cout <<  CV_32FC1 << std::endl;／／５

    return 0;
}

## 直方图均衡化
https://www.cnblogs.com/yoyo-sincerely/p/6159101.html
