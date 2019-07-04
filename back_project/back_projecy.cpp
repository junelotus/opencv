#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;
#define pai 3.14159
/*void cv::calcBackProject ( const Mat * images, int nimages, const int * channels, InputArray hist, OutputArray backProject, const float ** ranges, double scale = 1, bool uniform = true )

*/int main(int argc,char **argv)
{
if(argc<2) return 0;

Mat src =imread(argv[1]);
Mat hsv;
/*
int histSize[] ={3,3,3};
const float  range []={0,256};
const float *ranges[]={range,range,range};
const int chan_count [] = {0,1,2};
Mat mat_array[]={channels.at(0),channels.at(1),channels.at(2)};

calcHist(&src,1,chan_count,Mat(),h_hist,3,histSize,ranges,true,false);
*/
//normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
cvtColor(src,hsv,CV_BGR2HSV);
 int histSize[]={25,25};
const float range[]={0,256};
const float *ranges[]={range,range,range};
const int channels[] ={0,1,2};


MatND   hist;
calcHist(&hsv,1,channels,Mat(),hist,2,histSize,ranges,true,false);
normalize(hist, hist, 0, 255, NORM_MINMAX, -1, Mat());
MatND dest;//(src.size(),CV_32FC1);
calcBackProject(&hsv,1,channels,hist,dest,ranges);

Mat dest_june(hsv.size(),CV_8UC1);

for(int i=0;i<hsv.rows;i++)
for(int j=0;j<hsv.cols;j++)
{
    float h = hsv.at<Vec3b>(i,j)[0];
    float s = hsv.at<Vec3b>(i,j)[1];
    float value = hist.at<float>(h/25,s/25);
//cout<<value<<endl;
    dest_june.at<unsigned char>(i,j) = static_cast<unsigned char>(value*255);

}

 


imshow("src",src);
imshow("dest",dest);
imshow("dest_june",dest_june);
waitKey(100000);
return 0;

}


