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

void equalHistFun(const Mat & src,Mat& dest,const int cth)
{

int rows=src.rows;
int cols =src.cols;
map<float,int> hist;
        typedef map<float,int>::iterator It;
        for(int i=0;i<rows;i++)
                for(int j=0;j<cols;j++)
               { 
              float value = static_cast<float>(src.at<Vec3b>(i,j)[cth]);
                       
                       hist[value]++;
        }
It itf = hist.begin();
It its = ++itf;
itf= hist.begin();
for(;its!=hist.end();its++,itf++)
{
        //cout<<itf->first<<"  "<<its->second<<" ";
       
//        its->second += itf->second;
        hist[its->first] +=hist[itf->first]; 
        //cout<<its->first<<" "<<hist[its->first]<<endl;
       
  //     cout<<itf->first<<"  "<<its->first<<endl;
       }

        float area = cols*rows;
for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
        {
                float value = static_cast<float>(src.at<Vec3b>(i,j)[cth]);
                dest.at<Vec3b>(i,j)[cth] =static_cast<unsigned char>( (static_cast<float>(hist[value])/area)*255.0);
                
 cout<<(static_cast<float>(hist[value])/area)*255.0<<endl  ;             
                }
cout<<endl;
cout<<endl;
        
}






void fun_second(const Mat &src,Mat & dest)
{
        for(int i=0;i<3;i++)
                equalHistFun(src,dest, i);
        
        }

int main(){

        Mat src=imread("/home/june/opencv_test/equalHist.jpg");
        Mat dest(src.size(),CV_8UC3);
    
    fun_second(src,dest);
    imshow("src",src);
    imshow("dest",dest);
Mat dest_(src.size(),CV_8UC3);//
    //equalizeHist(src,dest_);
    imshow("opencv_",dest_);
    waitKey(10000);
    return 0;
        
        }
