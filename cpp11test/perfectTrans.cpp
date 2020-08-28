#include <iostream>
#include <boost/type_index.hpp>
 
using namespace std;
using boost::typeindex::type_id_with_cvr;  
 
template<typename T>
void PrintType(T&& param)
{
    // 利用Boost库打印模板推导出来的 T 类型
	cout << "T type：" << type_id_with_cvr<T>().pretty_name() << endl; 
    
    // 利用Boost库打印形参的类型
	cout << "param type:" << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
}
 
int main(int argc, char *argv[])
{
	int a = 0;                              // 左值
	PrintType(a);                           // 传入左值
 
	int &lvalue_refence_a = a;              // 左值引用
	PrintType(lvalue_refence_a);            // 传入左值引用
 
	PrintType(int(2));                      // 传入右值
}
