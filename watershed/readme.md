void watershed( InputArray image, InputOutputArray markers ); 
函数有两个参数，再输入图像到函数之前，必须在图像makers中使用正的索引粗略标出希望的大致要分割的区域。所以每一个区域都被表示为一个或者多个具有像素值１或者　２或者　３这样的的连通组建。像这样的marker可以使用findContours()和drawContours()从二值的mask中提却出来。这些marker是未来图像区域的种子，标记中的所有其他像素，如果和轮廓的关系未知，应该由算法定义，则应该设置为0。

总结：在分数岭算法使用之前，要首先对第二个参数进行处理，此参数应该包含不同区域的轮廓，每个轮廓有一个自己唯一的标号。轮廓的定位可以通过opencv中的findcontours方法实现，这些是在直行分水岭函数之前的要求。

接下来直行分水岭算法会发生：算法根据markers传入的发轮廓作为种子，对图像上的其他像素点根据分数岭算法规则进行判断，并对每个像素点的区域归属进行划定，直到处理完图像上的所有像素点。而区域和区域之间的分解处的值北定义为－１，以作划分。

关于watershed算法的流程如下：
1 预处理阶段：
输入图像
转化为灰度图像
直方图据横画图像增强
高斯模糊去噪　或者　非局部均值去噪声

2 生成marker的阶段：
手动　或者
边缘检测
findContours
3　分水岭分割生成图像
watershed
分割结果可视化
显示图像


分水领算法会根据markers传入的轮廓作为种子即注水点，对图像上的其他像素根据分水岭算法规则进行判断，对每个像素的区域归属进行划分，直到处理完成所有的像素点。
区域之间临界处的值被置为-1。
问题来了：分水岭算法如何对其他的像素点根据规则判断，进行划分，去看下源码。



将每个轮廓所有的邻居像素点放入排序的队列中，决定盆地的初始边界。
//draw a pixel-wide border of dummy "watershed" (i.e. boundary) pixels
for( j = 0; j < size.width; j++ )
        mask[j] = mask[j + mstep*(size.height-1)] = WSHED;//第一行和最后一行是都变成-1，mstep表示到下一行的步长

 for( i = 1; i < size.height-1; i++ )
    {
        img += istep; mask += mstep;//img初始的值是源图像的第一个点，mask初始的值是边缘图像的第一个点 从第一行和第一列开始
        mask[0] = mask[size.width-1] = WSHED; // boundary pixels，第一列和最后一列变成-1

        for( j = 1; j < size.width-1; j++ )
        {
            int* m = mask + j;
            if( m[0] < 0 ) m[0] = 0; //m[0]==0说明此处是非边界的盆地，才是在mask图像上是0，如果是边界的化改成0
            if( m[0] == 0 && (m[-1] > 0 || m[1] > 0 || m[-mstep] > 0 || m[mstep] > 0) )
            {
                // Find smallest difference to adjacent markers
                const uchar* ptr = img + j*3;//ptr是img的指针
                int idx = 256, t;
                if( m[-1] > 0 )
                    c_diff( ptr, ptr - 3, idx );//c_diff是找到前两个参数所指向的像素，通道相差的最大值，放在idx中。此处是找和同一行前一个像素的差距
                if( m[1] > 0 )
                {
                    c_diff( ptr, ptr + 3, t );//和统一行后一个像素的差距
                    idx = ws_min( idx, t );
                }
                if( m[-mstep] > 0 )
                {
                    c_diff( ptr, ptr - istep, t );//和上一行同一列像素的差距
                    idx = ws_min( idx, t );
                }
                if( m[mstep] > 0 )//如果下一行同一列的mask图像上有值的话
                {
                    c_diff( ptr, ptr + istep, t );//和下一行同一列像素间的差距
                    idx = ws_min( idx, t );//找到和上下左右分别三个通道相差最小的值放在idx中。
                }//idx：和上下左右中最大差距的最小值

                // Add to according queue
                assert( 0 <= idx && idx <= 255 );
                ws_push( idx, i*mstep + j, i*istep + j*3 );
                m[0] = IN_QUEUE;
            }
        }
    }
#define ws_push(idx,mofs,iofs)          \
    {                                       \
        if( !free_node )                    \
            free_node = allocWSNodes( storage );\
        node = free_node;                   \
        free_node = storage[free_node].next;\
        storage[node].next = 0;             \
        storage[node].mask_ofs = mofs;      \
        storage[node].img_ofs = iofs;       \
        if( q[idx].last )                   \
            storage[q[idx].last].next=node; \
        else                                \
            q[idx].first = node;            \
        q[idx].last = node;                 \
    }//其中q是一个关于队列的数组，其中每个元素都是一个队列，每个队列都有有一个首尾值，在ws_push( idx, i*mstep + j, i*istep + j*3 );的应用中，storage指一个关于nsnode的vector，allocWSNodes定义为
    static int allocWSNodes( std::vector<WSNode>& storage )
{
    int sz = (int)storage.size();
    int newsz = MAX(128, sz*3/2);

    storage.resize(newsz);
    if( sz == 0 )
    {
        storage[0].next = 0;
        sz = 1;
    }
    for( int i = sz; i < newsz-1; i++ )
        storage[i].next = i+1;
    storage[newsz-1].next = 0;
    return sz;
}

storage的next定义为当前的所以值+1,node = free_node; node记住的是当前可用的位置，\
        free_node = storage[free_node].next;free_node是记住的下一个可用的位置
将当前可用的点storage[node]的mask_ofs 和img_ofs进行更新，如果q中有关于（上下左右最大差值的最小值）的记录（此记录记录的是storage中的某个索引），则将此节点的next值值为当前的node，如果q中没有关于此（上下左右最大差值的最小值）的记录，则在q中创建此记录，并且将first值值为此node。总之在storage中不断添加元素，添加的新元素如果和上下左右差值的最小值是idx，则q的last用来记录上一个和上下左右差值也是idx的元素在storage中的位置索引，并且将此位置索引的next值设置为当前新添加的元素的索引，那么访问storage的时候，按照next取方位，可以找到和上下左右最大值的最小值相差相同元素的所有的坐标，mofs和iofs分别在记录。并且在storage中将当前元素node的next_c的值值为0,下一次的时候将next_c置为当前的node，node的next还是置为0。

 m = mask + mofs;
        ptr = img + iofs;

        // Check surrounding pixels for labels
        // to determine label for current pixel
        t = m[-1]; // Left
        if( t > 0 ) lab = t;
        t = m[1]; // Right
        if( t > 0 )
        {
            if( lab == 0 ) lab = t;
            else if( t != lab ) lab = WSHED;
        }
        t = m[-mstep]; // Top
        if( t > 0 )
        {
            if( lab == 0 ) lab = t;
            else if( t != lab ) lab = WSHED;
        }
        t = m[mstep]; // Bottom
        if( t > 0 )
        {
            if( lab == 0 ) lab = t;
            else if( t != lab ) lab = WSHED;
        }查看上下左右的像素，如果上下左右不相同说明是边界，值为边界，否则的话上下左右是一个值，此处的lable也是上下左右的值

        assert( lab != 0 );
        m[0] = lab;

        if( lab == WSHED )
            continue;

            之后将相邻的还没有标记的像素点加入到队列中，更新active_queue，在之前不是都加入到q里面了吗？答：之前加入的符合这个条件if( m[0] == 0 && (m[-1] > 0 || m[1] > 0 || m[-mstep] > 0 || m[mstep] > 0) )，单不一定上下左右总有一个值是是边界的，但在部分填充之后肯定有上下左右有一个边界是大于0的

            if( m[-1] == 0 )
        {
            c_diff( ptr, ptr - 3, t );
            ws_push( t, mofs - 1, iofs - 3 );
            active_queue = ws_min( active_queue, t );
            m[-1] = IN_QUEUE;
        }
        if( m[1] == 0 )
        {
            c_diff( ptr, ptr + 3, t );
            ws_push( t, mofs + 1, iofs + 3 );
            active_queue = ws_min( active_queue, t );
            m[1] = IN_QUEUE;
        }
        if( m[-mstep] == 0 )
        {
            c_diff( ptr, ptr - istep, t );
            ws_push( t, mofs - mstep, iofs - istep );
            active_queue = ws_min( active_queue, t );
            m[-mstep] = IN_QUEUE;
        }
        if( m[mstep] == 0 )
        {
            c_diff( ptr, ptr + istep, t );
            ws_push( t, mofs + mstep, iofs + istep );
            active_queue = ws_min( active_queue, t );
            m[mstep] = IN_QUEUE;
        }

        算法总结：首先给定了轮廓，之后交给watershed算法处理，处理过程：
        首先遍历图像一遍，将上下左右相邻的像素点有轮廓信息（像素值大于0的，是种子）的像素点加入到vector中，并且通过队列记录更新vector的下一个节点在vector中的位置，然后对加入到vector中的像素点进行处理，没完成一个点的处理，对此点的上下左右像素点进行判断，是否是像素值为0的点（没有像素值的点），如果是的话继续加入到vector中，集训处理。
        总之是一个从轮廓外层像中心填充的过程