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


waitKey(60000);
}

return 0;
}
