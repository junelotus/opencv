#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
using namespace std;
    using namespace cv;  
      
    int main(int argc,char *argv[])  
    {  
        float maxValue=0;  //定义距离变换矩阵中的最大值  
        Mat image=imread(argv[1]);  
        Mat imageGray;  
        cvtColor(image,imageGray,CV_RGB2GRAY);  
        imageGray=~imageGray;  //取反  
        GaussianBlur(imageGray,imageGray,Size(5,5),2); //滤波  
        threshold(imageGray,imageGray,20,200,CV_THRESH_BINARY); //阈值  
        imshow("s",imageGray);  
        Mat imageThin(imageGray.size(),CV_32FC1); //定义保存距离变换结果的Mat矩阵  
        distanceTransform(imageGray,imageThin,CV_DIST_L2,3);  //距离变换  
        Mat distShow;  
        distShow=Mat::zeros(imageGray.size(),CV_8UC1); //定义细化后的字符轮廓  
        for(int i=0;i<imageThin.rows;i++)  
        {  
            for(int j=0;j<imageThin.cols;j++)  
            {  
                if(imageThin.at<float>(i,j)>maxValue)  
                {  
                    maxValue=imageThin.at<float>(i,j);  //获取距离变换的极大值  
                }  
            }  
        }  
        for(int i=0;i<imageThin.rows;i++)  
        {  
            for(int j=0;j<imageThin.cols;j++)  
            {  
                if(imageThin.at<float>(i,j)>maxValue/1.9)  
                {  
                    distShow.at<uchar>(i,j)=255;   //符合距离大于最大值一定比例条件的点设为255  
                }  
            }  
        }  
        imshow("Source Image",image);  
        imshow("Thin Image",distShow);  
        waitKey();  
        return 0;  
    }  
