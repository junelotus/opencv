#include <iostream>
using namespace std;
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h> 
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/highgui>
using namespace cv;
bool resize_fun(Mat src,Mat& dest,int size_width,int size_height)
{

         int height  = src.rows;
         int width = src.cols;
cout<<width<<endl;
cout<<height<<endl;
//Mat dest(size_width, size_height, CV_8UC3, Scalar(255,255,255));         
if(width ==0 || height==0||size_height==0||size_width==0)
        return true;

for(int j=0;j<size_height;j++)
{//for every cols
//char * cols_current = dest+dest[y*size_width];


  double  y = static_cast<double>(j)*static_cast<double>(height)/static_cast<double>(size_height);
  Mat cols_current  = dest.row(j);      
  //cout<<"cols_current.size()="<<cols_current.size()<<endl;
  for(int i =0;i<size_width;i++)      
        {
                
                 double  x = static_cast<double>(i)*static_cast<double>(width)/static_cast<double>(size_width);
//cout<<"(x,y)="<<j<<","<<i<<endl;

                 int int_x = x;
                 int int_y = y;
                 double  u = x-static_cast<int>(x);
                 double v = y-static_cast<int>(y);
                
                
                for(int k=0;k<3;k++)
                {
                

                unsigned int a00_1 = src.at<Vec3b>(int_y,int_x)[k];
                unsigned int a10_1 = src.at<Vec3b>(int_y+1,int_x)[k];
                 unsigned int a01_1 = src.at<Vec3b>(int_y,int_x+1)[k];
                 unsigned int a11_1 = src.at<Vec3b>(int_y+1,int_x+1)[k];
        
                 unsigned int num= (static_cast<double>(int_y+1.0)-y)*(static_cast<double>(int_x+1.0)-x)*static_cast<unsigned int>(src.at<Vec3b>(int_y,int_x)[k])+
                                     v*(static_cast<double>(int_x+1.0)-x)*static_cast<unsigned int>(src.at<Vec3b>(int_y+1,int_x)[k])+
                                      (static_cast<double>(int_y+1.0)-y)*static_cast<double>(u)*static_cast<unsigned int>(src.at<Vec3b>(int_y,int_x+1)[k])+
                                       static_cast<double>(u)*static_cast<double>(v)*static_cast<unsigned int>(src.at<Vec3b>(int_y+1,int_x+1)[k]);
                
// cout<<a00_1<<" "<<a10_1<<" "<<a01_1<<" "<<a11_1<<endl;
 //cout<<"j="<<j<<"  i="<<i<<endl;
 dest.at<Vec3b>(j,i)[k]  = num;
   //             cout<<num<<endl;
    }


                
                
       //         cols_current.col[i] = src.at<>Vec3b(int_X,int_y);//static_cast<int>x,static_cast<int>y);


                
                
                
                
                
                }
        }

return true;        
}




int main()
{
        
       Mat src =imread("/home/june/opencv_test/dog.jpg");
       imshow("dog",src);



int width  = src.cols;
 int height = src.rows;

cout<<src.channels()<<endl;
cout<<height<<endl;

 int size_width = 720,size_height = 1280;
Mat dest(size_height,size_width,CV_8UC3,Scalar(0,0,0));
resize_fun(src,dest, size_width,size_height);
imshow("big dog",dest);

Mat imgDst(size_height,size_width,CV_8UC3,Scalar(0,0,0));
resize(src, imgDst, Size(720,1280));

imshow("opencv big dog",imgDst);

waitKey(600000);
       return 0;
        
        
        
}





