均值漂移算法：
https://blog.csdn.net/qwerasdf_1_2/article/details/54577336
根据距离　和　颜色空间设置半径，开始选择任意中心点，计算球体内和中心点的向量的均值(在颜色空间内　并且在距离空间内的各点和中心点的空间向量送往均值)


使用了图像金字塔


1、在未被分类的数据点中随机选择一个点作为中心点,注意是未北分类的点

2、找出离中心点距离在带宽之内的所有点，记做集合M，认为这些点属于簇c。

3、计算从中心点开始到集合M中每个元素的向量，将这些向量相加，得到偏移向量。

4、中心点沿着shift的方向移动，移动距离是偏移向量的模。

5、重复步骤2、3、4，直到偏移向量的大小满足设定的阈值要求，记住此时的中心点。／／中心点可以作为一个类别。

6、重复1、2、3、4、5直到所有的点都被归类。／／重复的过程如下所示，第一步中　没有访问过的点，是指没有在　族中出现过的点，还没有类别的点，过程中每访问一个点，这个点的类别都会增加一个。

7、分类：根据每个类，对每个点的访问频率，取访问频率最大的那个类，作为当前点集的所属类啊。／／因为每个类都有偏移所以同一个类别对于相同的像素点　，可能不止一次访问。试想某个区域中所有的点都是像素值相同的，选择中心的点作为步骤１中的中心点，那么最后的偏移是０，因为左右上下正负抵消，所以这个区域中的所有点被中心点所标志的访问了一次，所以他就属于中心点所属的类




最后可以以中心点的像素值作为次区域中每个像素点的像素值。



meanshift 算法源码分析 segmentation.cpp中(从空间和色彩空间考虑) watershed算法也在其中

camshift中的meanshift算法和这个有些不同:camshift算法中使用了距来替代质心的位置（主要是是从运动的角度即时间的角度来考虑）

        int dx = cvRound( m.m10/m.m00 - window.width*0.5 );
                int dy = cvRound( m.m01/m.m00 - window.height*0.5 );
                具体的使用可见camshift的readme.md (使用反向投影计算一阶距即质心的位置)

首先进行了图像金字塔的分割：
src_pyramid是原始图像的金字塔的处理，dst_pyramid是meanshift处理后的金子塔
termcrit 可以表示迭代次数，也可以表示迭代到小于某个阈值，在meanshift中出现。
sp0参数是空间的半径
sr是颜色空间的半径
float sp = (float)(sp0 / (1 << level));是根据不同的金字塔层数 缩小半径

//mean shift: process pixels in window (p-sigmaSp)x(p+sigmaSp)
                    minx = cvRound(x0 - sp); minx = MAX(minx, 0);
                    miny = cvRound(y0 - sp); miny = MAX(miny, 0);
                    maxx = cvRound(x0 + sp); maxx = MIN(maxx, size.width-1);
                    maxy = cvRound(y0 + sp); maxy = MIN(maxy, size.height-1);
计算空间中想要访问的区域的上下界限，因为不规则，所以要做越界判断。
tab 中的元素是减去了255的
 if( tab[t0-c0+255] + tab[t1-c1+255] + tab
 
 [t2-c2+255] <= isr2 ) 是关于三个通道的差距和颜色空间的半径之间的大小，如果在此方位内，要加上此时的坐标
  s0 += t0; s1 += t1; s2 += t2;

   icount = 1./count;
                    x1 = cvRound(sx*icount);
                    y1 = cvRound(sy*icount);//x1和y1是计算出来的均值漂移之后的位置
                    s0 = cvRound(s0*icount);
                    s1 = cvRound(s1*icount);
                    s2 = cvRound(s2*icount);//计算出来的s0 s1 s2是计算出来的三个通道的均值

                    到521行是一次均值漂移的过程，迭代不大于设定的次数或者小于设定的差距阈值，还是继续进行的，下一论同样是本次漂移的第n次，即在542行之前是选定了一个像素点不断迭代的过程。

                     dptr[0] = (uchar)c0;
                dptr[1] = (uchar)c1;
                dptr[2] = (uchar)c2;指向的是哪个像素？答：初始选中的点，比如在第一次 选中某个未访问过得点进行迭代 的那个点

                CV_ENABLE_UNROLLED是优化参数

                所以算法只是发现了种子而已，要使用漫水填充法floodFill进行图像的填充
