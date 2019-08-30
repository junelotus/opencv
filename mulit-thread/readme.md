
https://blog.csdn.net/tuxedolinux/article/details/86619843
# wait函数作用
void print_id(int id) {

unique_lock<mutex> lck(mtx); // 上锁

while (!ready) {

cv.wait(lck); //wait 函数作用 线程等待直到被唤醒（释放锁 + 等待，唤醒，在函数返回之前重新上锁）

}
# lock_guard和unique_lock的区别 都是对互斥量mutex加锁的锁类型
mutex mtx;
 
void foo() {
    lock_guard<mutex> lck(mtx);
    while (not_ready) {
		// ...
        cv.wait(mtx);
	}
}
lock_guard只可以 在构造函数中对互斥量进行加锁，在析构函数中对互斥量解锁，在中间的wait中是如何加锁解锁呢？
如果wait解锁到wait加锁这段期间发生了异常，互斥量处于解锁的状态，在之后后lock_guard要析构，析构的时候进行解锁。此时锁就会出现问题，因为互斥量mutex上已经没有锁了。
unique_lock不同支出在于 其析构函数：
~unique_lock() _NOEXCEPT { 	// 析构  
if (_Owns)				// 若互斥量在析构之前已经解锁了，由于存在_Owns标志，不再解锁，所以不会发生析构异常  
	_Pmtx->unlock();	// 若没有，则正常析构  
    }
https://blog.csdn.net/yingzinanfei/article/details/60755257
# condition_variable 条件变量
当condition_variable对象的某个wait函数被调用的时候，使用unique_loock来锁住当前进程，线程会一直被阻塞。直到在另外一个线程在相同的condition_variable对象上调用notify函数来唤醒当前进程。
# lock 和mutex
lock_guard和Mutex RAII相关，方便线程对互斥量mutex上锁
1.lock_guard对象通常用于管理某个锁对象
2.在某个lock_guard对象的生命周期内，他所管理的锁mutex对象会一直保持上锁的状态。在lock_guard生命周期结束之后，他所管理的锁对象会被解锁。
3.不负责锁对象mutex的生命周期，只是简化了上锁和解锁的操作，方便线程互斥量上锁。
unique_lock和mutex RAII相关，方便线程对互斥量上锁，提供了更好的上锁和解锁控制
1.以独占的方式管理mutex
# condition_variable 条件变量
当condition_variable对象的某个wait函数被调用的时候，使用unique_loock来锁住当前进程，线程会一直被阻塞。直到在另外一个线程在相同的condition_variable对象上调用notify函数来唤醒当前进程。
wait是等待锁的操作
# c++ feature
https://www.jianshu.com/p/f59e9b52677a
C++11之std::async

有wait 和get函数，都是在等待异步线程结束，get可以拿到返回结果。

异步策略不需要使用wait或者get等待异步直行完毕，异步策略自己会等到线程结束。


延迟策略std::async(std::launch::deferred,[](){ ...}); 必须使用wait或者get等待线程结束。
