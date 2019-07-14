#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include "findContour.hpp"
using namespace std;
using namespace cv;
#define pai 3.14159
/*关于轮廓矩的计算,首先都要先计算出轮廓*/

/*第一个函数用来找到矩的运算*/
int match_method =0 ;
 
int max_trackbar = 255;

/*https://www.cnblogs.com/zuochanzi/p/7159108.html*/
double  fun_m00(const vector<Point> &contour_first,const Mat &gray)
{
size_t size = contour_first.size();

double re =0.0;
for(auto i=0;i<size;i++)
{
    Point p = contour_first[i];
    re+=static_cast<unsigned int>(gray.at<unsigned char>(p.y,p.x));//e二值的前景为255

}
    
return re/255.0;

}



double  fun_img_m00(const Mat &gray)
{
 

double re =0.0;
for(auto x=0;x<gray.rows;x++)
    for(auto y=0;y<gray.cols;y++)
{ 
    re+=static_cast<unsigned int>(gray.at<unsigned char>(x,y));//e二值的前景为255

}
    
return re/255.0;

}



double  fun_img_m10(const Mat &gray)
{
 

double re =0.0;
for(auto x=0;x<gray.rows;x++)
    for(auto y=0;y<gray.cols;y++)
{ 
    re+=static_cast<unsigned int>(gray.at<unsigned char>(x,y))/255.0 *static_cast<double>(x);//e二值的前景为255

}
    
return re;

}



double  fun_img_m01(const Mat &gray)
{
 

double re =0.0;
for(auto x=0;x<gray.rows;x++)
    for(auto y=0;y<gray.cols;y++)
{ 
    re+=static_cast<unsigned int>(gray.at<unsigned char>(x,y)) /255.0*static_cast<double>(y);//e二值的前景为255

}
    
return re;

}

double  fun_m10(const vector<Point> &contour_first,const Mat &gray)
{
size_t size = contour_first.size();

double re =0.0;
for(auto i=0;i<size;i++)
{
    Point p = contour_first[i];
    re+=static_cast<unsigned int>(gray.at<unsigned char>(p.x,p.y)) *p.x;

}
    
return re/255.0;

}


void fun_ContourMoments()
{
     on_trackbar();
     /*首先通过轮廓获得矩的 */
     //CvMoments *moments;
     size_t size = contours.size();
     vector<Moments> contours_moments(size);
	 vector<Point2f> centers(size);
	 int wode  =0;

     for (size_t i = 0; i < contours.size(); i++)
	{
        wode+=contours[i].size();
	 
		contours_moments[i] = moments(gray,1); //计算每个轮廓矩，传入的参数可以是图像，矩的计算，看到源码 应该是按照 p297页的公式计算的，但p和q全部为0时，因为图像是二值图像，所以表示的边界上的像素点的值的和，也是边界上像素点的个数
        //contourMoments
		centers[i] = Point(static_cast<float>(contours_moments[i].m10 / contours_moments[i].m00), static_cast<float>(contours_moments[i].m01 / contours_moments[i].m00));
        	//图像中心Center(x0, y0)=(m10/m00,m01/m00)
    }
    /*计算m00 m01 和contours_moments[0][0]和contours_moments[0][1] 分别做比较*/
cout<<"wode ="<<wode <<endl;

cout<<fun_m00(contours[0],gray) <<"  "<<contours[0].size()<<endl;
cout<<"opencv result = "<<contours_moments[0].m00<<endl;
cout<<"img result  "<<fun_img_m00(gray)<<endl;//由函数fun_img_m00 和moments，传入参数为二值图像可知，moments计算出来是图像的矩，moo表示的是这个图相中前景区域的像素点的个数
cout<<centers[0].x<<"  "<<centers[0].y<<endl;
cout<<static_cast<int>(fun_img_m10(gray)/fun_img_m00(gray))<<"  "<<static_cast<int>(fun_img_m01(gray)/fun_img_m00(gray))<<endl;//从此向上的2行计算记过是一致的，说明图像的距就是按照p279处定义来的，
//此函数计算的是图像的距，此例中的轮廓是用vector<vector<Point>>存储的，如果想计算轮廓的距，首先要把vector转换成seq
//  cvGetSpatialMoment
//  cvGetCentralMoment
/*hu矩具有平移 缩放 旋转不变性，普通距(p279)中心距(p281)不能是物体具有平移旋转比例不变性，归一化中心距 有平移和比例不变性 */
/*利用hu距进行匹配 */
cout<<matchShapes(gray,gray_d,1,0)<<endl;//必须单通道，（包含二值图像在内）
// convexHull
// convexityDefects

}
int main(int argc,char** argv)
{
    if(argc<3) return 0;
    src = imread(argv[1]);
    dest = imread(argv[2]);
    fun_ContourMoments();
  
    return 0;


}
