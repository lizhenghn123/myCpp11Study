//http://www.devbean.net/2012/05/cpp11-decltype/
#include <iostream>
using namespace std;



//decltype关键字用于查询表达式的类型,且是在编译期就能推导出表达式类型
/***
对于decltype( e )而言，其判别结果受以下条件的影响：
1. 如果e是一个标识符或者类成员的访问表达式，则decltype(e)就是e所代表的实体的类型。
如果没有这种类型或者e是一个重载函数集，那么程序是错误的（下例中的 (2) 和 (3)）；
2. 如果e是一个函数调用或者一个重载操作符调用（忽略e外面的括号），那么decltype(e)就是该函数的返回类型（下例中的 (1)）；
3. 如果e不属于以上所述的情况，则假设e的类型是 T：当e是一个左值时，decltype(e)就是T&；
否则（e是一个右值），decltype(e)是T（下例中的 (4) 即属于这种情况。
在这个例子中，e实际是(a->x)，由于有这个括号，因此它不属于前面两种情况，所以应当以本条作为判别依据。而(a->x)是一个左值，因此会返回double &）。
4. decltype((e))的结果永远是引用，而decltype(e)结果只有当 e 本身就是一个引用时才是引用
***/
const int&& foo();
struct A { double x; };
void test_decltype()
{
	{
		int i;
		const A* a = new A();

		decltype(foo())  x1 = 2;  // const int&&    (1)
		decltype(i)      x2;      // int			(2)
		decltype(a->x)   x3;      // double			(3)
		decltype((a->x)) x4 = 1;  // double&		(4)
	}
	{
		int    i;
		float  f;
		double d;

		typedef decltype(i + f) type1;  // float
		typedef decltype(f + d) type2;  // double
		typedef decltype(f < d) type3;  // bool
	}
}

//decltype在模板编程中用处
//如下例，当处理模板时，根本不知道 T 和 U 的实际类型。即使这两个模板值实际都是 C++ 内置类型，我们也无法确切地知道它们的和的类型。
template<typename T, typename U>
auto foo(T t, U u) -> decltype(t + u) { return t + u; }
//template<typename T, typename U>
//decltype(t + u) foo(T t, U u){ return t + u; }  //Error!因为t和u在定义前就出现了，但直到编译器解析到函数原型的后半部时，t和u才是有意义的

void test_decltype_in_template()
{
	auto v = foo(1, 1.0);
}

int main()
{
	test_decltype();
	test_decltype_in_template();

	std::cout << "success\n";
	getchar();
	return 0;
}