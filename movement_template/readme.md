## 在头文件tracking_c.h中
首先是对运动分析:使用如下函数

/* Updates motion history image given motion silhouette */
CVAPI(void)    cvUpdateMotionHistory( const CvArr* silhouette, CvArr* mhi,
                                      double timestamp, double duration );

/* Calculates gradient of the motion history image and fills
   a mask indicating where the gradient is valid */
CVAPI(void)    cvCalcMotionGradient( const CvArr* mhi, CvArr* mask, CvArr* orientation,
                                     double delta1, double delta2,
                                     int aperture_size CV_DEFAULT(3));

/* Calculates average motion direction within a selected motion region
   (region can be selected by setting ROIs and/or by composing a valid gradient mask
   with the region mask) */
CVAPI(double)  cvCalcGlobalOrientation( const CvArr* orientation, const CvArr* mask,
                                        const CvArr* mhi, double timestamp,
                                        double duration );

/* Splits a motion history image into a few parts corresponding to separate independent motions
   (e.g. left hand, right hand) */
CVAPI(CvSeq*)  cvSegmentMotion( const CvArr* mhi, CvArr* seg_mask,
                                CvMemStorage* storage,
                                double timestamp, double seg_thresh );
以上每个函数都要看下
接下来是对运动进行追踪：
使用meanshift camshift，考虑空间上的追踪