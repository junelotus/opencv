1.LMS算法 也叫做 最陡下降法 随机梯度法
最小均方误差算法：使用某种代价函数或者某个性能指标来衡量滤波器好坏，最常用的就是均方误差。
公式表示如下：
E{e(n)*e(n)} =E{(d(n)-y(n))*(d(n)-y(n))} （1）
x(n):输入向量
E{e(n)*e(n)}：均方误差
d(n)：x(n)输入滤波器之后的期望输出
h(n):多维自变量
y(n)：x(n)经过滤波器之后的实际输出，表示为h(n)*x(n)
e(n):表示期望输出和实际输出之间的误差
式(1)可以表示为以h(n)为多维自变量函数，所对应的函数是一个超抛物面（可以想象成碗的样子）且是恒正的，该抛物面叫做 误差性能曲面，在此曲面上的取值最小的点对莹的坐标就是 最优滤波器系数向量。

均方误差达到最小时，滤波器性能达到最优

在误差曲面上寻找最优解的方法 沿着曲面的切线方向，就是负梯度方向进行寻找，假设地n次迭代的到的权值向量为h(n)，均方误差为E(n)，则地n+1次迭代的到的系数可以由下式求出：
h(n+1) = h(n)-0.5g(n)u(n)
其中g(n)是第n次迭代的方向向量，u(n)是第n次迭代所用的步长，又叫做收敛因子

推导过程：
使用gg(n)作为g(n)的估值，求解时使用瞬时误差能量e(n)*e(n)来替代E{e(n)*e(n)}:
gg(n) = 偏（e(n)*e(n）/偏(h(n)) = 偏(d(n)-h(n)*x(n))*(d(n)-h(n)*x(n))/偏(h(n))= -2*e(n)*x(n)
则：
h(n+1) =h(n)+u*e(n)*x(n)
为了是算法收敛，u的去值范围在（0，2/（M *Px）） ，其中M为滤波器长度，Px为输入信号的功率 

NLMS: 归一化LMS算法

和LMS的区别在于 ：步长u是一个随时间变化的量，定义为：
u = a/(M*PPx(n))
其中PPx(n) = (x(n)的转置*x(n))/M,
为了使算法收敛 a的取值范围在（0，2）
为了避免PPx过小导致u过大，可以在u的分母上加上一个很小的常数c
u = a/(M*PPx(n)+c)

以上来自链接https://blog.csdn.net/wjrenxinlei/article/details/62889437
https://blog.csdn.net/wjrenxinlei/article/details/62892008
# 回声消除
图2.1.1 上方是扬声器，下方是麦克风，扬声器处理来的声音是x，即为回声也是远端语音，和当前的输入s也是近端一起传入麦克风中。

# pdf中说的算法
2.2 维纳滤波器  Wopt的求解
均方误差(MSE)
对于离散时间系统，
期待相应信号：dk
自适应系统输出：yk
k为采样时刻

误差信号kenai：kenai = dk-yk
自适应线性组合输出： yk=Wk*xk,
xk为在k时刻的输入信号
Wk为在k时刻的权向量
系统均方误差：
E(kefai*kefai) = E[(dk-yk)*(dk-yk)];

对W求解偏导数，在偏导数为0的情况下得到Wopt，维纳霍夫方程是将输入用向量表示出来替换到E(kefai*kefai)等号右边的过程。
2.3 LMS算法
求导过程类似于上述
具体求解噪声向量W的过程如下：
(1)首先获得噪声输入x(n)
(2)采集带有噪声的语音信号s(n)+x(n)
(3)用带有噪声的语音信号s(n)+x(n)-x'(n)，x'(n)是估计到的噪声信号
(4)用(3)的输出作为误差，根据误差反馈调节噪声权值向量w。
在本算法中差值e=for(n)(s(n)+x(n)-x'(n)),n表示在带有信噪声的语音信号分成n段。最终目的是使e*e最小，即x(n)和x'(n)的差值最小。

2.3.1 NLMS
输入信号较大时，会遇到梯度噪声放大的问题，使能量低的信号算法收敛速度比较慢。
讲述如信号按照自身的平均能量进行归一化处理，即为归一化LMS算法。
