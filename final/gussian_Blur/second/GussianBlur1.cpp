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


void fun (int middle,Mat &dest,const Mat &src_copy,int i_,int j_,const vector<vector<double> >& core)
{
        double x =0.0;
        double y=0.0;
        double z=0.0;
        for(int i=0-middle;i<=middle;i++)
                for(int j=0-middle;j<=middle;j++)
                {//cout<<core[i+middle][j+middle]<<endl;
                        x+=core[i+middle][j+middle]*src_copy.at<Vec3b>(i_+i+middle,j_+j+middle)[0];
                        y+=core[i+middle][j+middle]*src_copy.at<Vec3b>(i_+i+middle,j_+j+middle)[1];
                        z+=core[i+middle][j+middle]*src_copy.at<Vec3b>(i_+i+middle,j_+j+middle)[2];
                        
                        
                        
                        }




                dest.at<Vec3b>(i_,j_)[0] = x;
                dest.at<Vec3b>(i_,j_)[1] =y;
                dest.at<Vec3b>(i_,j_)[2] =z;
        
        
        }
bool gussianBlur(const Mat & src,Mat& dest,int core_size,int rows_src,int cols_src,double sigma)
{

        int middle  = core_size/2;
        //Mat core(core_size,core_size,CV_8UC1.Scalar(0));
        vector<double> hang(core_size,0.0);
        vector<vector<double> > core(core_size,hang);
        double i=0.0,j=0.0;
        double first =1.0/2.0/pai/sigma/sigma;
        double sum =0.0;
        for(i = 0-middle;i<=middle;i++)
                 for(j=i;j<=middle;j++)
                 {
                        i =static_cast<double>(i); 
                         j =static_cast<double>(j);
                   double num = first *exp (-(i*i+j*j)/2.0/sigma/sigma);
                   core[i+middle][j+middle] = num;
                   core[j+middle][i+middle] =num;
                   sum+=num*(i==j?1:2);
if(i==j&&i==0)                         
 cout<<core[i+middle][j+middle]<<endl;                        
                         
                 }
        
for(i=0;i<core_size;i++)
        for(j=0;j<core_size;j++)
                core[i][j]/=sum;


Mat src_copy(rows_src+middle,cols_src+middle,CV_8UC3,Scalar(0,0,0));
/*
for(int i=0;i<rows_src+middle;i++)
	for(int j=0;j<middle;j++)
{

src_copy.at<Vec3b>(i,j)[0] = src.at<Vec3b>(i,0)[0];
src_copy.at<Vec3b>(i,j)[1] = src.at<Vec3b>(i,0)[1];
src_copy.at<Vec3b>(i,j)[2] = src.at<Vec3b>(i,0)[2];


}

for(int i=0;i<rows_src+middle;i++)
        for(int j=cols_src;j<cols_src+middle;j++)
{

src_copy.at<Vec3b>(i,j)[0] = src.at<Vec3b>(i,cols_src-1)[0];
src_copy.at<Vec3b>(i,j)[1] = src.at<Vec3b>(i,cols_src-1)[1];
src_copy.at<Vec3b>(i,j)[2] = src.at<Vec3b>(i,cols_src-1)[2];


}




for(int i=0;imiddle;i++)
        for(int j=middle;j<clos_src;j++)
{

src_copy.at<Vec3b>(i,j)[0] = src.at<Vec3b>(0,j)[0];
src_copy.at<Vec3b>(i,j)[1] = src.at<Vec3b>(0,j)[1];
src_copy.at<Vec3b>(i,j)[2] = src.at<Vec3b>(row_src-1,j)[2];


}

*/


//for(int i=0;i<middle;i++)
// src.copyTo(src_copy);




copyMakeBorder(src,src_copy,middle,middle,middle,middle,BORDER_REPLICATE);//ok//BORDER_CONSTANT not ok );//BORDER_REFLECT ok) ;


/*(for(i=0;i<rows_src;i++)
       for(j=middle;j<cols_src+middle;j++)
{
//memcpy(src_copy_addr,src_addr,cols_src*3);
src_copy.at<Vec3b>(i+middle,j)[0] = src.at<Vec3b>(i,j)[0];
src_copy.at<Vec3b>(i+middle,j)[1] = src.at<Vec3b>(i,j)[1];
src_copy.at<Vec3b>(i+middle,j)[2] = src.at<Vec3b>(i,j)[2];

}*/
        for(i=0;i<rows_src;i++)
                for(j=0;j<cols_src;j++)
                {
  fun (middle,dest,src_copy, i, j,core);                       
                        
                        
               }
        
        
        
}

int main()
{
        
         Mat src =imread("/home/user/june/test/timg.jpeg");
         imshow("dog",src);

        int rows = src.rows;
        int cols =src.cols;
        int core_size =5;
        int m = core_size /2;
        double sigma =2;
Mat dest(rows,cols,CV_8UC3,Scalar(0,0,0));
gussianBlur( src,dest,core_size,rows,cols,sigma);

 imshow("blur dog",dest);


Mat dstImage;
GaussianBlur(src,dstImage,Size(5,5),2,2);
 imshow("blur dog opencv ",dstImage);
waitKey(600000);
       return 0;
}
