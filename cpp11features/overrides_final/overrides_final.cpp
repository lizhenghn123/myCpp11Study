#include <iostream>
#include <string>
#include <vector>
using namespace std;

//               override 和 final
/***
override : 编译器会检查基类是否存在一虚拟函数与派生类中带有声明override的虚拟函数有相同的函数签名(signature)；若不存在，则会报错
final    : 用来避免类型被继承，或是基类的函数被改写
***/
struct Base1
{
	virtual void foo1(float a)
	{
		std::cout << "Base: " << a << std::endl;
	}
	virtual void foo2(float a)
	{
		std::cout << "Base: " << a << std::endl;
	}
};

struct Derived1 : Base1 
{
	virtual void foo1(int a)  //这里并没有重载基类中的虚函数foo1，因为这两个函数签名并不同
	{
		std::cout << "Derived: " << a << std::endl;
	}
	virtual void foo2(float a) override //通过override强制规定foo2是重载基类的虚函数foo2，这样可以避免书写错误
	{
		std::cout << "Derived: " << a << std::endl;
	}
};


struct NoInherit final {}; //使用final表示该类不能被继承
//struct Child : NoInherit  {}; //Error
struct Base2
{
	virtual void foo(int) final { } //使用final禁止派生函数改写该函数
};
struct Derived2 : Base2
{
	//virtual void foo(int); //Error,
};


int main()
{
	Base1 *b = new Derived1;
	b->foo1(1);	   // Base1 1, 因为Base和Derived中的foo1并不构成虚函数重载，因为两者签名不同，这里很容易由于书写错误引起问题！
	b->foo1(1.0);  // Base1 1
	b->foo2(1);    // Derived1 1
	b->foo2(1.0);  // Derived1 1

	getchar();
	return 0;
}