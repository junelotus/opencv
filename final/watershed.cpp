/*
其中marksShow 中的图像边缘深浅不一，是因为在drawContours的时候　使用了不同的灰度来填充，并且使用了cv::convertScaleAbs来乘倍数并且平移（尽管这边使用的是默认参数a=1,b=0）
.不同的深度可以作为不同的种子,这一步是在findContours 之后的

使用findContours函数和drawContours函数，先找到轮廓再画出轮廓的方式属于比较老的方法、
现在有 cv::connectedComponents() 和函数 cv::connectedComponentsWithStats()函数来代替以上方法

int  cv::connectedComponents (
    cv::InputArrayn image,                // input 8-bit single-channel (binary)
    cv::OutputArray labels,               // output label map
    int             connectivity = 8,     // 4- or 8-connected components
    int             ltype        = CV_32S // Output label type (CV_32S or CV_16U)
    );
int  cv::connectedComponentsWithStats (
    cv::InputArrayn image,                // input 8-bit single-channel (binary)
    cv::OutputArray labels,               // output label map
    cv::OutputArray stats,                // Nx5 matrix (CV_32S) of statistics:
                                                          // [x0, y0, width0, height0, area0;
                                                          //  ... ; x(N-1), y(N-1), width(N-1),
                                                           // height(N-1), area(N-1)]
    cv::OutputArray centroids,            // Nx2 CV_64F matrix of centroids:
                                                           // [ cx0, cy0; ... ; cx(N-1), cy(N-1)]
    int             connectivity = 8,     // 4- or 8-connected components
    int             ltype        = CV_32S // Output label type (CV_32S or CV_16U)
    );
而centroids则对应的是中心点
而label则对应于表示是当前像素是第几个轮廓


*/

#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
 
#include <iostream>
 
using namespace cv;
using namespace std;
 
Vec3b RandomColor(int value);  //生成随机颜色函数
bool voidfind(int x,int y,vector<Point> v)
 {


	  
			double distance = pointPolygonTest(v, Point2f(y, x), true);
			 
		 if(distance>=0.0) {cout<<distance<<endl;return true;}
		 return false;
 
// 	int pxmax = -1;
// 	int pxmin=100000;
// 	int pymax =-1;
// 	int pymin=10000;
	

// 	for(int i=0;i<size;i++)
// 	{
		
// 		 if(v[i].y==x)
// 		 {
// 			 cout<<"wode"<<endl;
// 			 if(v[i].y>=pymax)
// 			 pymax= v[i].x;
// 			 if(v[i].y<=pymin)
// 			 pymin= v[i].x;
// 		 }
// 		 if(v[i].x ==y)
// 		 {
// 			 cout<<"nide"<<endl;
// 			 if(v[i].x>=pxmax)
// 			 pxmax= v[i].y;
// 			 if(v[i].x<=pxmin)
// 			 pxmin= v[i].y;

// 		 }

// 		 if(x>=pxmin &&x<=pxmax &&y>=pymin &&y<=pymax ) return true;
// 		 //cout<< x<<"  "<< pxmin<<" "<<pxmax<< " "<<y<<"  "<<pymin<<"  " <<pymax<< endl;
// 		 return false;

// 	}
	 


}

int  findWhich(int x,int y,vector<vector<Point>> contours)
{
	int size =contours.size();
	for(int i=0;i<size;i++)
		{
			if(voidfind(  x,  y,contours[i])) return i;


		}

return -1;
}
 
int main( int argc, char* argv[] )
{
	Mat image=imread(argv[1]);    //载入RGB彩色图像
	imshow("Source Image",image);
 
	//灰度化，滤波，Canny边缘检测
	Mat imageGray;
	cvtColor(image,imageGray,CV_RGB2GRAY);//灰度转换
	GaussianBlur(imageGray,imageGray,Size(5,5),2);   //高斯滤波
	imshow("Gray Image",imageGray); 
	Canny(imageGray,imageGray,80,150);  
	imshow("Canny Image",imageGray);
 
	//查找轮廓
	vector<vector<Point>> contours;  
	vector<Vec4i> hierarchy;  
	 cv::Mat element(5,5,CV_8U,cv::Scalar(255));
		   cv::dilate(imageGray,imageGray,element);
	findContours(imageGray,contours,hierarchy,CV_RETR_TREE , CV_CHAIN_APPROX_NONE,Point()); 
    
Mat PerspectiveImagea=Mat::zeros(image.size(),CV_8UC3);
	for(int i=0;i<image.rows;i++)
	{
		for(int j=0;j<image.cols;j++)
		{
			 int t = findWhich(i,j,  contours); 
			 if(t==-1)
			 PerspectiveImagea.at<Vec3b>(i,j) = image.at<Vec3b>( i,j);
			 else
			//std::cout<<t<<endl;
			PerspectiveImagea.at<Vec3b>(i,j) = image.at<Vec3b>( contours[t][0].y,contours[t][0].x);
			 
		}
	}
	imshow("june",PerspectiveImagea);


	Mat imageContours=Mat::zeros(image.size(),CV_8UC1);  //轮廓	
	Mat marks(image.size(),CV_32S);   //Opencv分水岭第二个矩阵参数
	marks=Scalar::all(0);
	int index = 0;
	int compCount = 0;
	for( ; index >= 0; index = hierarchy[index][0], compCount++ ) 
	{
		//对marks进行标记，对不同区域的轮廓进行编号，相当于设置注水点，有多少轮廓，就有多少注水点
		drawContours(marks, contours, index, Scalar::all(10+compCount), 1, 8, hierarchy);
		drawContours(imageContours,contours,index,Scalar(255),1,8,hierarchy);  
	}

	std::cout<<contours.size()<<std::endl;
 
	//我们来看一下传入的矩阵marks里是什么东西
	Mat marksShows;
	convertScaleAbs(marks,marksShows);
	imshow("marksShow",marksShows);
	imshow("轮廓",imageContours);
	
//cv::Mat  img_edge, labels, img_color, stats,centroids;

//connectedComponentsWithStats ( img_edge, marks, stats, centroids);
	watershed(image,marks);
 
	//我们再来看一下分水岭算法之后的矩阵marks里是什么东西
	Mat afterWatershed;
	convertScaleAbs(marks,afterWatershed);
	imshow("After Watershed",afterWatershed);
 
	//对每一个区域进行颜色填充
	Mat PerspectiveImage=Mat::zeros(image.size(),CV_8UC3);
	for(int i=0;i<marks.rows;i++)
	{
		for(int j=0;j<marks.cols;j++)
		{
			 //int t = findWhich(i,j,  contours);
			int index=marks.at<int>(i,j); 
			if(marks.at<int>(i,j)==-1)
			{
				PerspectiveImage.at<Vec3b>(i,j)=Vec3b(255,255,255);
			}			 
			else
			{
				PerspectiveImage.at<Vec3b>(i,j) =RandomColor(index);
			}
		}
	}
	imshow("After ColorFill",PerspectiveImage);
 
	//分割并填充颜色的结果跟原始图像融合
	Mat wshed;
	addWeighted(image,0.4,PerspectiveImage,0.6,0,wshed);
	imshow("AddWeighted Image",wshed);
 
	waitKey();
}
 
Vec3b RandomColor(int value)    //<span style="line-height: 20.8px; font-family: s//ans-serif;">//生成随机颜色函数</span>
{
	value=value%255;  //生成0~255的随机数
	RNG rng;
	int aa=rng.uniform(0,value);
	int bb=rng.uniform(0,value);
	int cc=rng.uniform(0,value);
	return Vec3b(aa,bb,cc);
}
