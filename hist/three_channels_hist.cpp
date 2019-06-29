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
//#ifndef COLORHISTOGRAM_H
//#define COLORHISTOGRAM_H

 
using namespace cv;

class ColorHistogram
{
public:
    ColorHistogram();
    MatND getHistogram(const Mat& image);
    Mat getHistogramImage(const Mat&image);
    void colorReduce(Mat& image,int div=64);
private:
    int histSize[3];
    float hranges[3];
    const float* ranges[3];
    int channels[3];
};
ColorHistogram::ColorHistogram()
{
    //准备彩色直方图的参数
    histSize[0] = histSize[1] = histSize[2] = 2;
    //BGR的范围
    hranges[0] = 0.0;
    hranges[1] = 1.0;
    hranges[2] =2.0;
    //所有通道拥有相同的范围
    ranges[0] = hranges;
    ranges[1] = hranges;
    ranges[2] = hranges;
    //三个通道
    channels[0] = 0;
    channels[1] = 1;
    channels[2] = 2;
}

//获取直方图
//因为彩色的色彩数目较多，则直方图的栏目则也很多
MatND ColorHistogram::getHistogram(const Mat& image)
{
    MatND hist;
    calcHist(&image,            //图像矩阵指针，可多个图像
             1,                 //图像的数量，1张
             channels,          //通道的数量，一张图片(3通道的)为0~2，两张为3~5,三张为...
             Mat(),             //掩码图像。（不使用掩码图像）
             hist,              //计算返回的直方图
             2,                 //三维直方图
             histSize,          //每个维度的直方图数组的大小
             ranges,            //像素值的范围，BGR三个通道的像素值相同
             false,
             false
    );
    return hist;
}

// 将直方图用图表形式显示出来
Mat ColorHistogram::getHistogramImage(const Mat&image)
{
    //计算直方图
    MatND hist = getHistogram(image);

    //获取最大值和最小值
    double  maxValue[3] = {0};
    double  minValue[3] = {0};
    int maxIdx[3] = {0};
    int minIdx[3] = {0};

    minMaxIdx(hist,minValue,maxValue,minIdx,maxIdx);
    //qDebug()<< hist.channels();
    //显示直方图的图像
    Mat histImg(histSize[0],histSize[0],CV_8U,Scalar(255));
    //设置最高点为nbins的90%
    int highPoint = static_cast<int>(0.9*histSize[0]);
    //每个条目都绘制一条垂直线
    //qDebug() << hist.size;
    for(int h = 10000;h < histSize[0]+10000;h++){
        float binVal = hist.at<float>(h);
        int intensity = static_cast<int>(binVal*highPoint/maxValue[0]);
        //两点之间绘制一条直线
        line(histImg,Point(h,histSize[0]),
                     Point(h,histSize[0]-intensity),
                     Scalar::all(0));
    }
    return histImg;
}

// 减少图像的色彩数目
void ColorHistogram::colorReduce(Mat& image,int div)
{
    int n1 = image.rows;
    int nc = image.cols;
    //图像是连续存储的吗？
    if(image.isContinuous()){
        //没有则对行进行填补
        nc = nc*n1;
        //一维数组
        n1 = 1;
    }
    int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));
    //用来对像素值进行取整的二进制掩模
    uchar mask = 0xFF << n;
    for(int j = 0;j < n1;j++){
        uchar* data = image.ptr<uchar>(j);
        for(int i = 0;i < nc;i++){
            *(data++) = (*data)&mask + div/2;
            *(data++) = (*data)&mask + div/2;
            *(data++) = (*data)&mask + div/2;
        }
    }
}

int main()
{

        ColorHistogram ch;
        Mat src= imread("dis_1.png");
        Mat hsv;
        cvtColor(src,hsv,CV_BGR2HSV);    

       Mat result =  ch.getHistogram(hsv);//getHistogramImage(hsv);
for(int i=0;i<result.rows;i++)
        for(int j=0;j<result.cols;j++)
                cout<<static_cast<float>(result.at<float>(i*result.cols+j))<<endl;
cout<<result.size()<<endl;
return 0;
}
