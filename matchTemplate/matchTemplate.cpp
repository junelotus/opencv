#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
/*http://www.opencv.org.cn/opencvdoc/2.3.2/html/doc/tutorials/imgproc/histograms/template_matching/template_matching.html
关于matchTemplate函数的结果，dest也是四则为(sec.rows-temp.rows+1,src.cols-temp.cols+1)大小的
定义在/home/june/opencv_test/opencv-3.4.0/modules/imgproc/src/templmatch.cpp 1090行 

*/
#include <opencv2/opencv.hpp>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/highgui.h>
#include <opencv/cv.h>	 	
#include <cmath>
#include <stdio.h>
using namespace std;
using namespace cv;
#define pai 3.14159
Mat src;
Mat temp;
int match_method =0 ;
Mat dest;
int max_trackbar = 5;
char   src_win[] = "src";
char dest_win[] ="dest";
void MatchMethod(int ,void *)
{       Mat img_display;
        src.copyTo(img_display);
        matchTemplate(src,temp,dest,match_method);
        normalize( dest, dest, 0, 1, NORM_MINMAX, -1, Mat() );
        dest.create(src.rows-temp.rows+1,src.cols-temp.cols+1,CV_32FC1);
        double minval,maxval;
        Point minLoc,maxLoc;
        Point matchLoc;
        minMaxLoc(dest,&minval,&maxval,&minLoc,&maxLoc,Mat());
       // if(match_method <=1 )
         if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
         matchLoc = minLoc;
        else 
                matchLoc = maxLoc;
        
rectangle(img_display,matchLoc,Point(matchLoc.x+temp.cols,matchLoc.y+temp.rows),Scalar::all(0),2,8,0);
        imshow( src_win,img_display );
          imshow( dest_win, dest );
          imshow("dest",dest);
          return ;
}
/*平方差匹配,按照三通道的来计算*/
void fun_CV_FIVE_FUN(const Mat&src,const Mat &temp,Mat& dest,const int nd)
{      
       Mat img_display;
       src.copyTo(img_display); 
         int src_rows = src.rows;
        int src_cols = src.cols;
        int rows  = temp.rows;
        int cols = temp.cols;
        Mat srcc ;
        Mat tempp;
         cvtColor(src,srcc,CV_BGR2GRAY);
         cvtColor(temp,tempp,CV_BGR2GRAY);
        dest.create(src.rows-temp.rows+1,src.cols-temp.cols+1,CV_8UC1);
        for(int i=0;i<src_rows-rows;i++)
                for(int j=0;j<src_cols-cols;j++)
                {
                        float sq_diff =0.0;
                        float ccorr =0.0;
                        float z =0.0;
                        float z1 =0.0;
                        float z2=0.0;

                        for(int ii=0;ii<rows;ii++)
                        for(int jj=0;jj<cols;jj++)
                        {
                                /*cv_tm_sqdiff */
                                float a = static_cast<float>(temp.ptr<unsigned char>(ii,jj)[0]);
                                float b= static_cast<float>(src.ptr<unsigned char>(i+ii,j+jj)[0]);
                               // cout<<a<<endl;
                                //cout<<b<<endl;
                                sq_diff +=((temp.ptr<unsigned char>(ii,jj)[0])-src.ptr<unsigned char>(i+ii,j+jj)[0] )*((temp.ptr<unsigned char>(ii,jj)[0])-src.ptr<unsigned char>(i+ii,j+jj)[0] );//(a-b)*(a-b); //  cout<<a<<endl;
                                

                                a = static_cast<float>(temp.ptr<unsigned char>(ii,jj)[1]);
                                 b= static_cast<float>(src.ptr<unsigned char>(i+ii,j+jj)[1]);
                               // cout<<a<<endl;
                                //cout<<b<<endl;
                                sq_diff +=((temp.ptr<unsigned char>(ii,jj)[1])-src.ptr<unsigned char>(i+ii,j+jj)[1] )*((temp.ptr<unsigned char>(ii,jj)[1])-src.ptr<unsigned char>(i+ii,j+jj)[1] );//(a-b)*(a-b); //  cout<<a<<endl;
                               ;//(a-b)*(a-b); //  cout<<a<<endl;
                                a = static_cast<float>(temp.ptr<unsigned char>(ii,jj)[2]);
                                 b= static_cast<float>(src.ptr<unsigned char>(i+ii,j+jj)[2]);
                               // cout<<a<<endl;
                                //cout<<b<<endl;
                                sq_diff +=((temp.ptr<unsigned char>(ii,jj)[2])-src.ptr<unsigned char>(i+ii,j+jj)[2] )*((temp.ptr<unsigned char>(ii,jj)[2])-src.ptr<unsigned char>(i+ii,j+jj)[2] );//(a-b)*(a-b); //  cout<<a<<endl;
                               ;//(a-b)*(a-b); //  cout<<a<<endl;
sq_diff=sqrt(sq_diff);
                                // cout<<sq_diff<<endl;
                        //         sq_diff +=(temp.at<Vec3b>(ii,jj)[0] - src.at<Vec3b>(ii,jj)[0])*(temp.at<Vec3b>(ii,jj)[0] - src.at<Vec3b>(ii,jj)[0]);
                        //         cout<<sq_diff<<"  "<<endl;
                        //         sq_diff +=(temp.ptr<float>(ii,jj)[1] - src.ptr<float>(ii,jj)[1])*(temp.ptr<float>(ii,jj)[1] - src.ptr<float>(ii,jj)[1]);
                        //        cout<<sq_diff<<"  "<<endl;
                        //         sq_diff +=(temp.ptr<float>(ii,jj)[2] - src.ptr<float>(ii,jj)[2])*(temp.ptr<float>(ii,jj)[2] - src.ptr<float>(ii,jj)[2]);
 
                                z1+=a*a;
                                z2 += b*b;
                                



                        }
                        
                        z=sqrt(z1*z2);
                        dest.ptr<unsigned char>(i)[j] = static_cast<unsigned char> (sq_diff);
                        if(static_cast<float>(sq_diff==0)) cout<<"nide"<<endl;
                        //cout<<z<<endl;
                        // switch(nd){
                        //         case 0:
                        //         dest.ptr<unsigned char>(i)[j] = static_cast<unsigned char> (sq_diff);
                        //         //cout<<static_cast<float>(dest.ptr<unsigned char>(i)[j])<<endl;
                        //         break;
                        //         case 3:
                        //         dest.ptr<unsigned char>(i)[j] = static_cast<unsigned char>(sq_diff/z);

                        //         break;
                        //         default: break;



                        // }

                         



                                        
                                        
                                        
                                        
                                        
                                        }

                                
                                
                        
                        cout<<"wode"<<endl;
                

        double minval,maxval;
        Point minLoc,maxLoc;
        Point matchLoc;
        minMaxLoc(dest,&minval,&maxval,&minLoc,&maxLoc,Mat());
        cout<<"heh"<<static_cast<float>(minval)<<endl;
       // if(match_method <=1 )
         if( nd  == 0 || nd == CV_TM_SQDIFF_NORMED )
                {  matchLoc = minLoc;cout<<"tt"<<endl;}
        else 
                matchLoc = maxLoc;
                float min =255;
                 for(int i=0;i<src_rows-rows;i++)
                // for(int j=0;j<src_cols-cols;j++)
                // {
                //         float v = static_cast<float>(dest.at<unsigned char>(i,j));
                //         if(v<=min)
                //         {
                //                 min = v;
                //                 cout<<min<<endl;
                //               matchLoc=Point(j,i); 
                //                rectangle(img_display,matchLoc,Point(matchLoc.x+temp.cols,matchLoc.y+temp.rows),Scalar::all(0),2,8,0);
         
                //         }


                // }
        
        rectangle(img_display,matchLoc,Point(matchLoc.x+temp.cols,matchLoc.y+temp.rows),Scalar::all(0),2,8,0);
        imshow( "my own",img_display );
         imshow( "dest",dest );
          imshow( "temp",temp);
        
}


int main(int argc,char ** argv)
{
cout<<CV_TM_SQDIFF<<endl;
cout<<CV_TM_SQDIFF_NORMED<<endl;
if(argc<3) return 0;
src =imread(argv[1]),temp=imread(argv[2]);

 char trackbar_label[] = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
  
char *  src_win = "src";
char* dest_win ="dest";

namedWindow(src_win,CV_WINDOW_AUTOSIZE);
namedWindow(dest_win,CV_WINDOW_AUTOSIZE);
createTrackbar(trackbar_label,src_win,&match_method,max_trackbar,MatchMethod);
// {
//         Mat dest;
// fun_CV_FIVE_FUN(   src,  temp, dest,0);
// }


const char* opencv_libraries = 0; 
const char* addon_modules = 0; 
//cvGetModuleInfo( 0, &opencv_libraries,&addon_modules ); 
printf( "OpenCV: %s\r\nAdd-on Modules: %s\r\n.", opencv_libraries, addon_modules); 
waitKey(60000);
        
return 0;        
}
