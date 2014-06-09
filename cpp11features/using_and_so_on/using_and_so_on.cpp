#include <iostream>
#include <string>
#include <vector>
using namespace std;

template< typename first, typename second, int third>
class SomeType;

//typedef可定义模板类型一个新的类型名称，但是不能够使用typedef来定义模板的别名
typedef std::vector<int> IntVec;    // Ok

//template< typename second>
//typedef SomeType<int, second, 5> TypedefName;   // Error

//使用using定义模板别名
template< typename second>
using TypedefName = SomeType<int, second, 5>;   // Ok

//using也能在C++11中定义一般类型的别名，等同typedef：
typedef void(*PFD)(double);		// Ok
using PFD = void(*)(double);	// Ok

//类型别名
typedef std::string MyStr1;     // Ok
using MyStr2 = std::string;     // Ok

//外部模版
extern template class std::vector<std::string>; //告诉编译器不要在该编译单元内将该模板实例化。

//右尖括号：C++11 提供了新的解析规则，多个右尖括号的时候，会优先为模板解析；但是有括号的时候，会先解析括号
//VS2013不支持
//template<bool Test> class SomeType { };
//std::vector<SomeType<1>2>> x1; // Interpreted as a std::vector of SomeType<true> 2>, which is not legal syntax. 1 is true.
//std::vector<SomeType<(1>2)> > x1; // Interpreted as a std::vector of SomeType<false>, which is legal C++11 syntax, (1>2) is false.

int main()
{
	//模板别名
	IntVec v;

	//类型别名
	MyStr2 ss;

	//C++11添加一个新的类型 long long int，它保证最小要和long int一样大，且不能小于 64 - bit
	std::cout << sizeof(long int) << "\n";       // 4	
	std::cout << sizeof(long long int) << "\n";  // 8

	//新式的以范围为基础的for循环：可以遍历C式数组、初始化列表(initializer lists)，和定义了begin()/end()函数(返回迭代器)的类型。
	int my_array[5] = { 1, 2, 3, 4, 5 };
	for (int &x : my_array)
	{
		x *= 2;
	}

	getchar();
	return 0;
}