#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
using namespace std;
using namespace cv;
int main()
{Mat x(1,4,CV_32FC1,Scalar(0));
Mat y(1,4,CV_32FC1,Scalar(0));
     //for(int i=0;i<4;i++)
 
    x.ptr<float>(0)[0] = 2;
    x.ptr<float>(0)[1]=0;
    x.ptr<float>(0)[2] =-2;
    x.ptr<float>(0)[3]=0;
    y.ptr<float>(0)[0] = 0;
    y.ptr<float>(0)[1]=2;
    y.ptr<float>(0)[2] =0;
    y.ptr<float>(0)[3]=-2;


//x.at<Vec1b>(0,3)[0] =0;

/*
     y.at<Vec1b>(0,0)[0] =0;
     y.at<Vec1b>(0,1)[0] =2;
     y.at<Vec1b>(0,2)[0] =0;
     y.at<Vec1b>(0,3)[0] =-2;
*/

Mat Mag(1,4,CV_32FC1,Scalar(0));
Mat Angle(1,4,CV_32FC1,Scalar(0));
cartToPolar( x,  y, Mag,  Angle,1);

             
             
        

        for(int i=0;i<4;i++)
                cout<<static_cast<double>(Mag.ptr<float>(0)[i])<<" "<<static_cast<double>(Angle.ptr<float>(0)[i])<<endl;
                return 0;
        }

        /*输出结果为2 0
        2 90
        2 180
        2 270
        说明x和y中存放的是坐标的信息，sqrt(x[i]*x[i]+y[i]*y[i])是结果
        */
