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
void overwrite_distance_fun(const Mat & mask,Mat &dest)
{//dest是扩大了的imggary的数组，用于掩模的扫描
/*从左上角到右下角　从右下角到左上角各掩模一边*/
int mask_rows = mask.rows;
int m = mask_rows/2;
int rows = dest.rows-mask_rows;
int cols = dest.cols-mask_rows;
//int mask_rows = mask.rows;
//int m = mask_rows/2;
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
	{  // float value = static_cast<float>(dest.at<float>(i+ii,j+jj) );
	//	if(value!=0) continue;
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

}

       


imshow("二值图像bigger",dest);
/*

*/
//distanceTransform(imgGray,imgGray,CV_DIST_L2,3); 
overwrite_distance_fun( mask,dest);


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


void find_center( const Mat &src,const Mat &mask)
{
       // Mat dest (src.size(),Scalar(0));
        int rows = src.rows;
        int cols =src.cols;
        Mat dest(rows+6,cols+6,CV_32FC1,Scalar(0));//
        Mat imgGray;
        cvtColor(src,imgGray,CV_RGB2GRAY);  //灰度化
        imgGray =~imgGray;
        GaussianBlur(imgGray,imgGray,Size(5,5),2);
        threshold(imgGray,imgGray,20,255,CV_THRESH_BINARY);
/*threshold 函数将图像二值化，第五个参数为THRESH_BINARY 或THRESH_BINARY_INV时，第四个参数表示用来设置前景区域的值*/
        rows = imgGray.rows;
        cols = imgGray.cols;
        
/*        eaussianBlur(imgGray,imgGray,Size(5,5),2);
        threshold(imgGray,imgGray,20,200,CV_THRESH_BINARY);

        rows = imgGray.rows;
        cols = imgGray.cols;
*/
        int m = mask.rows/2;
       //copyMakeBorder(imgGray,dest,m,m,m,m,BORDER_REPLICATE);
        
for(int i=3;i<rows+3;i++)
        for(int j=3;j<cols+3;j++)
                 {
                                  dest.ptr<float>(i)[j] =static_cast<float>( imgGray.ptr<unsigned char/*8u to deal*/>(i-3)[j-3]);// ==0?0:255);

                 }

        overwrite_distance_fun(mask,dest);

      imshow("own distance result",dest); 
       
       float max=0.0;
        Point p(0,0);
        for(int i=0;i<dest.rows;i++)
                for(int j=0;j<dest.cols;j++)
                         {
                                 float  value = dest.at<float>(i,j);
                          if(max<value)
                                       {  max=value;
                                          p.x= j;p.y=i;
                                 }
                                 }
circle(dest, p, 10, Scalar(0,0,0));
cout<<p.x<<" "<<p.y<<endl;
imshow("center original",src);
        imshow("center result",dest);
//Mat imageThin;
 Mat imageThin(imgGray.size(),CV_32FC1); 
 distanceTransform(imgGray,imageThin,CV_DIST_L2,3);  //距离变换 
//imshow("center original",src);
       
       imshow("opencv distance result",imageThin);
       
       max =0.0;
       for(int i=0;i<imageThin.rows;i++)
               for(int j=0;j<imageThin.cols;j++)
               {
                       float value =imageThin.at<float>(i,j);
                      // if(value!=0)
                     //          cout<<value<<endl;
                      if(max<value)
                       {
                               max =value;
                               p.x =j;
                               p.y=i;
                               }
                       
                       }
         normalize(imageThin,imageThin,0,255,CV_MINMAX);
         cout<<p.x<<" "<<p.y<<endl;
          circle(imageThin, p, 10, Scalar(0,0,0));    
               imshow("opencv result",imageThin);


waitKey(100000);





        




        
}
int main()
{Mat src = imread("dis_1.png");
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

       // fun_distance(src,mask);
       
 Mat      src_center= imread("../dis_2.jpg");
       find_center(src_center,mask);
  /*
 int rows = src.rows;
 int cols =src.cols;
 Mat dest(rows+6,cols+6,CV_32FC1,Scalar(0));//
 Mat imgGray;
 cvtColor(src,imgGray,CV_RGB2GRAY);  //灰度化
 imgGray =~imgGray;
 GaussianBlur(imgGray,imgGray,Size(5,5),2);
 threshold(imgGray,imgGray,20,200,CV_THRESH_BINARY);

    Mat imageThin(imgGray.size(),CV_32FC1); //定义保存距离变换结果的Mat矩阵
        distanceTransform(imgGray,imageThin,CV_DIST_L2,3);  //距离变换
float max=0;
Point p(0,0);
for(int i=0;i<imageThin.rows;i++)
        for(int j=0;j<imageThin.cols;j++)
        {
                float value  = imageThin.at<float>(i,j);
                if(max<value)
                       {max=value;
                       p.x =j;
                       p.y=i;
                               
                               }          
                
                }
cout<<p.x<<"  "<<p.y<<endl;
normalize(imageThin,imageThin,0,255,CV_MINMAX);
circle(src,p,10,Scalar(0));
imshow("Thin Image",src);
  
  
    /*Mat distShow;
        Point Pt(0,0);
        float maxValue=0;
        distShow=Mat::zeros(imgGray.size(),CV_8UC1); //定义细化后的字符轮廓
            for(int i=0;i<imageThin.rows;i++)
                        {
                                        for(int j=0;j<imageThin.cols;j++)
                                                        {
                                                                            distShow.at<uchar>(i,j)=imageThin.at<float>(i,j);
                                                                                        if(imageThin.at<float>(i,j)>maxValue)
                                                                                                            {
                                                                                                                                    maxValue=imageThin.at<float>(i,j);  //获取距离变换的极大值
                                                                                                                                                    Pt=Point(j,i);  //坐标
                                                                                                                                                                }
                                                                                                                                                                        }
                                                                                                                                                                            }
                                                                                                                                                                                normalize(distShow,distShow,0,255,CV_MINMAX); //为了显示清晰，做了0~255归一化
                                                                                                                                                                                    circle(src,Pt,maxValue,Scalar(0,0,255),3);    
                                                                                                                                                                                        circle(src,Pt,3,Scalar(0,255,0),3);
                                                                                                                                                                                            imshow("Source Image",src);
                                                                                                                                                                                                imshow("Thin Image",distShow);
 */ waitKey(10000);








       
       return 0;
}
