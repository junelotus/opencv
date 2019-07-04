#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
using namespace cv;
#define pai 3.14159
/* 这个文件 先通过图像创建hist，然后通过直方图创建计算EMD的参数signature，然后计算EMD*/
/*关于EMD算法的实现 会接下来了解 */


void calcHistFun(const Mat &src,SparseMat &hist)
{
int histSize[]={3,3,3};
const float range[] ={0,256};
const float * ranges[]= {range,range,range};
const int channels[] = {0,1,2};
 calcHist(&src,1,channels,Mat(),hist,3,histSize,ranges,true,false);
return ;



}
template<class T>
void createSignature(const SparseMat &hist,vector<T> & sig)
{SparseMatConstIterator_<float> it  = hist.begin<float>(), it_end = hist.end<float>();
int dims = hist.dims();
for(;it!=it_end;it++)
{
T curr;
float value = it.value<float>();
curr[0]=value;
const SparseMat::Node *node = it.node();
    
for(int i=0;i<dims;i++)
{
  // cout<<"i="<<i<<endl;
   curr[i+1] = node->idx[i];
 
}
 

sig.push_back(curr);
}

// for(int i=0;i<sig.size();i++)
// {

//     for(int j=0;j<2;j++)
//     cout<<sig.at<float>(i)[j]<<"  ";
//     cout<<endl;
// }

return ;
}


int main(int argc,char** argv)
{
if(argc<3)  return 0;
Mat src = imread(argv[1]);
SparseMat hist_1,hist_2;
calcHistFun(src,hist_1);
src = imread(argv[2]);
calcHistFun(src,hist_2);
int dims = hist_1.dims();
cout<<"dims="<<dims<<endl;
#define IS_THREE
#ifdef IS_THREE
vector<Vec4f> sig_1;
vector<Vec4f> sig_2;
#else
vector<Vec3f> sig_1;
vector<Vec3f> sig_2;
#endif // DEBUG 
 createSignature(hist_1,sig_1);
 createSignature(hist_2,sig_2);
 Mat sigg_1,sigg_2;
sigg_1 = Mat(sig_1).clone().reshape(1);//将图像改为单通道，保持行和列不变

for(int i=0;i<sig_1.size();i++)
{for(int j=0;j<4;j++)
cout<<sig_1[i][j]<<"  ";
cout<<endl;
}

cout<<endl;

for(int i =0;i<sigg_1.rows;i++)
{
    for(int j=0;j<sigg_1.cols;j++)
        cout<<sigg_1.ptr<float>(i)[j]<<" ";
        cout<<endl;
}
sigg_2 = Mat(sig_2).clone().reshape(1);




cout<<EMD(sigg_1,sigg_2,CV_DIST_L1)<<endl;
cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//18 *4 单通道


// cout<<Mat(sig_2).rows<<" "<<Mat(sig_2).cols<<endl;//没有reshape之前有18×1,4通道图像
// cout<<Mat(sig_2).channels()<<endl;
// cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后18×4 ，单通道图像
// cout<<sigg_2.channels()<<endl;
// cout<<endl;

// sigg_2 = Mat(sig_2).clone().reshape(2);
// cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后18×2 ，2通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// sigg_2 = Mat(sig_2).clone().reshape(3);
// cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后24*1 ，3通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// sigg_2 = Mat(sig_2).clone().reshape(4);
// cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后18×1 ，4通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;


// Mat test_shape(36,4,CV_32FC1);
// sigg_2 = test_shape.reshape(3);
// cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后48×1 ，3通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// {
//     Mat test_shape(48,3,CV_32FC2);
//     for(int i=0;i<48;i++)
//    { for(int j=0;j<3;j++)
//  {   test_shape.at<Vec2f>(i,j)[0]=(i*3+j)*2;
   
//    cout<<(i*3+j)*2<<"  ";
//    test_shape.at<Vec2f>(i,j)[1]=(i*3+j)*2+1;
//      cout<<(i*3+j)*2+1<<"  ";
//    }
// cout<<endl;}
// sigg_2 = test_shape.reshape(4);
// for(int i=0;i<sigg_2.rows;i++)
// {for(int j=0;j<sigg_2.cols;j++)
// cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
// cout<<endl;
// }cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后72×1 ，4通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// /*从 0 1   2 3    4 5
//      6 7   8 9   10 11
//      变成
//      0 1 2 3 
//     4 5 6 7 */
// }
// {
//     Mat test_shape(48,3,CV_32FC1);
//     for(int i=0;i<48;i++)
//    { for(int j=0;j<3;j++)
//  {   test_shape.ptr<float>(i)[j]=i*3+j;
   
//    cout<<i*3+j<<"  ";
//    }
// cout<<endl;}
// sigg_2 = test_shape.reshape(4);
// for(int i=0;i<sigg_2.rows;i++)
// {for(int j=0;j<sigg_2.cols;j++)
// cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
// cout<<endl;
// }cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后36×1 ，4通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// /*从 0 1 2
//      3 4 5
//      变成
//      0 1 2 3 
//     4 5 6*/
// }
// /*在opencv中，reshape函数比较有意思，它既可以改变矩阵的通道数，又可以对矩阵元素进行序列化，非常有用的一个函数。

// 函数原型：

// C++: Mat Mat::reshape(int cn, int rows=0) const

// 参数比较少，但设置的时候却要千万小心。

// cn: 表示通道数(channels), 如果设为0，则表示保持通道数不变，否则则变为设置的通道数。

// rows: 表示矩阵行数。 如果设为0，则表示保持原有的行数不变，否则则变为设置的行数。

// 首先设置一个初始矩阵：一个20行30列1通道的一个矩阵*/ 





// {
//     Mat test_shape(48,3,CV_32FC2);
//     for(int i=0;i<48;i++)
//    { for(int j=0;j<3;j++)
//  {   test_shape.at<Vec2f>(i,j)[0]=(i*3+j)*2;
   
//    cout<<(i*3+j)*2<<"  ";
//    test_shape.at<Vec2f>(i,j)[1]=(i*3+j)*2+1;
//      cout<<(i*3+j)*2+1<<"  ";
//    }
// cout<<endl;}
// sigg_2 = test_shape.reshape(1);
// for(int i=0;i<sigg_2.rows;i++)
// {for(int j=0;j<sigg_2.cols;j++)
// //cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
// cout<<sigg_2.at<float>(i,j)<<"  ";
// cout<<endl;
// }cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后48×6 ，1通道图像

// cout<<sigg_2.channels()<<endl;
// cout<<endl;
// /*0 1   2 3   4 5  //3通道
// 变成
//  0  1   2  3  4  5//6通道

// */
 
 //}





 return 0;

 }

