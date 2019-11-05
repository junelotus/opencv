#include <opencv2/opencv.hpp>
using namespace cv;

int main()
{
    Mat f = imread("/home/user/june/test/camera/camera/dis_1.png");
    Mat  s(f);
    Point p(0,0);
    imshow("before",f);
    circle(s,p,10, Scalar(0,0,0));
    imshow("after",f);
    waitKey(100000);
return  0;

}
/*结论 使用上述初始化是浅层拷贝*/