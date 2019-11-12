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

int main()
{
Mat src = imread("/home/user/june/test/woman.png");

imshow("original",src);
int rows = src.rows;//行
int cols  =src.cols;//列
cout<<"输入极坐标原点,用分数表示:"<<endl;
Point2f center(rows,cols);

cin>>center.x >>center.y;

center.x *= rows;
center.y *=cols;


float  max1_cols = std::max(sqrt(center.x*center.x+center.y*center.y ), sqrt(center.x*center.x+(center.y-cols)*(center.y-cols) )  );

float max2_cols =std::max(sqrt((center.x-rows)*(center.x-rows)+center.y*center.y ) ,sqrt((center.x-rows)*(center.x-rows) +(center.y-cols)*(center.y-cols)));


float dest_cols = std::max(max1_cols+1,max2_cols+1 );

cout<<dest_cols<<endl;

//float max1_rows = 
//float max2_rows = 

Mat dest(360,dest_cols,CV_8UC3,Scalar(0,0,0));
for(int i=0;i<rows;i++)
	for(int j=0;j<cols;j++)
{
int y = sqrt((i-center.x)*(i-center.x)+(j-center.y)*(j-center.y));
int x =(pai+atan2(j-center.y,i-center.x))/2.0/pai*360.0;//(arctan(static_cast<double>(j)/static_cast<double>(i)));
//cout<<"zuobiao"<<x<<" "<<y<<endl;
for(int k=0;k<3;k++)
dest.at<Vec3b>(x,y)[k] = src.at<Vec3b>(i,j)[k];


}
cout<<"wode"<<endl;
imshow("original",src);
imshow("topolar",dest);
waitKey(100000);
return 0;


}





