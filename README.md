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

## 关于calcBackProject和calcBackProjectPatch
cv::calcBackProject ( const Mat * images, int nimages, const int * channels, InputArray hist, OutputArray backProject, const float ** ranges, double scale = 1, bool uniform = true )
void cvCalcBackProjectPatch( IplImage** image, CvArr* dst, CvSize patch_size, CvHistogram* hist, int method, double factor );
image
    输入图像 (可以传递 CvMat** )
dst
    输出图像.
patch_size
    扫描输入图像的补丁尺寸
hist
    直方图
method
    比较方法，传递给 cvCompareHist (见该函数的描述).
factor
    直方图的归一化因子，将影响输出图像的归一化缩放。如果为 1，则不定。 /*归一化因子的类型实际上是double，而非float*/

calcBackProject:利用已知的直方图在参数图像上进行扫描，如果直方图(可以是均衡化的直方图)中某段像素值区间的bin值为bin_value，参数图像上点(x,y)处的值为此像素值，则在结果图像dest的(x,y)处像素值为bin_value;
calcBackProjectPatch：此函数不是关于单个像素的处理了，是使用滑动窗口即像素块之间的对比来计算像素块中心的权值;首先给定一个直方图用来描述待检测的特征，使用的滑动窗口大于待检测的物体时（目标检测器），滑动窗口覆盖的像素区域计算出一个直方图和给定的hist比较，计算相似度，作为滑动窗口中心位置的权值，权值最大的点所代表的区域，即为待检测物体的最佳候选区域；使用的滑动窗口比待检测的物体小的时候（区域检测器），反响投影上的每一个点，都表示该像素点的肤色概率。函数没有使用padding，得到的dest图像在长和宽上都减去（patch_size-1）大小。



## 搜索函数的时候，可以先搜索以cv开头的函数，比如要找函数matchTemplate，可以现在全局搜索cvMatchTemplate，然后他调用了matchTemplate。

## 英特尔(R)集成性能基元 (R)ipp
ippiSqrDistanceNorm_8u32f_C1R 
#define ippiSqrDistanceNorm_8u32f_C1R ippicviSqrDistanceNorm_8u32f_C1R
使用了intel的加速函数实现，在matchTemplate函数中的各种方法。



## OTUS 最大类间方差法
用来对灰度图像二值化

threshold(gray,gray,0,255,THRESH_OTSU);//CV_THRESH_BINARY);
/*
CV_THRESH_OTSU是提取图像最佳阈值算法。该方法在类间方差最大的情况下是最佳的，就图像的灰度值而言，OTSU给出最好的类间分离的阈值。
原理：

对于图像I(x,y)，前景(即目标)和背景的分割阈值记作T，属于前景的像素点数占整幅图像的比例记为ω0，其平均灰度μ0；背景像素点数占整幅图像的比例为ω1，其平均灰度为μ1。图像的总平均灰度记为μ，类间方差记为g。

假设图像的背景较暗，并且图像的大小为M×N，图像中像素的灰度值小于阈值T的像素个数记作N0，像素灰度大于阈值T的像素个数记作N1，则有：
　　　　　　ω0=N0/ M×N (1)
　　　　　　ω1=N1/ M×N (2)
　　　　　　N0+N1=M×N (3)
　　　　　　ω0+ω1=1　　　 (4)
　　　　　　μ=ω0*μ0+ω1*μ1 (5)
　　　　　　g=ω0(μ0-μ)^2+ω1(μ1-μ)^2 (6)
将式(5)代入式(6),得到等价公式:
　　　　　　g=ω0ω1(μ0-μ1)^2 　　 (7)　这就是类间方差
采用遍历的方法得到使类间方差g最大的阈值T,即为所求。
     */

     在findContour.hpp中可以找到


## 距
/*hu矩具有平移 缩放 旋转不变性，普通距(p279)中心距(p281)不能是物体具有平移旋转比例不变性，归一化中心距 有平移和比例不变性 */
/*利用hu距进行匹配 ，图像必须是单通道图像，二值图像也好
matchShapes(gray,gray_d,1,0)//最后一个参数为0,传入的前两个参数是图像的化，会首先计算距，然后使用p283的表8-2介绍的三种方法进行匹配
## 凸包和凸包缺陷
凸包缺陷的结构体：
凸包缺陷的起始点
凸包缺陷的结束点
凸包缺陷中离凸包的边最远的点
最远点和包的边的距离
寻找凸包缺陷的函数：

@param contour Input contour.
@param convexhull Convex hull obtained using convexHull that should contain indices of the contour
points that make the hull.
@param convexityDefects The output vector of convexity defects. In C++ and the new Python/Java
interface each convexity defect is represented as 4-element integer vector (a.k.a. cv::Vec4i):
(start_index, end_index, farthest_pt_index, fixpt_depth), where indices are 0-based indices
in the original contour of the convexity defect beginning, end and the farthest point, and
fixpt_depth is fixed-point approximation (with 8 fractional bits) of the distance between the
farthest contour point and the hull. That is, to get the floating-point value of the depth will be
fixpt_depth/256.0.
 */
 CV_EXPORTS_W void convexityDefects( InputArray contour, InputArray convexhull, OutputArray convexityDefects );

## freeman 链码编码
描述轮廓的时候，用一系列的点及其走向表明轮廓，点是8连通的，一共有360/45个角度可以选择。
##CCH 链式编码直方图
用来统计轮廓的freeman链码编码中每一种走向的直方图，所以轮廓要是旋转45度，对于直方图来说，只是将每个bin循环移动一个距离就好。用EMD匹配的时候，结果是0,即完全匹配。
## PCG 成对几何直方图 每一对边组成的直方图 n*(n-1)/2对边 
轮廓多边形的每一条边，都被选择成为基准边，考虑其他的边相对这条边的关系，包括三个值， dmin dmax和角度， 此直方图有两个维度，分别是角度和距离，每一对边，有两个bin。直方图有旋转不变性（不止旋转45度的时候）可以用来做轮廓的匹配。

PGH的能力更强。

## 等级匹配 匹配两个轮廓
用一个轮廓创建一个轮廓树步骤：
1.首先搜索轮廓上突出或者凹陷的三角像周边
2.每个这样的三角形通过一条直线相连，此直线链接的是轮廓上不相邻的两点，所以轮廓上的三角形或者被削平或者被填充
3.每次这样的直线连接使轮廓上的点减少1
4.对于每个三角形，如果三角形两侧有原始的边，那么他就是轮廓树的叶子，如果一侧是已经存在的三角形，则就是这个三角形的父节点。


## 轮廓的多边形逼近算法 ： approxPolyDP( InputArray curve, OutputArray approxCurve,double epsilon, bool closed );函数使用了dp算法，该算法步骤如下
1.手下找打轮廓上最远的两个点添加到结果中，此两点连成一条直线,作为多边形咱数的一条边，此边在后续会更新
2.再从轮廓中寻找离上述直线最远的点，添加到结果中
3.不断迭代上述两步骤，直到所有的点到多边形的距离，小于参数epsilon

## 多边形逼近过程中有寻找关键点的过程  findDominantPoint 算法叫做IPAN算法
算法通过扫描 在轮廓上并且在曲线内部的点 构造三角形，对于三角形的大小和张角，在特定的全局阈值和其他相邻点构成的三角形张角更小的情况下，具有更大张角的点被留下

如树上p274描述：规定了四个参数最短距离dmin 最长距离dmax，相邻距离dn（一般不超过dmax） 最大角度a
两点固定时，寻找在轮廓上的第三个顶点时，首先将构成的三角形两边的距离在 dmin和dmax之间的，张角<a的所有三角形找出来，
然后保留对于dn（某个特定距离）有最小夹角的所有点p


## 帧差　计算背景模型
此方法用于背景中没有移动的物体，前景在图像中走过的场景（比如手在前景中划过）下计算背景
假设计算一个视频中的背景，视频有ｎ帧图像
１.首先累加ｎ帧图像　ｃｖＡｄｄ，累加各相邻帧的绝对插值cvabsdiff，将每一帧图像变为３通道浮点类型的，便于之后累加
2.将以上累加的两个结果帧，除以帧树ｎ，得到一个累加均值帧　iavgf 和累加绝对差值帧　idifff ,
3.设置阈值，若像素值>iavg+7*idifff 或者　像素值<iavgf-6*idifff 则表示该像素表达了一个前景，否则是后景。
## opencv3.3增加的函数
寻找连通区域
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
## convertScaleAbs
可用于图像增强

cv::convertScaleAbs(src,dest,a,b)用于实现对整个图像数组中的每一个元素，进行如下操作：

dest(i) = saturate uchar(|a*src(i)+b\)


## git 修改用户名和密码


查看用户名和邮箱地址：

$ git config user.name

$ git config user.email

修改用户名和邮箱地址

$  git config --global user.name  "xxxx"

S  git config --global user.email  "xxxx"

直接修改git的配置文件的方式来进行修改
 1） 打开全局的.gitconfig文件的命令为：$  vi ~/.gitconfig;   然后在文件中直接修改即可.
## git 修改所提交分支的用户名和邮箱


 第二步，如图所示，你可以找到你想修改的那次记录的commit id
 第三步，使用git reset –soft [版本号]命令进入你的提交记录
 第四步，使用 git commit --amend --author='用户名 <邮箱>'修改
 第四步，修改完文件，退出vim（一直按住esc ，再连续按大写的z）
 第五步：使用 git push提交代码

## Git修改已经提交的用户名信息
### 第一步，（n）代表提交次数
git rebase -i HEAD~n
### 第二步
然后按`i`编辑，把`pick` 改成 `edit`，按'Esc'退出编辑，按`:wq`保存退出
### 第三步
git commit --amend --author="作者 <邮箱@xxxx.com>" --no-edit
### 第四步
git rebase --continue
### 第五步
git push --force


##概述
https://blog.csdn.net/chenhongwu666/article/details/50714926

## 图像金字塔的用处
主要解决图像分析尺度问题的，许多图像分析任务，包括超分辨、目标检测等等都是一种很重要的手段。
  更多的是构造特征时：1、适应尺度变化。2、增加特征维度，构造高维特征。在缩放法哦比较小的图像上高斯核，相当于在scale较大的图像上使用较大的高斯核。详情参见sift算法


