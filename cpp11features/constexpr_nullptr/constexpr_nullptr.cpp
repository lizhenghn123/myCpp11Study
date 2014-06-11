#include <iostream>
#include <string>
#include <vector>
using namespace std;

//              nullptr
/***
常量0扮演着整型常量和空指针常量的双重身份。
为了解决0的二义性,C++11通过引入一个新的关键字来纠正这个问题，用来标志空指针常量: nullptr。
它的类型是nullptr_t(用来隐式转换到任何指针或者成员指针(pointer-to-member)类型，不能转换成整型类型，除了bool)。
***/

void foo(char *) { std::cout << "foo(char *)\n"; }
void foo(int)    { std::cout << "foo(int)\n"; }

void test_nullptr()
{
	char *pc = nullptr; // ok
	int  *pi = nullptr; // ok
	bool  bb = nullptr; // ok, b is false
	//int   i1 = nullptr; // error,nullptr不是整数0

	int  *p1 = NULL;	// ok
	int   i2 = NULL;	// ok, NULL==0

	foo(NULL);     // 调用者可能希望调用的是foo(char *)，但实际上调用foo(int)，因为#define NULL ((void*)0)
	foo(nullptr);  // call foo(char *), not foo(int);
}

//              constexpr
/***
常量表达式(const expression) 是指值不会改变并且在编译过程就能得到计算结果的表达式。
C++11规定，允许将变量声明为constexpr类型以便由编译器来验证变量是否是一个常量表达式。
声明为constexpr 的变量一定是一个常量，而且必须用常量表达式初始化。
***/
//?+ VS2013 尚不支持该关键字

#ifndef WIN32
int GetFive1() { return 5; }
constexpr int GetFive2() { return 5; }
//constexpr int GetFive3(int i) { return i + 1; } //Error,非编译期常量，不可使用constexpr修饰
void test_constexpr()
{
	//int arr1[GetFive1() + 1]; //Error，C++中数组大小必须在编译期确定，但编译器并不知道GetFive1是个常数
	int arr2[GetFive2() + 1];

	constexpr int i = 100;      // 100 是常量表达式
	constexpr int i2 = i + 1;   // i + 1 是常量表达式
	constexpr sz = GetFive2();  // 只有当GetFive2是一个constexpr函数时才正确

	const int *p = nullptr;     // p 是一个指向整行常量的指针, p 是可变的，p指向的对象是不可变的
	constexpr int *q = nullptr; // q 是一个指向整数的常量指针, 是不可变的，q指向的对象是可变的
}
#else
void test_constexpr()
{
	std::cout << "Visual Studio 2013 don't support constexpr\n";
}
#endif

int main()
{
	test_nullptr();

	test_constexpr();

	getchar();
	return 0;
}