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
cvtColor(src,hsv,CV_BGR2HSV);

imshow("hsv",hsv);
    
    vector<Mat> channels;
    split(hsv,channels);
    int histSize = 300;
     float range[] = { 0,180 };
     const float * histRange ={range};
     bool uniform = true, accumulate = false;
/*for(int i=0;i<hsv.rows;i++)
        for(int j=0;j<hsv.cols;j++)
                cout<<static_cast<float>(channels.at(1).ptr(i)[j])<<endl;
  */   Mat ori_r = channels.at(0);
     Mat h_hist, s_hist, v_hist;
     calcHist( &channels.at(0), 1, 0, Mat(), h_hist, 1, &histSize, &histRange, uniform, accumulate );
float range_s[] ={0,255};
const float * histRange_s={range_s};
calcHist( &channels.at(2), 1, 0, Mat(), s_hist, 1, &histSize, &histRange_s, uniform, accumulate );
 int hist_w = 512, hist_h = 400;
     int bin_w = cvRound( (double) hist_w/histSize );
         Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
normalize(h_hist, h_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
normalize(s_hist, s_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
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
