## 在头文件tracking_c.h中
首先是对运动分析:使用如下函数

/* Updates motion history image given motion silhouette */
CVAPI(void)    cvUpdateMotionHistory( const CvArr* silhouette, CvArr* mhi,
                                      double timestamp, double duration );
cvUpdateMotionHistory函数作用：
silhouette:　首先此参数是一个包含当前时刻轮廓信息的图像
mhi:包含一段时间之内的的轮廓的信息，使用silhouette进行更新
timestamp:当前时刻的信息，表示毫秒的信心
duration:用于更新的时间阈
函数逻辑：
分为三种情况：
	  timestamp(当前时间帧)  ,if silhouette(x,y)!=0
mhi(x,y)  0 ,if silhouette(x,y)==0 && timestamp - mhi(x,y)>duration
          mhi(x,y)  .otherwise ig timestamp -mhi(x,y) <=duration

根据当前轮廓的值更新图像。　
mhi始终包含了在从当前时刻到duration时刻之前的一段时间中的轮廓的信息

/* Calculates gradient of the motion history image and fills
   a mask indicating where the gradient is valid */
CVAPI(void)    cvCalcMotionGradient( const CvArr* mhi, CvArr* mask, CvArr* orientation,
                                     double delta1, double delta2,
                                     int aperture_size CV_DEFAULT(3));
void calcMotionGradient( InputArray mhi, OutputArray mask, OutputArray orientation, double
delta1, double delta2, int apertureSize=3 )

计算全局中每个像素的梯度值，找到有效的数值，输出到第三个参数orientation中
函数运算过程：
aperture_size:在计算的时候选择的邻域的值
delta1　delta2 :在邻域中的最大或者最小的阈值。具体使用如下：

min(delta1,delta2) <=M(x,y)-m(x,y)<=max(delta1,delta2)
其中M(x,y)和m(x,y)分别是在aperture_size邻域中找到的梯度的最大最小值，当上式成立的时候，mhi(x,y)为有效的。

方向的计算：
orirntation(x,y) = arctan((dy)/(dx));//y方向的导数和x方向的导数之间的比值的反正切

fastAtan2( float y, float x )函数是经常被用到的。The function fastAtan2 calculates the full-range angle of an input 2D vector. The angle is measured in degrees and
varies from 0 to 360 degrees. The accuracy is about 0.3 degrees.








/* Calculates average motion direction within a selected motion region
   (region can be selected by setting ROIs and/or by composing a valid gradient mask
   with the region mask) */
CVAPI(double)  cvCalcGlobalOrientation( const CvArr* orientation, const CvArr* mask,
                                        const CvArr* mhi, double timestamp,
                                        double duration );
这个函数计算所选区域的平均运动方向，返回值在0到360之间。
这个计算的参数有一个方向权重直方图，直方图的权重大小：越近的时间的移动拥有越大的权重。



/* Splits a motion history image into a few parts corresponding to separate independent motions
   (e.g. left hand, right hand) */

void segmentMotion( InputArray mhi, OutputArray segmask, vector<Rect>& boundingRects, double
timestamp, double segThresh )
CVAPI(CvSeq*)  cvSegmentMotion( const CvArr* mhi, CvArr* seg_mask,
                                CvMemStorage* storage,
                                double timestamp, double seg_thresh );
参数segThresh:分割阈值
建议是最大的历史步长或者比其更大
函数返回值为CvSeq*，c++版本中调用c版本函数，将返回值写到boundingRects中



该函数找到所有的运动段，并用单独的值(1,2，…)在segmask中标记它们。它还计算了一个矢量与ROIs的运动连接组件。然后，使用提取的特定组件掩码，使用calcGlobalOrientation()计算每个组件的运动方向。
/*这个函数计算所有的移动片段，将他们命名为segmask-i，并且计算出运动相关组件的ROI区域的向量，
所有组件的运动可以通过使用特定的掩码，使用函数calcGlobalOrientation()计算。
*/
接下来是对运动进行追踪：
使用meanshift camshift，考虑空间上的追踪
