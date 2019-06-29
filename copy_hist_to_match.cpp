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

//imshow("hsv",hsv);
    int rows = hsv.rows;
    int cols = hsv.cols;
    vector<Mat> channels;
    split(hsv,channels);
    int histSize[] ={2};
    float range[] = { 0,1,2};


     
     const float* histRange[] ={range};//,range_1};
     bool uniform = false, accumulate = false;

  
  
     Mat ori_r = channels.at(0);
     int size[3] = {2,2,2};
     
//SparseMat h_hist;

//MatND h_hist;
/*此处试验多个图像和多个通道数*/
/*稀疏矩阵测试*/
{
        SparseMat h_hist;

int histSize[] ={3,3,3};
const float  range []={0,256};
const float *ranges[]={range,range,range};
const int chan_count [] = {0,1,2};
Mat mat_array[]={channels.at(0),channels.at(1),channels.at(2)};

calcHist(&src,1,chan_count,Mat(),h_hist,3,histSize,ranges,true,false);//使用稀疏矩阵作为返回值的时候，依然无效
cout<<"zero"<<h_hist.nzcount()<<endl;

SparseMatConstIterator_<float> it = h_hist.begin<float>(),
        it_end = h_hist.end<float>();
        double s = 0;
        int dims = h_hist.dims();
        cout<<"dims="<<dims<<endl;
int idx[3];
 

        for(; it != it_end; ++it)
        {
                cout<<"heh"<<endl;
                    // print element indices and the element value
                        const SparseMat::Node* n = it.node();
                            printf("(");
                                for(int i = 0; i < dims; i++)
                                                printf("%d%s", n->idx[i], i < dims-1 ? ", " : ")");
                                                    printf(": %g\n", it.value<float>());
        }

 


}
 /*MatND 测试*/
{
  MatND h_hist;
  int histSize[] ={3,3,3};
  const float  range []={0,256};
  const float *ranges[]={range,range,range};
  const int chan_count [] = {0,1,2};
  Mat mat_array[]={channels.at(0),channels.at(1),channels.at(2)};

  calcHist(&src,1,chan_count,Mat(),h_hist,3,histSize,ranges,true,false);//使用稀疏矩阵作为返回值的时候，依然无效
cout<<endl;
cout<<endl;
for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
                for(int k=0;k<3;k++)
                {
                        cout<<"("<<i<<","<<j<<","<<k<<"):"<<h_hist.at<float>(i,j,k)<<endl;
                        
                        }


        
        }

  //  calcHist( &channels.at(0), 1, 0, Mat(), h_hist, 1, histSize, histRange, uniform, accumulate );
     
     
    /*验证直方图计算的数据是否和手动统计的数据一样多*/
   /*map<float,float> re;
   for(int i=0;i<rows;i++)
            for(int j=0;j<cols;j++)
            {
                    float value  = static_cast<float>(channels.at(0).ptr(i)[j]);

                    re[value]++;
        
        
            }   



    for(int i=0;i<2;i++)
    {
            //cout<<i<<" "<<h_hist.at<float>(i)<<endl;

 
 }
    //cout<<re[0]+re[1]<<endl;
   // cout<<re[2]+re[3]<<endl;
    
    
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
