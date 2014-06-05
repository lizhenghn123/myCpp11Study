#include <iostream>
#include <string>
#include <vector>
using namespace std;

/***               delete 和 default
如果类中定义了任何一种构造函数，编译器不再生成默认的构造函数。
但是，如果一个类既在指定了构造函数的同时，又需要编译器生成一个默认的构造函数。
C++ 11中允许显式的使用或者删除指定的成员函数

delete ： 表示这个函数的不可调用的
***/
struct NonCopyable
{
	NonCopyable() = default;
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable & operator=(const NonCopyable&) = delete;

	void foo(double i){ }
	void foo(int) = delete;  //不允许通过整形参数调用foo，也禁止了int->double的转换
	template<class T> void f(T) = delete;  //禁止了除了以double进行传参外其他所有的使用方式
private:
	//NonCopyable(const NonCopyable&);  // C++11之前的做法
	//NonCopyable & operator=(const NonCopyable&);
};

class NonA : public NonCopyable
{

};

int main()
{
	NonA a;
	//NonA b = a;  //Error
	//NonA c(a);   //Error

	a.foo(1.0);
	//a.foo(1); //Error

	getchar();
	return 0;
}