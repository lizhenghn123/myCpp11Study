/* http://www.ibm.com/developerworks/cn/aix/library/1307_lisl_c11/ */
#include <iostream>
#include <string>
#include <vector>
using namespace std;

//基于安全的理由，具名的参数将永远不被认定为右值，即使它是被如此声明的；为了获得右值必须使用 std::move<T>()
bool is_r_value(int &&) { return true; }
bool is_r_value(const int &) { return false; }
bool forward_r_value(int && i) { return is_r_value(i); }
void test_rvr(int && i)
{
	cout << is_r_value(i) << "\n"; //false: i为具名变量，即使被声明成右值也不会推导成右值(所有命名对象都只能是左值引用)
	cout << is_r_value(std::move<int&>(i)) << "\n";  //true: 使用 std::move<T>() 取得右值
	cout << is_r_value(2) << "\n"; //true: 2是右值 
	cout << forward_r_value(2) << "\n";  //false: 虽然2是右值，但是经过转发后变成了具名变量，最终变成左值
}

//                   右值引用最大的价值之一： 支持转移语义(Move Sementics)
/***
转移语义可以将资源(堆，系统对象等) 从一个对象转移到另一个对象，这样能够减少不必要的临时对象的创建、拷贝以及销毁，
能够大幅度提高 C++ 应用程序的性能。

临时对象的维护 ( 创建和销毁 ) 对性能有严重影响。通过转移语义，临时对象中的资源能够转移其它的对象里。

在现有的C++机制中，我们可以定义拷贝构造函数和赋值函数。
要实现转移语义，需要定义转移构造函数，还可以定义转移赋值操作符。
对于右值的拷贝和赋值会调用转移构造函数和转移赋值操作符。
如果转移构造函数和转移拷贝操作符没有定义，那么就遵循现有的机制，拷贝构造函数和赋值操作符会被调用。

普通的函数和操作符也可以利用右值引用操作符实现转移语义。
***/

//所有命名对象都只能是左值引用，如果已知一个命名对象不再被使用而想对它调用转移构造函数和转移赋值函数，
//也就是把一个左值引用当做右值引用来使用，可以使用标准库提供的std::move函数，这个函数以非常简单的方式将左值引用转换为右值引用。
std::string test(const std::string& str)
{
	printf("1: 0x%08x\n", str.c_str());
	std::string tmp(str);
	tmp.append("test!");  //注掉此行代码，2和3地址不同，添加此行后，2和3地址相同。
	printf("2: 0x%08x\n", tmp.c_str());
	//return std::move(tmp);  //和下面的直接返回是一样的，因为string已经实现了转移语义
	return tmp;
}

std::vector<int> test(const std::vector<int>& v)
{
	printf("1: 0x%x\n", &v[0]);
	std::vector<int> t(v);
	t.push_back(88);
	printf("2: 0x%x\n", &t[0]);
	return t; // 与std::move(t);结果一样
	//return std::move(t);
}

//                   右值引用最大的价值之二： 精确传递、完美转发 (Perfect Forwarding)
/***             
能够更简洁明确地定义泛型函数
精确传递适用于这样的场景：需要将一组参数原封不动的传递给另一个函数。
“原封不动”不仅仅是参数的值不变，在 C++ 中，除了参数值之外，还有一下两组属性：左值／右值和 const/non-const。
精确传递就是在参数传递过程中，所有这些属性和参数值都不能改变。在泛型函数中，这样的需求非常普遍。
***/
//void process_value(int i) { std::cout << "int\n"; }
void process_value(int& i) { std::cout << "int&\n"; }
void process_value(const int& i) { std::cout << "const int&\n"; }
void process_value(int&& i) { std::cout << "int&&\n"; }
void process_value(const int&& i) { std::cout << "const int&&\n"; }

template<typename T>
void print_value(T& t)
{
	t++;
	cout << "lvalue " << t << "\n";
}

template<typename T>
void print_value(T && t)
{
	cout << "rvalue " << t << "\n";
}

template<typename T>
void do_forward(T && v)
{
	v++;
	print_value(v);
	print_value(std::forward<T>(v)); //按照参数本来的类型来转发出去
	print_value(std::move(v));       //将v变成右值引用
}

void test_forward()
{
	int a = 0;
	const int& b = 1;
	process_value(a); // int& 
	process_value(b); // const int& 
	process_value(2); // int&&
	process_value(std::move(a)); // int&&
	process_value(std::move(2)); // int&&
	process_value(std::move(b)); // const int&&

	int x = 1;
	do_forward(1);  // lvalue rvalue rvalue
	do_forward(x);  // lvalue lvalue rvalue
	do_forward(std::forward<int>(x));  // lvalue rvalue rvalue	
}

//万能函数包装器（右值引用+完美转发+可变模板参数）： 可以接收所有的函数，带返回值的、不带返回值的、带参数的、不带参数的
template<typename Function, class... Args>
inline auto FuncWrapper(Function && func, Args && ... args) -> decltype(func(std::forward<Args>(args)...))
{
	//typedef decltype(func(std::forward<Args>(args)...)) ReturnType;
	return func(std::forward<Args>(args)...);
}

void func1(){ cout << "void" << endl; }
int  func2(){ return 1; }
int  func3(int x){ return x; }
std::string func4(std::string s1, std::string s2){ return s1 + s2; }

void test_func_wapper()
{
	FuncWrapper(func1);  // 1
	std::cout << FuncWrapper(func2) << "\n"; // 1
	std::cout << FuncWrapper(func3, 2) << "\n"; // 2
	std::cout << FuncWrapper(func4, "hello", " world") << "\n"; // hello  world
}

int main()
{
	test_rvr(0);
	cout << "----------------------------\n";

	test_forward();
	cout << "----------------------------\n";

	test_func_wapper();
	cout << "----------------------------\n";

	printf("3: 0x%08x\n", test("右值引用测试！").c_str());
	cout << "----------------------------\n";

	std::vector<int> v(3); // 改变这个值的大小(<3)，将会看到v2[0]地址的变化
	v.push_back(2);
	v.push_back(5);
	v.push_back(9);
	std::vector<int> v2 = test(v);
	printf("3: 0x%x\n", &v2[0]); 
	for (int i = 0; i < 100; ++i)
		v2.push_back(i);
	printf("4: 0x%x\n", &v2[0]);
	cout << "----------------------------\n";

	getchar();
	return 0;
}