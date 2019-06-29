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

int main(int argc,char**argv){
Mat src;// =NULL;
if(argc==2)// && NULL!=(src=imread(argv[1])))
{
src =imread(argv[1]);
Mat hsv;
cvtColor(src,hsv,CV_BGR2HSV);//从rgb转化到hsv空间

imshow("hsv",hsv);
    int rows = hsv.rows;
    int cols = hsv.cols;
    vector<Mat> channels;
    split(hsv,channels);
 //   split(src,channels);
    int histSize[] ={2};//每一维bin的个数，数组大小和维度相同，每个元素代表此维上的bin的个数。只有一个元素说明直方图只有一维，最大为32维。若此值为256,则与手动用map统计出的结果相同，简单把直方图看作一个一个的竖条的话，就是每一维上竖条的个数。
    float range[] = { 0,2,4};//后续将range数组初始化二维数据，每一个range数组表示某一维度上bin的上线界。假设次数组是一维的bin的range， 如果是均匀直方图，则将第一维度均匀地分为histSize[0]个，假设histSize[0]为2,range={0,70}，每一个bin的上下界限为[0,35],[35,70];假设range不是数对，有两个以上的数字，则说明按照[0,20][20,70]为2个bin的上下限。

/*总结：void calcHist(const Mat* images, int nimages, const int* channels, InputArray mask, SparseMat& hist,                                   int dims, const int* histSize, const float** ranges, bool uniform=true, bool accumulate=false) 
在此函数中：
参数 (6)dims 表示直方图的维度，最大为32
     (7)histSize:表示每一个维度上bin的个数，所以histSize数组大小应该等于dims的大小，而其中的每个元素表示对应维度上的bin的个数
     (8)ranges 对于均匀直方图(即nuiform==true),ranges是一个由dims个float数对构成的数组,数对表示对应维的bin的范围.  eg.某维有N==2个bins,在ranges中对应的数对为{0,10},均匀的意思是讲,将该维的bin均匀的非为N==2个区间:[0,5]和[5,10],这是程序自动划分的,只需提供给他数对表示最值范围即可.

        对于非均匀的直方图,ranges的组成元素就不在是简单的数对了,而是一个个子数组,每个数组还有N+1个元素(N为该维的bin的数量),这N+1个元素将表示怎样对bin进行非均匀的划分.    eg.某维N==4个bins,ranges中对应的字数组为5个元素{0,2,4,9,10},非均匀的意思就是讲,讲该bin划分为非均匀区间[0,2],[2,4][4,9].[9,10]. 

          然后根据区间统计落在每个区间中的数量,从而计算出直方图.

          (9)nuiform是否均匀,对应ranges中元素的不同表示.如上.

          (10)accumulate一般为false,为TRUE时,在calchist中给hist分配内存时hist不会被清除,从而可以将多幅图的直方图统计到一个hist矩阵中.  或者有利于及时的更新直方图(不懂什么意思).

*/

     //float range_1[] = {20,70};
     /* ranges。用来进行统计的范围。比如
     
              float rang1[] = {0, 20};
              
                      float rang2[] = {30, 40};
                      
                              const float *rangs[] = {rang1, rang2};那么就是对0，20和30，40范围的值进行统计。
                              
                              --------------------- 
                              
                              作者：熊彬程的博客 
                              
                              来源：CSDN 
                              
                              原文：https://blog.csdn.net/xbcreal/article/details/52916089 
                              
                              版权声明：本文为博主原创文章，转载请附上博文链接！*/
     const float* histRange[] ={range};//,range_1};
     bool uniform = false, accumulate = false;

  
  
     Mat ori_r = channels.at(0);
     int size[3] = {2,2,2};
     
     //cv::SparseMat h_hist(3,size,CV_32F), s_hist, v_hist;
Mat h_hist;
/*此处试验多个图像和多个通道数*/
{
/*直方图的维度dims一定要小于channels的数组的大小*/
        int histSize[] ={2,2,2};
        const float  range []={0,1,2};
        const float *ranges[]={range,range,range};
const int chan_count [] = {0,1,2};//通道数目，如果传入两个图像，第一个图像有三个通道，第二个图像有一个通道，则一共是4哥通道{3,2,0}分别表示使用第二个图像的第一个通道，第一副图想的3通道和1通道来参与运算
Mat mat_array[]={channels.at(0),channels.at(1),channels.at(2)};
//SparseMatConstIterator_<float> it = h_hist.begin<float>();

//cout<<h_hist.total<<endl;
calcHist(mat_array,3,chan_count,Mat(),h_hist,1,histSize,ranges,false,false);
cout<<"wideu "<<h_hist.dims<<endl;
cout<<"size "<<h_hist.size()<<endl;
for(int i=0;i<h_hist.rows;i++)
        for(int j=0;j<h_hist.cols;j++)
                cout<<static_cast<float>(h_hist.ptr<float>(i)[j])<<endl;
//cv::SparseMatIterator it = h_hist.begin();
//int dims = h_hist.dims();
//cout<<dims<<endl;


//cout<<"wode"<<endl;
/*for(it = h_hist.begin<float>();it!=h_hist.end<float>();it++){
        cout<<"nide"<<endl;
cout<<it.value<float>()<<endl;
cout<<*it<<endl;
}*/
/*for(int i=0;i<3;i++)
{for(int j=0;j<2;j++)
cout<< h_hist.hash( i*2+j )<<endl;
}
cout<<"wode"<<h_hist.nzcount();
*///float* p0 = h_hist.find<float>(17610.0 );
//cout<<p0<<endl;


cout<<endl;
cout<<endl;
/* calcHist( &channels.at(1), 1, 0, Mat(), s_hist, 1, histSize, histRange, uniform, accumulate );
for(int i=0;i<1;i++)
{for(int j=0;j<2;j++)
cout<<static_cast<float>(s_hist.at<float>(i*2+j))<<endl;
}
*/

//const int chan_count_s[]={0,1,2};
calcHist(&hsv,1,chan_count,Mat(),h_hist,1,histSize,ranges,false,false);
cout<<endl;
cout<<endl;


for(int i=0;i<2;i++)
{for(int j=0;j<2;j++)
cout<<static_cast<float>(h_hist.at<float>(i*2+j))<<endl;
}


}
/*此处试验多个图像和多个通道数*/


    calcHist( &channels.at(0), 1, 0, Mat(), h_hist, 1, histSize, histRange, uniform, accumulate );
     
     
    /*验证直方图计算的数据是否和手动统计的数据一样多*/
   map<float,float> re;
   for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
            {
                    float value  = static_cast<float>(channels.at(0).ptr(i)[j]);

                    re[value]++;
        
        
            }   



    for(int i=0;i<2;i++)
    {
            cout<<i<<" "<<h_hist.at<float>(i)<<endl;

 
 }
    cout<<re[0]+re[1]<<endl;
    cout<<re[2]+re[3]<<endl;
    
    
    float range_s[] ={0,255};
    const float * histRange_s={range_s};
//    calcHist( &channels.at(2), 1, 0, Mat(), s_hist, 1, histSize, &histRange_s, uniform, accumulate );
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize[0] );
    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    //normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    //normalize(s_hist, s_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
/*for(int i=0;i<300;i++){
 //cout<<i<<endl;
 rmalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
// cout<<h_hist.at<float>(i)<<endl;
//cout<<i<<"  "<<s_hist.at<float>(i)<<endl;
}*/

waitKey(60000);
}

return 0;
}
