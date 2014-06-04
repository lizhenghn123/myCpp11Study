#include <iostream>
#include <string>
#include <vector>
using namespace std;
//http://zh.wikipedia.org/zh-cn/C++11#.E7.B5.B1.E4.B8.80.E7.9A.84.E5.88.9D.E5.A7.8B.E5.8C.96

//                                强类型枚举
/***
在标准C++中，枚举类型不是类型安全的。枚举类型被视为整数，这使得两种不同的枚举类型之间可以进行比较。
C++03 唯一提供的安全机制是一个整数或一个枚举型值不能隐式转换到另一个枚举别型。
此外，枚举所使用整数类型及其大小都由实现方法定义，皆无法明确指定。 
最后，枚举的名称全数暴露于一般范围中，因此两个不同的枚举，不可以有相同的枚举名。 
好比 enum Side{ Right, Left }; 和 enum Thing{ Wrong, Right }; 不能一起使用。
C++11 引进了一种特别的 "枚举类"，可以避免上述的问题。使用 enum class 的语法来声明。

此种枚举为类型安全的。枚举类型不能隐式地转换为整数；也无法与整数数值做比较。 (表示式 Enumeration::Val4 == 101 会触发编译期错误)。
枚举类型所使用类型必须显式指定。
***/
enum class Enumeration1   //默认类型是int
{
	Val1,
	Val2,
	Val3 = 100,
	Val4 /* = 101 */,
};

enum class Enumeration2 : long
{
	Val1,
	Val2,
	Val3 = 100,
	Val4 /* = 101 */,
};

enum OldEnum1{ EOLDNUM1, EOLDNUM2 };
//enum OldEnum2{ EOLDNUM1, EOLDNUM2 }; //不可定义，因为老的枚举类型其作用域类似全局，前面已有EOLDNUM1、EOLDNUM2定义了

void test_enum()
{
	//OldEnum1 和整数之间可以互转、比较等操作

	Enumeration1 e1 = Enumeration1::Val1;
	//Enumeration1 e2 = 2; //Error 整形也不能转换为枚举类对象
	//int e = e1;          //Error 枚举类型也不能转换为整数 

	Enumeration2 e21 = Enumeration2::Val1;
	//Enumeration2 e22 = Enumeration1::Val1;  //Error  Enumeration1和Enumeration2是不同的枚举类
	//if (e21 == 1)       //Error  枚举类型无法与整数数值做比较		
}

//                                无限制的union
/***
在标准 C++ 中，并非任意的类型都能做为 union 的成员。比如带有 non-trivial 构造函数的类型就不能是 union 的成员。
在新的标准里，移除了所有对 union 的使用限制，除了其成员仍然不能是引用类型。

注意：目前visual studio 2013尚不支持该功能，请看：http://msdn.microsoft.com/zh-cn/library/hh567368.aspx
http://www.csdn.net/article/2013-03-18/2814528-c11-compiler-support-shootout-visual-studio-gcc-clang-intel
***/
struct Point {
	Point() {}
	Point(int x, int y) : x_(x), y_(y) {}
	int x_, y_;
};

union U {
	int z;
	double w;
	//Point p;  // Illegal in C++03; legal in C++11
	U()// : p()
	{
		//new (&p) Point(); // Due to the Point member, a constructor definition is now required.
	}
};

int main()
{

	getchar();
	return 0;
}