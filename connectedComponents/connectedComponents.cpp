#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>

using namespace cv;
using namespace std;
int main(){
Mat img = imread("1_img.jpg");
Mat  img_edge, labels, img_color, stats,centroids;
threshold(img, img_edge, 128, 255, cv::THRESH_BINARY);
bitwise_not(img_edge,img_edge);
cv::imshow("Image after threshold", img_edge);
int i, nccomps = cv::connectedComponentsWithStats (
    img_edge, labels,
    stats, centroids
    );
cout << "Total Connected Components Detected: " << nccomps << endl;
vector<cv::Vec3b> colors(nccomps+1);
colors[0] = Vec3b(0,0,0); // background pixels remain black.
for( i = 1; i < nccomps; i++ ) {
    colors[i] = Vec3b(rand()%256, rand()%256, rand()%256);
    if( stats.at<int>(i, cv::CC_STAT_AREA) < 200 )
        colors[i] = Vec3b(0,0,0); // small regions are painted with black too.
}
img_color = Mat::zeros(img.size(), CV_8UC3);
for( int y = 0; y < img_color.rows; y++ )
    for( int x = 0; x < img_color.cols; x++ )
    {
        int label = labels.at<int>(y, x);
        CV_Assert(0 <= label && label <= nccomps);
        img_color.at<cv::Vec3b>(y, x) = colors[label];
    }
cv::imshow("Labeled map", img_color);
cv::waitKey();
}
