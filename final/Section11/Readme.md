# 追踪
分为两种：
tracking by detection:基于检测的追踪
tracking by detection：基于匹配的追踪
基于检测的追踪：
p332
1.基于检测：在每一帧上检测，将测结果连接起来
E(h) = sum(I(u,t)-I(u+h,t+1));u取值遍历整个图像块，（1）
其中I(u,t)表示t时刻的图像块
当h很小的时候可以用 I(u+h,t+1) 约等于 I(u,t)+h*I'. I'是图像的梯度。（2）
将（2）带入（1）：
sum（I'*I'的转置）h = sum(I(u,t)-I(u,t+1))* I' 其中sum表示遍历图像块 
 
# 基于仿射变换来确定一个匹配
上述说的变化是对平移变化的追踪，图像块在不同帧上出现了放射变化，用如下公式：
E(M,C) = sum(I(u,t)-I(Mu+C,t)) ,sum表示对图像块的遍历

可以使用 角点检测 开始。
1.查找初始帧上的所有角点
2.在下一帧上查找初始帧上的像素块所有角点，即角点匹配。然后观察 当前帧上的角点所属的块是否和上一阵上的块匹配，如果匹配的话，属于这个追踪，如果不匹配这个追踪结束，寻找新的角点并且创建新的追踪。可以和卡尔漫滤波结合 11.4.1将介绍。

#基于匹配：

