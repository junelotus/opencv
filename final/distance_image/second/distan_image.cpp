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
void overwrite_distance_fun(const Mat& imggray,const Mat & mask,Mat &dest)
{

int rows = imggray.rows;
int cols = imggray.cols;
int mask_rows = mask.rows;
int m = mask_rows/2;
float min =1000.0;
Mat dest_copy(dest.size(),CV_32FC1);



for(int i=m;i<rows+m;i++)
  for(int j=m;j<cols+m;j++)
	{ 
	float value = static_cast<float>(dest.at<float>(i,j)); 
	if(value ==0) continue;
	min=value;
	for(int ii =0-m;ii<=m;ii++ )
		for(int jj=0-m;jj<=m;jj++)
	{
		if(min>mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj) ))
 			min=mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj));	
		
		
	}	
	//	if(min!=1000.0)
		 dest.at<float>(i,j) = min;
	//min =1000.0;




	}


for(int i=rows-1+m;i>=m;i--)
  for(int j=cols-1+m;j>=m;j--)
        {
        float value = static_cast<float>(dest.at<float>(i,j));
        if(value ==0) continue;
	min =value;
        for(int ii =0-m;ii<=m;ii++ )
                for(int jj=0-m;jj<=m;jj++)
        {
                if(min>mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj) ))
                        min=mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj));


        }
           //     if(min!=1000.0)
                 dest.at<float>(i,j) = min;
       // min =1000.0;




        }




}


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
         dest.ptr<float>(i)[j] =static_cast<float>( imgGray.ptr<unsigned char/*8u to deal*/>(i-3)[j-3]);// ==0?0:255);

//if()
//cout<< imgGray.ptr<unsigned int>(i-3)[j-3]<<endl;
}

       


imshow("二值图像bigger",dest);
/*
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
                       float value = static_cast<float>( imgGray.ptr<unsigned char>(i+ii)[j+jj] );
                                if(value==0)
                                {
                                        if(min_>mask.ptr<float>(3+ii)[3+jj] )
                                                min_ = mask.ptr<float>(3+ii)[3+jj];
                                        }


    

                                                
                                                
                                               

                        //else not 0        
                                
                                }
cout<<"min_="<<min_<<endl;
			if(min_!=100000.0)
                           dest.ptr<float>(i)[j] = min_;     
                        
                            min_ =100000.0;                        
                        
                }
                
                
                
                }

//Mat 
min_ =100000.0;
                
for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
        {
                 if(dest.ptr<float>(i)[j]!=0.0)
                 {
                         
                         for(int ii=-3;ii<=3;ii++)
                         for(int jj =-1;jj<=3;jj++)
                          {//if 0
                            float value = static_cast<float>( imgGray.ptr<unsigned char>(i+ii)[j+ii] );
                            if(value!=0)                                                                                                            
                            {
                                    
                                    if(dest.ptr<float>(i)[j]>value+mask.ptr<float>(3+ii)[3+jj])
                                            min_ = value+mask.ptr<float>(3+ii)[3+jj];
                                    
                                    
                                    
                                    }

				if(min_!=100000.0)
                                    dest.ptr<float>(i)[j] = min_;

                                    min_ =100000.0;

                                    
                                    }
                         
                         
                         }
                
                
                
                
        }


for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
        {
                 if(dest.ptr<float>(i)[j]!=0.0)
                 {

                         for(int ii=-3;ii<=3;ii++)
                         for(int jj =-1;jj<=3;jj++)
                          {//if 0
                            float value = static_cast<float>( imgGray.ptr<unsigned char>(i+ii)[j+ii] );
                            if(value!=0)                                                                            
                            {

                                    if(dest.ptr<float>(i)[j]>value+mask.ptr<float>(3+ii)[3+jj])
                                            min_ = value+mask.ptr<float>(3+ii)[3+jj];



                                    }

                                if(min_!=100000.0)
                                    dest.ptr<float>(i)[j] = min_;

                                    min_ =100000.0;


                                    }


                         }




        }

        float max=0.0;
for(int i=3;i<rows+3;i++)
                for(int j=3;j<cols+3;j++)
                {float value =  static_cast<float>( dest.ptr<float>(i)[j] );
                        if(max<value)
                                max =value;
                        }

for(int i=3;i<rows+3;i++)
                        for(int j=3;j<cols+3;j++)
                                                {float value =  static_cast<float>( dest.ptr<float>(i)[j] );
                                                                        if(max/1.9>value)
                                                                                  //                              max =value;
                                                                                    
                                                                                   dest.ptr<float>(i)[j]  = 0; }

*/
//distanceTransform(imgGray,imgGray,CV_DIST_L2,3); 
overwrite_distance_fun(imgGray, mask,dest);


float  max =0.0;
 max=0.0;
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
              {
                float value =  static_cast<float>( dest.ptr<float>(i)[j] );
                if(max<value)

                     max =value;

              }

Mat distShow=Mat::zeros(imgGray.size(),CV_8UC1); //定义细化后的字符轮廓
     for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)


  {
        float value =  static_cast<float>( dest.ptr<float>(i)[j] );

              if(max/1.9<value)



                                                 //                              max =value;





                 dest.ptr<float>(i)[j]  =255 ;

else 
 dest.ptr<float>(i)[j]  =0 ;


 }



        imshow("ruohua",dest);






Mat imageThin(imgGray.size(),CV_32FC1); //定义保存距离变换结果的Mat矩阵  
distanceTransform(imgGray,imageThin,CV_DIST_L2,3);  //距离变换  
//distanceTransform(imgGray,imgGray,CV_DIST_L2,3); 


          max=0.0;
        for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
              {
		float value =  static_cast<float>( imageThin.ptr<float>(i)[j] );
                if(max<value)
                                                                                                                        		max =value;
                                                                                                                                 }
//Mat distShow=Mat::zeros(imgGray.size(),CV_8UC1); //定义细化后的字符轮廓
     for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
                                                                                                                                                                                                                                        {
	float value =  static_cast<float>( imageThin.ptr<float>(i)[j] );
                                                                                                                                 if(max/1.9<value)
                                                                                                                                                                                                                                                                                                                                                                                                          //                              max =value;

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             distShow.ptr<unsigned char>(i)[j]  =255 ; }


imshow("opencv ruohua",distShow);


imshow("二值图像",imgGray);

waitKey(100000);

        
}
void fun_elaboration( const Mat &src)
{
        
        
}
int main()
{Mat src = imread("/home/user/june/test/opencv/distance_image/dis_1.png");
Mat mask(7,7,CV_32FC1,Scalar(0));
mask.at<float>(0,0) =4.5;
mask.at<float>(0,1) =4;
mask.at<float>(0,2) =3.5;
mask.at<float>(0,3) =3;

mask.at<float>(1,0) =4;
mask.at<float>(1,1) =3;
mask.at<float>(1,2) =2.5;
mask.at<float>(1,3) =2;

mask.at<float>(2,0) =3.5;
mask.at<float>(2,1) =2.5;
mask.at<float>(2,2) =1.5;
mask.at<float>(2,3) =1;

mask.at<float>(3,0) =3;
mask.at<float>(3,1) =2;
mask.at<float>(3,2) =1;
mask.at<float>(3,3) =0;
for(int i=4;i<7;i++)
 for(int j=0;j<4;j++)
	mask.at<float>(i,j) = mask.at<float>(7-i-1,j);

for(int i=0;i<7;i++)
 for(int j=4;j<7;j++)
	mask.at<float>(i,j) = mask.at<float>(i,7-j-1); 



//for(int i=-3;i<4;i++)
  //      for(int j=-3;j<4;j++)
    //            mask.ptr<float>(i+3)[j+3] = abs(i)+abs(j);

        fun_distance(src,mask);
        return 0;
}
