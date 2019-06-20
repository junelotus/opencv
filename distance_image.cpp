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
/*细化轮廓*/

//Mat mask={{4.5,4,3.5,3,3.5,4,4.5},{4.5,4,3.5,3,3.5,4,4.5}};
void fun_distance(const Mat& src ,const Mat& mask)
{
int rows = src.rows;
int cols =src.cols;
Mat dest(rows+6,cols+6,CV_32FC1,Scalar(0));//
Mat imgGray;
cvtColor(src,imgGray,CV_RGB2GRAY);  //灰度化
imgGray =~imgGray;
GaussianBlur(imgGray,imgGray,Size(5,5),2);
threshold(imgGray,imgGray,20,200,CV_THRESH_BINARY);

 rows = imgGray.rows;
 cols = imgGray.cols;


for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
 { 
         dest.ptr<float>(i)[j] =static_cast<float>( imgGray.ptr<unsigned char/*8u to deal*/>(i-3)[j-3] ==0?0:255);

//cout<< imgGray.ptr<unsigned int>(i-3)[j-3]<<endl;
}

       


imshow("二值图像bigger",dest);

int r_mask =mask.rows;
int c_mask =mask.cols;
float min_ = 100000.0;
for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
        {
                
                if(dest.ptr<float>(i)[j]!=0.0)
                {
                      for(int ii=-3;ii<=3;ii++)  
                        for(int jj =-1;jj<=3;jj++)
                        {//if 0
                        float value = static_cast<float>( imgGray.ptr<unsigned char>(i-3)[j-3] );
                                if(value==0)
                                {
                                        if(min_>mask.ptr<float>(3+ii)[3+jj] )
                                                min_ = mask.ptr<float>(3+ii)[3+jj];
                                        }

                                        

                                                
                                                
                                               

                        //else not 0        
                                
                                }

                           dest.ptr<float>(i)[j] = min_;     
                        
                            min_ =100000.0;                        
                        
                }
                
                
                
                }

min_ =100000.0;
                
for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
        {
                 if(dest.ptr<float>(i)[j]!=0.0)
                 {
                         
                         for(int ii=-3;ii<=3;ii++)
                         for(int jj =-1;jj<=3;jj++)
                          {//if 0
                            float value = static_cast<float>( imgGray.ptr<unsigned char>(i-3)[j-3] );
                            if(value!=0)                                                                                                            
                            {
                                    
                                    if(dest.ptr<float>(i)[j]>value+mask.ptr<float>(3+ii)[3+jj])
                                            min_ = value+mask.ptr<float>(3+ii)[3+jj];
                                    
                                    
                                    
                                    }

                                    dest.ptr<float>(i)[j] = min_;

                                    min_ =100000.0;

                                    
                                    }
                         
                         
                         }
                
                
                
                
        }

        float max=0.0;
for(int i=3;i<rows+3;i++)
                for(int j=3;j<cols+3;j++)
                {float value =  static_cast<float>( dest.ptr<unsigned char>(i)[j] );
                        if(max<value)
                                max =value;
                        }

for(int i=3;i<rows+3;i++)
                        for(int j=3;j<cols+3;j++)
                                                {float value =  static_cast<float>( dest.ptr<unsigned char>(i)[j] );
                                                                        if(max/1.9>value)
                                                                                  //                              max =value;
                                                                                    
                                                                                   dest.ptr<unsigned char>(i)[j]  = 0; }


//distanceTransform(imgGray,imgGray,CV_DIST_L2,3); 


        imshow("ruohua",dest);

distanceTransform(imgGray,imgGray,CV_DIST_L2,3); 


         max=0.0;
        for(int i=0;i<rows;i++)
                                for(int j=0;j<cols;j++)
                                                        {float value =  static_cast<float>( imgGray.ptr<unsigned char>(i)[j] );
                                                                                if(max<value)
                                                                                                                        max =value;
                                                                                                                                                }

                                                       for(int i=0;i<rows;i++)
                                                                                for(int j=0;j<cols;j++)
                                                                                                                                                                                                                                        {float value =  static_cast<float>( imgGray.ptr<unsigned char>(i)[j] );
                                                                                                                                                                                                                                                                                                                if(max/1.9>value)
                                                                                                                                                                                                                                                                                                                                                                                                          //                              max =value;

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             imgGray.ptr<unsigned char>(i)[j]  = 0; }


imshow("opencv ruohua",imgGray);

imshow("二值图像",imgGray);

waitKey(100000);

        
}
void fun_elaboration( const Mat &src)
{
        
        
}
int main()
{Mat src = imread("/home/june/opencv_test/dis_1.png");
Mat mask(7,7,CV_32FC1,Scalar(0));
for(int i=-3;i<4;i++)
        for(int j=-3;j<4;j++)
                mask.ptr<float>(i+3)[j+3] = abs(i)+abs(j);

        fun_distance(src,mask);
        return 0;
        }
