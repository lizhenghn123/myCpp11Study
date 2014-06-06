#include <iostream>
#include <string>
#include <vector>
using namespace std;

//                 变长参数模板
/***
C++11 之前, 不论是类模板或是函数模板，都只能按其被声明时所指定的样子，接受一组固定数目的模板参数 ；
C++11 加入新的表示法，允许任意个数、任意类别的模板参数，不必在定义时将参数的个数固定。

emplate<typename... Values> class tuple;  模板类 tuple 的对象，能接受不限个数的 typename 作为它的模板形参：
	class tuple<int, std::vector<int>, std::map<std::string, std::vector<int>>> someInstanceName;
实参的个数也可以是 0，所以 class tuple<> someInstanceName 这样的定义也是可以的。
若不希望产生实参个数为 0 的变长参数模板，则可以采用以下的定义：
	template<typename First, typename... Rest> class tuple;

如template<typename... Params> void printf(const std::string &strFormat, Params... parameters);
其中，Params 与 parameters 分别代表模板与函数的变长参数集合， 称之为参数包 (parameter pack)。参数包必须要和运算符"..."搭配使用，避免语法上的歧义。

变长参数模板中，变长参数包无法如同一般参数在类或函数中使用； 因此典型的手法是以递归的方法取出可用参数

除了在模板参数中能使用...表示不定长模板参数外，函数参数也使用同样的表示法代表不定长参数。
***/


//C++实现的printf函数：
//printf_cpp会不断地递归调用自身：函数参数包 args... 在调用时， 会被模板类别匹配分离为 T value和 Args... args。
//直到 args... 变为空参数，则会与简单的 printf(const char *s) 形成匹配，退出递归。
void printf_cpp(const char *s)
{
	while (*s)
	{
		if (*s == '%' && *(++s) != '%')
			throw std::runtime_error("invalid format string: missing arguments");
		std::cout << *s++;
	}
}

template<typename T, typename... Args>
void printf_cpp(const char* s, T value, Args... args)
{
	while (*s)
	{
		if (*s == '%' && *(++s) != '%')
		{
			std::cout << value;
			printf_cpp(*s ? ++s : s, args...); // 即便当 *s == 0 也会产生调用，以检测更多的类型参数。
			return;
		}
		std::cout << *s++;
	}
	throw std::logic_error("extra arguments provided to printf");
}

//计算变长参数的数量
template<typename ...Args> 
struct count_paras
{
	static const int size = sizeof...(Args);
};

int main()
{
	printf_cpp("My name is %s, age is %d, live in %s\n", "lizheng", 26, "Beijing");

	std::cout << count_paras<int, double>::size << "\n"; // 2
	std::cout << count_paras<>::size << "\n"; // 0

	getchar();
	return 0;
}