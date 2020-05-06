
#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <map>
using namespace std;
int n = 0;
class Foo
{
private:
	int val;
	string str;
public:
	Foo() :val(0), str("")
	{
		cout << "默认构造函数" << endl;
	}
	Foo(int v, string s) :val(v), str(s)
	{
		cout << "两个参数的构造函数" << endl;
	}
 
	Foo(const Foo &rhs)
	{n++;
cout<<n<<endl;
		val = rhs.val;
		str = rhs.str;
		cout << "赋值构造函数" << endl;
	}

	Foo(const Foo && rhs)
	{n++;
cout<<n<<endl;
		val = rhs.val;
		str = rhs.str;
		cout << "move构造函数" << endl;
	}
 
	Foo &operator=(const Foo &rhs)
	{
		val = rhs.val;
		str = rhs.str;
		cout << "赋值操作符重载" << endl;
		return *this;
	}
 
	~Foo()
	{
		cout << "析构函数" << endl;
	}
};
int main()
{

vector<Foo> ve;
ve.reserve(3);//不会调用构造函数
Foo f(21,"hehe");
cout<<endl;
//ve.push_back(Foo(19, "Jay"));
cout<<endl;
ve.push_back(f);//此处调用了一次复制构造函数 ，其实是move构造函数,在没有显式重写带有打印的move构造函数时，可以看到打印出复制构造函数，所以默认调用复制构造函数（在定义了其他构造函数时，move必须重写 才是有定义的）
ve.push_back(Foo(19, "Jay"));
cout<<endl;
ve.emplace_back(18,"Tom");//只调用两个参数的构造函数


string n = "wode";
cout<<&n<<endl;
string && wode = std::move(n);
cout<<"n="<<n<<endl;

string nide = std::move(n);
cout<<"n="<<n<<endl;
cout<<"nide="<<nide<<endl;
vector<string> re;
re.push_back(std::move(n));
cout<<&re[0]<<endl;

string hehe = "hehe";
string && h = std::move(hehe);

cout<<"hehe="<<hehe<<endl;
cout<<"h="<<h<<endl;

string hh = std::move(hehe);
cout<<"hehe="<<hehe<<endl;
cout<<"hh="<<hh<<endl;

return 0;
}
//总结： 右值没有名字 ，左值有名字，使用右值的时候 使用的是值，使用左值的时候使用的是地址；

//将变量A std::move到任何引用的时候，左值医用或者右值引用，A的值在move之后都还可以访问；将A的值move到左值后，A的值变成不确定值。

//emplace : vector.emplace('1',10)//直接在vector的作用空间中调用构造函数构造对象，不调用其他任何复制构造函数；vector.push_back(Foo('1',10)) 调用构造函数构造临时对象，临时对象 复制构造一个对象，再push_back


/*https://blog.csdn.net/yang20141109/article/details/50775667
https://blog.csdn.net/janeqi1987/article/details/100065133
https://blog.csdn.net/p942005405/article/details/84644069/
https://blog.csdn.net/p942005405/article/details/84644101
https://blog.csdn.net/xiaolewennofollow/article/details/52559306
*/

