https://blog.csdn.net/xiaohu2022/article/details/79599947#%E5%89%8D%E8%A8%80
# cuda基本语法的总结
流式多处理器（SM)
host :cpu device :GPU
1. __global__: 在device上执行，在host上调用，也可以在device上调用,返回类型是void
，不支持可变参数，不能使类成员函数，是kernel异步的，以为值host不会等待kernel执行完成就直行下一步骤。
2.__device__:在device上直行，在device上调用。不可以和__global__同时使用。
3.__host__ :在host上执行，在host上调用
# kernel在device上直行的时候　启动多线程
1.kernel启动的所有线程被称为一个网格grid,同一个网格共享相同的全局内存空间。
2.网格中分了很多块,线程块block，一个线程块包含很多线程，线程也是按照坐标形式排列的。
3.　


二：锁页内存https://blog.csdn.net/chenxiuli0810/article/details/90899014

