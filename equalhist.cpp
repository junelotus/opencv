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

void equalHistFun(const Mat & src,Mat& dest,const int cth,const int c_count,const int byte_count=1)
{

int rows=src.rows;
int cols =src.cols;
map<float,int> hist;
        typedef map<float,int>::iterator It;
        for(int i=0;i<rows;i++)
                for(int j=0;j<cols;j++)
               { 
              float value = static_cast<float>(src.ptr(i)[j*c_count+cth]);
                       //cout<<"value="<<value<<endl;
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
                float value = static_cast<float>(src.ptr(i)[j*c_count+cth]);
                dest.ptr(i)[j*byte_count*c_count+cth] =static_cast<float>( (static_cast<float>(hist[value])/area)*255);//(c_count==3?1.0:255.0));
                
 //cout<<(static_cast<float>(hist[value])/area)*255.0<<endl  ;             
                }
//cout<<endl;
//cout<<endl;
        
}






void fun_second(const Mat &src,Mat & dest,const int c_count,const int byte_count=1)
{
        for(int i=0;i<c_count;i++)
                equalHistFun(src,dest, i,c_count);
        
        }

int main(){

        Mat src=imread("equalHist.jpg");
        Mat dest(src.size(),CV_8UC3);
     
    fun_second(src,dest,3,32/8);
    imshow("src",src);
    imshow("dest",dest);
    Mat dest_(src.size(),CV_8UC1);//
   Mat dest_copy(src.size(),CV_8UC1);
   cvtColor(src, dest_, CV_BGR2GRAY);
   imshow("opencv_huidu",dest_);

    equalizeHist(dest_,dest_copy);
    imshow("opencv_",dest_copy);
   imshow("opencv_",dest_copy);

   // equalizeHist(dest_,dest_copy);
   fun_second(dest_,dest_copy,1);
	 imshow("my",dest_copy);
     waitKey(10000);
    return 0;
        
        }
