# opencv
learning opencv
https://docs.opencv.org/trunk/
## Bilinear: 
从dest图像计算出原图像对应的坐标，此坐标很大概率上是浮点数，取这个浮点坐标最近的四联通坐标（x1,y1）(x1,y2)(x2,y1)(x2,y2)
作出以下两步运算，f(x,y)即为dest上（x,y）点的坐标：
1 f(x,y1)  = (x2-x)/(x2-x1)*f(x1,y1) +(x-x1)/(x2-x1)*f(x2,y1)
  f(x,y2) =  (x2-x)/(x2-x1)*f(x1,y2) +(x-x1)/(x2-x1)*f(x2,y2)
2 f(x,y) = (y2-y)/(y2-y1)*f(x,y1) + (y-y1)/(y2-y1)*f(x,y2)，其中x 和y均作为浮点是来使用。
上述两部计算可以简化为一个公式  ：
 f(x,y) = (1/((x2-x1)*(y2-y1)))/(f(x1,y1)*(x2-x)*(y2-y) + f(x2,y1) *(x-x1)*(y2-y) + f(x1,y2) *(x2-x)*(y-y1) + f(x2,y2)*(x-x1)*(y-y1))
### 我觉得并没有图像中心不对其，而导致有些像素无法加入运算的问题。
### 距离图像
使用掩模（对称的距离矩阵）mask扫描二值图像dest两遍，从左上角到右下角，再从右下角到左上角，更新二值图像的value用：
if(min>mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj) ))
           min=mask.at<float>(ii+m,jj+m)+static_cast<float>(dest.at<float>(i+ii,j+jj));
### threshold函数
   threshold(imgGray,imgGray,20,255,CV_THRESH_BINARY);
/*threshold 函数将图像二值化，第五个参数为THRESH_BINARY 或THRESH_BINARY_INV时，第四个参数表示用来设置前景区域的值*/
### point 
  point.y 行的值
  point.x 列的值

## 椒盐噪声
在图像上随机黑白点的噪声
## CV_32FU3
每个像素值在0.0到1.0之间，尺度因子为１。
## cv_32F和cv_32FU1之间的区别
CV_32F is defined as:

 #define CV_32F  5

while CV_32FC1 is defined as:

#define CV_CN_SHIFT   3
#define CV_DEPTH_MAX  (1 << CV_CN_SHIFT)／／８
#define CV_MAT_DEPTH_MASK       (CV_DEPTH_MAX - 1)／／７
#define CV_MAT_DEPTH(flags)     ((flags) & CV_MAT_DEPTH_MASK)　／／掩码７
#define CV_MAKETYPE(depth,cn) (CV_MAT_DEPTH(depth) + (((cn)-1) << CV_CN_SHIFT))　５＋（０<<3）=5

#define CV_32FC1 CV_MAKETYPE(CV_32F,1)


#include <opencv2\opencv.hpp>
#include <iostream>
int main()
{
    std::cout <<  CV_32F << std::endl;／／５
    std::cout <<  CV_32FC1 << std::endl;／／５

    return 0;
}

## 直方图均衡化
equalhist:图像增强
https://www.cnblogs.com/yoyo-sincerely/p/6159101.html

## 直方图函数calHist
void calcHist(const Mat* images, 
int nimages, 
const int* channels, 
InputArray mask, 
SparseMat& hist,
int dims, 
const int* histSize, 
const float** ranges, 
bool uniform=true, 
bool accumulate=false)
(1)images:是一个图像数组,所以传参的时候,要传一个地址(一幅图用&src,多幅图的话,放在数组中,传入数组名)

(2)nimages:就是上一个中的图像总数

(3)channels:用来计算直方图的通道维数数组,第一个数组的通道由0到arrays[0].channels()-1列出，第二个数组的通道从arrays[0].channels()到arrays[0].channels()+arrays[1].channels()-1以此类推;(其实不太懂什么意思,求教)

(4)mask:一个掩码,用来选择图像中参与hist统计的像素,0表示参加计算.一般用Mat(),表示全部参与

(5)hist,直接传入即可(为传引用,也不用取地址),经计算后变成一个dims维的矩阵

(6)dims,维数  CV_MAX_DIMS ==32,最大的

(7)histSize,就是每一维的bins的个数,也要传入地址 eg.二维的int histSize={bins_1,bins_2};

(8)ranges 对于均匀直方图(即nuiform==true),ranges是一个由dims个float数对构成的数组,数对表示对应维的bin的范围.  eg.某维有N==2个bins,在ranges中对应的数对为{0,10},均匀的意思是讲,将该维的bin均匀的非为N==2个区间:[0,5]和[5,10],这是程序自动划分的,只需提供给他数对表示最值范围即可.

   对于非均匀的直方图,ranges的组成元素就不在是简单的数对了,而是一个个子数组,每个数组还有N+1个元素(N为该维的bin的数量),这N+1个元素将表示怎样对bin进行非均匀的划分.    eg.某维N==4个bins,ranges中对应的字数组为5个元素{0,2,4,9,10},非均匀的意思就是讲,讲该bin划分为非均匀区间[0,2],[2,4][4,9].[9,10]. 然后根据区间统计落在每个区间中的数量,从而计算出直方图.
(9)nuiform是否均匀,对应ranges中元素的不同表示.如上.
 (10)accumulate一般为false,为TRUE时,在calchist中给hist分配内存时hist不会被清除,从而可以将多幅图的直方图统计到一个hist矩阵中.  或者有利于及时的更新直方图(不懂什么意思).

Example:
1.int histSize[] ={2};
  float range[] = { 0,1,2};
  const float* histRange[] ={range};//,range_1};
  bool uniform = false, accumulate = false;
  calcHist( &channels.at(0), 1, 0, Mat(), h_hist, 1, histSize, histRange, false, accumulate );
其中&channels.at(0)表示单通道图像的指针，
1 表示图像的总数
0表示只有一个图像通道数目表示，用来计算直方图的通道维数数组，1表示取多个图像中的中的第一个通道，
Mat()表示掩码为空
h_hist表示计算出来的直方图
1表示直方图为1维的直方图
histRange数组大小为1,表示直方图只有一维，histRange[0]==2表示第一维上有两个bin
histRange是使用range来初始化的，histRange的数组大小也表示维度，每个子数组表示此维度上bin的上写界限，如果要均匀的分为histRange[i]个bin，字数子即range中是两个数，表示上下界，且nuiform为true
此函数表示用图像建立以为直方图，直方图有两个bin，上下界限分别为[0,1)[1,2)
channels参数：  channels。用来计算直方图的channes的数组。比如输入是2副图像，第一副图像有0，1，2共三个channel，第二幅图像只有0一个channel，

那么输入就一共有4个channes，如果int channels[3] = {3, 2, 0}，那么就表示是使用第二副图像的第一个通道和第一副图像的第2和第0个通道来计
dims 的大小要小于channels数组的大小，channels中的通道表示每一个维度，用channels[i]表示的通道里的数值计算直方图的第i维。

在nuiform为false时，第六个参数最好是1,计算维度为1的直方图，使用mat存储，多维的话 返回的值和真实值有偏差,使用稀疏矩阵存储，也没有正确输出
SparseMat:稀疏矩阵,使用稀疏矩阵遍历的迭代器遍历的时候，只能输出非0值的选项
稀疏矩阵opencv链接：https://docs.opencv.org/trunk/dd/da9/classcv_1_1SparseMat.html

在nuiform为true表示均匀分布的时候，第六哥参数可以是计算多维的，可以大于等于1 ，为3之类的，可以用稀疏矩阵或者MatND得到hist。
nuiform==true:
当 histSize[] ={3,3}说明是2维的直方图，每一维度有3个bin
 range[] = { 0,256};range_1={0,180};const float* histRange[] ={range,range_1};说明把第一个维度每个维度的宽度为256/3,第二个维度每个宽度为180/3,将函数的第六哥参数设置为2,计算出来的直方图是二维的，坐标为[0,1,2]*[0,1,2]义工九个区间，用二维坐标图可以看到九个区间的横纵区间的意义（已经验证在test_hist_qujian.cpp中）,例如二维坐标的左下角的 表示第一个通道在[0,86)((256+3)-1/3-1==85,85为上界限)第二个通道在[0,60)((180+3-1)/3-1==59,为上界限,即为不大于商的整数，已经验证在test_hist_qujian.cpp中)范围内的坐标的个数;如果histSize[] ={1,1} 二维直方图只有一个区间，是图像像素个数的和，不是图像像素个数×通道数
利用range统计的的时候 上限是不包含在内的即range={0,1,2},统计时候的区间为[0,1) [1,2)


##reshape:
在opencv中，reshape函数比较有意思，它既可以改变矩阵的通道数，又可以对矩阵元素进行序列化，非常有用的一个函数。

函数原型：

C++: Mat Mat::reshape(int cn, int rows=0) const

参数比较少，但设置的时候却要千万小心。

cn: 表示通道数(channels), 如果设为0，则表示保持通道数不变，否则则变为设置的通道数。

rows: 表示矩阵行数。 如果设为0，则表示保持原有的行数不变，否则则变为设置的行数。
在mk_signature_form_hist.cpp中有测试
reshape的原则 按照行以此往前填充新增的通道
{
    Mat test_shape(48,3,CV_32FC1);
    for(int i=0;i<48;i++)
   { for(int j=0;j<3;j++)
 {   test_shape.ptr<float>(i)[j]=i*3+j;
   
   cout<<i*3+j<<"  ";
   }
cout<<endl;}
sigg_2 = test_shape.reshape(4);
for(int i=0;i<sigg_2.rows;i++)
{for(int j=0;j<sigg_2.cols;j++)
cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
cout<<endl;
}cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后36×1 ，4通道图像

cout<<sigg_2.channels()<<endl;
cout<<endl;
/*从 0 1 2//1通道
     3 4 5
     变成
     0 1 2 3 
    4 5 6*/
}

{
    Mat test_shape(48,3,CV_32FC2);
    for(int i=0;i<48;i++)
   { for(int j=0;j<3;j++)
 {   test_shape.at<Vec2f>(i,j)[0]=(i*3+j)*2;
   
   cout<<(i*3+j)*2<<"  ";
   test_shape.at<Vec2f>(i,j)[1]=(i*3+j)*2+1;
     cout<<(i*3+j)*2+1<<"  ";
   }
cout<<endl;}
sigg_2 = test_shape.reshape(4);
for(int i=0;i<sigg_2.rows;i++)
{for(int j=0;j<sigg_2.cols;j++)
cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
cout<<endl;
}cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后72×1 ，4通道图像

cout<<sigg_2.channels()<<endl;
cout<<endl;
/*从 0 1   2 3    4 5//2 通道
     6 7   8 9   10 11
     变成
     0 1 2 3 
    4 5 6 7 */
}

在通道数变大的时候，列数首选变为1列

{
    Mat test_shape(48,3,CV_32FC2);
    for(int i=0;i<48;i++)
   { for(int j=0;j<3;j++)
 {   test_shape.at<Vec2f>(i,j)[0]=(i*3+j)*2;
   
   cout<<(i*3+j)*2<<"  ";
   test_shape.at<Vec2f>(i,j)[1]=(i*3+j)*2+1;
     cout<<(i*3+j)*2+1<<"  ";
   }
cout<<endl;}
sigg_2 = test_shape.reshape(1);
for(int i=0;i<sigg_2.rows;i++)
{for(int j=0;j<sigg_2.cols;j++)
//cout<< sigg_2.at<Vec4f>(i,j)[0]<<"  "<< sigg_2.at<Vec4f>(i,j)[1]<<"  "<< sigg_2.at<Vec4f>(i,j)[2]<<" "<<sigg_2.at<Vec4f>(i,j)[3]<<endl;
cout<<sigg_2.at<float>(i,j)<<"  ";
cout<<endl;
}cout<<sigg_2.rows<<" "<<sigg_2.cols<<endl;//reshape之后48×6 ，1通道图像

cout<<sigg_2.channels()<<endl;
cout<<endl;
/*0 1   2 3   4 5  //3通道
变成
 0  1   2  3  4  5//6通道

*/
 
}

在通道数变小的时候，列数变为 原来列×原来通道数/现在通道数目
## git reset --soft HEAD^ 取消之前的commit