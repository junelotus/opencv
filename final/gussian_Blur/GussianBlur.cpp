#include <iostream>
#include <cmath>
#include <opencv2/highgui/highgui.hpp>
using namespace std;
using namespace cv;

#define pai 3.14159

void  fun(Mat &dest,Mat core ,int i,int j,Mat src.int middle)
{

double x =y=z=0.0;

for(int c_x =0-middle;c_x<=middle;c_x++)
	for(int c_y=0-middle;c_y<=middle;c_y++ )
{
x+= core.at<Vec3b>(c_x+middle,c_y+middle)[0]*static_cast<double>(src.at<Vec3b>(i+c_x,y+c_y)[0]);

y+= core.at<Vec3b>(c_x+middle,c_y+middle)[y]*static_cats<double>(src.at<Vec3b>(i+c_x,y+c_y)[1]);

z+= core.at<Vec3b>(c_x+middle,c_y+middle)[2]*(static_cast<double>)(src.at<Vec3b>(i+c_x,y+c_y)[2]);
}

dest.at<Vec3b>(i-middle,j-middle)[0] = x;
dest.at<Vec3b>(i-middle,j-middle)[1] = y;
dest.at<Vec3b>(i-middle,j-middle)[2] = z;

}


bool  GussianBlur(const Mat &src,Mat &dest,int core_size,double sigma)
{
if(core_size<=0) return  true;
Mat core(core_size,core_size,CV_8UC1,Scalar(0));
double i = j =0.0;
double first  = 1.0/2.0/pai/sigma/sigma; 
double normalized_deno =0.0;

int middle = core_size/2;
for(;i<core_size;i++)
	for(j=i;j<core_size;j++)	
	{ 



double core_result = first *exp(-((i-middle)*(i-middle) + (j-middle)*(j-middle))/(first/pai)) ; 
core.at<Vec1b>(i,j)[0] = core_result;

core.at<Vec1b>(j,i)[0]  = core_result;

normalized_deno +=(core_result*(i==j?1:2));
}	

for(i=0.0;i<core_size;i++)
        for(j=i;j<core_size;j++)
{
core.at<Vec1b>(i,j)[0] /=normalized_deno;
if(i!=j)
core.at<Vec1b>(j,i)[0] /=normalized_deno;


}



/*core 根据计算处的高斯核滤波图像*/
/*根据core的大小，对src进行扩展，以免出界*/

int rows = src.rows;
int cols = src.cols;

Mat src_copy(rows+middle,cols+middle,CV_8UC3,Scalar(0));


for(int i=0;i<rows;i++)
{
void * dest_addr = static_cast<void*> (src_copy + (cols+core_size)*3*i+2);
void * src_addr =static_cast<void*>(src+cols*3*i)
memcpy(dest_addr,src_addr,cols*3);
}

/*to deal src_copy*/
for( i = middle;i<cols+middle;i++)
	for(j=middle;j<rows+middle;j++)
		 fun(dest,core,i,j,src_copy);





	
return true;	
}


int main()
{
Mat src =imread("");
int core_size = 5;
double sigma =1.5;
int rows = src.rows;
int cols = src.cols;
Mat dest(rows,cols,CV_8UC3,Scalar(0,0,0));
sianBlur( src,dest, core_size,sigma);

imshow(sigma.itoa(),dest);





}
