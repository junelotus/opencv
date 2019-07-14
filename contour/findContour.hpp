#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
using namespace std;
using namespace cv;
#define pai 3.14159
Mat src;
Mat dest;
Mat gray;
Mat gray_d;
MemStorage g_storage;
vector<vector<Point>> contours;
vector<Vec4i> hierarchy;  
int g_threshold = 100;

    char *  Contours_win = "Contours";
 

void  on_trackbar(){//int ,void *){//函数必须有两个参数int 和 void *参数
if(g_storage==NULL)
    g_storage  = cvCreateMemStorage(0);
else
    cvClearMemStorage(g_storage);
cvtColor(src,gray,CV_BGR2GRAY);
imshow("gray",gray);//尽管之后做了处理。这里依然可以显示灰度图像
//threshold(gray,gray,0,255,THRESH_OTSU);//CV_THRESH_BINARY);


cvtColor(dest,gray_d,CV_BGR2GRAY);
imshow("gray",gray);//尽管之后做了处理。这里依然可以显示灰度图像
//threshold(gray_d,gray_d,0,255,THRESH_OTSU);//CV_THRESH_BINARY);

imshow("binary",gray);
namedWindow(Contours_win,CV_WINDOW_AUTOSIZE);
/*
CV_THRESH_OTSU是提取图像最佳阈值算法。该方法在类间方差最大的情况下是最佳的，就图像的灰度值而言，OTSU给出最好的类间分离的阈值。
原理：

对于图像I(x,y)，前景(即目标)和背景的分割阈值记作T，属于前景的像素点数占整幅图像的比例记为ω0，其平均灰度μ0；背景像素点数占整幅图像的比例为ω1，其平均灰度为μ1。图像的总平均灰度记为μ，类间方差记为g。

假设图像的背景较暗，并且图像的大小为M×N，图像中像素的灰度值小于阈值T的像素个数记作N0，像素灰度大于阈值T的像素个数记作N1，则有：
　　　　　　ω0=N0/ M×N (1)
　　　　　　ω1=N1/ M×N (2)
　　　　　　N0+N1=M×N (3)
　　　　　　ω0+ω1=1　　　 (4)
　　　　　　μ=ω0*μ0+ω1*μ1 (5)
　　　　　　g=ω0(μ0-μ)^2+ω1(μ1-μ)^2 (6)
将式(5)代入式(6),得到等价公式:
　　　　　　g=ω0ω1(μ0-μ1)^2 　　 (7)　这就是类间方差
采用遍历的方法得到使类间方差g最大的阈值T,即为所求。
     */
findContours(gray, contours, hierarchy, CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);
/*

对于每一个轮廓，hierarchy都包含4个整型数据，分别表示：后一个轮廓的序号、前一个轮廓的序号、子轮廓的序号、父轮廓的序号。 */
Mat resultImage = Mat ::zeros(src.size(),CV_8UC3);
drawContours(resultImage, contours, -1, Scalar(255, 0, 255));

//  imshow(Contours_win,resultImage);
    
//    waitKey(60000);


return ;


}
// int main(int argc,char** argv)
// {
//     if(argc<2) return 0;
//     src = imread(argv[1]);
// 
//     on_trackbar(0);
//     return 0;


// }



