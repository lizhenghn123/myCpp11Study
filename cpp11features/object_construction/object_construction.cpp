#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

//1. C++11允许构造函数调用其他构造函数，也即委托或转接(delegation).
class SomeType 
{	
public:
	SomeType() : SomeType(0, "invalid"){ }
	SomeType(int i) : SomeType(i, "guest"){ }
	SomeType(const std::string& s) : SomeType(1, s){ }

	SomeType(int i, const std::string& s) : id(i), name(s)
	{ 
		std::cout << id << "\t" << name << "\n";
	}
private:
	int id;
	std::string name;
};

//2. C++11允许派生类手动继承基类的构造函数，编译器可以使用基类的构造函数完成派生类的构造。
class BaseClass
{
public:
	explicit BaseClass(int iValue){ }
};

class DerivedClass : public BaseClass
{
public:
	using BaseClass::BaseClass; //此语法等同于声明一个DerivedClass(int)的构造函数
};

//3. C++11可以使用以下的语法完成成员初始化:
class SomeClass
{
public:
	SomeClass() { print(); }
	SomeClass(int iNewValue, const std::vector<int> v) : iValue(iNewValue),vvv(v){ print(); }
public:
	void print()
	{
		std::cout << "iValue : " << iValue << "\n"; 
		std::copy(vvv.begin(), vvv.end(), std::ostream_iterator<int>(std::cout, "\t"));
		std::cout << "\n";
	}
private:
	int iValue = 5;  //若是构造函数中没有设置iValue的初始值，则会采用类定义中的成员初始化，令iValue初值为5
	std::vector<int> vvv;// = { 1, 2, 3, 4 }; //暂不支持初始化列表默认值
};

void test_obj_ctor()
{
	{
		SomeType s1;
		SomeType s2(1);
		SomeType s3("lizheng");
		SomeType s4(100, "sometype");
		std::cout << "-----------------------------\n";
	}
	{		
		BaseClass b1(1);
		//DerivedClass d1(2);   //好吧，似乎是VS2013还不支持
		//DerivedClass d2;    //Error,因为DerivedClass有了一个继承而来的构造函数，所以不会有默认构造函数
		std::cout << "-----------------------------\n";
	}
	{
		std::vector<int> v = { 1, 2, 3, 4 };
		SomeClass s1;          // 使用了默认定义的值
		SomeClass s2(2,v);     // 
		std::cout << "-----------------------------\n";
	}
}

int main()
{
	test_obj_ctor();

	getchar();
	return 0;
}