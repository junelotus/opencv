#include "opencv2/highgui.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include<map>
#include <stdlib.h>
using namespace std;
using namespace cv;
int main(int argc,char **argv)
{
        
        // =NULL;
        if(argc==2)// && NULL!=(src=imread(argv[1])))
        {
Mat src =imread(argv[1]);
//if(src==NULL) return 0;
vector<Mat> chan;
split(src,chan);

map<float,int>re;
for(int i=0;i<src.rows;i++)
for(int j=0;j<src.cols;j++)
{
        /*src.at<Vec3F>(i,j)[0]=i*85+1+j>255?255:i*85+1+j;
        src.at<Vec3F>(i,j)[1]=i*85+2+j>255?255:i*85+2+j;

        src.at<Vec3F>(i,j)[2]=i*85+j+3>255?255:i*85+j+3;
        */


        
            float value = static_cast<float>(chan.at(0).ptr<unsigned char>(i)[j]);
         //cout<<value<<endl;
         re[value]++;
        }

//calcHist( &channels.at(1), 1, 0, Mat(), s_hist, 1, histSize, histRange, uniform, accumulate );


SparseMat h;

int histSize[] ={3,3,3};
const float  range []={0,256};
const float *ranges[]={range,range,range};
const int chan_count [] = {0,1,2};
//Mat mat_array[]={channels.at(0),channels.at(1),channels.at(2)};

calcHist(&src,1,chan_count,Mat(),h,2,histSize,ranges,true,false);//使用稀疏矩阵作为返回值的时候，依然无效

int dims  = h.dims();
SparseMatConstIterator_<float>  it =h.begin<float>(),it_end=h.end<float>();
       for(;it!=it_end;it++)
       {
               const SparseMat::Node* node = it.node();
              cout<<"( ";
              for(int i = 0; i < dims; i++)
                       cout<<node->idx[i]<<" ";
                       
               cout<<")  ";
               cout<<static_cast<float>(it.value<float>())<<endl;
 
 }
map<float,int>::iterator wode =re.begin();


cout<<"127 "<<re[127]<<endl;
cout<<"128 "<<re[128]<<endl;
int sum =0;
map<float,int>::iterator nide =++wode;

wode = re.begin();
/*验证上下界限*/
for(;wode!=re.end();wode++,nide++)
{

sum+=wode->second;
       /* if(nide->first==85) cout<<sum<<endl;
       
       if(wode->first==85) { cout<<sum<<endl;break;}//256/3=85.3,对应的累加到85 是正确的;

if(nide->first==128) cout<<sum<<endl;//当分成2哥bin的时候，累加到127是争取的，说明取的是（256+2-1）/2-1 和（256+3-1）/3-1取整数，即为不大于商的整数
       
              if(wode->first==128) { cout<<sum<<endl;break;}
*/        
        }
/*验证上下界限*/


/*验证各个区间*/
int count  =0;

for(int i=0;i<src.rows;i++)
        for(int j=0;j<src.cols;j++)
        {
                float v1=  static_cast<float>(chan.at(0).ptr<unsigned char>(i)[j]);
                float v2= static_cast<float>(chan.at(1).ptr<unsigned char>(i)[j]);
                if(v1>=86&&v1<=170 &&v2>=86&&v2<=170)//count是2450,对应的（1,1）的数值，所以按照坐标画出直方图然后去对应 就是每个通道落在对应区间的像素值的数量。
                        count++;
                
                
                }

cout<<count;
/*验证各个区间*/




       
       
       imshow("src",src);
        }
        
        return 0;
        }


