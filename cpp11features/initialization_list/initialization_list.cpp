#include <iostream>
#include <string>
#include <vector>
#include <complex>
using namespace std;


void foo1(std::string a[]) { }
void foo2(std::initializer_list<std::string> list) { }

struct BasicStruct
{
	int x;
	float y;
};

class SequenceClass
{
public:
	SequenceClass(int i = 0){}
	//初始化列表构造函数
	SequenceClass(std::initializer_list<int> list){}
	SequenceClass(std::initializer_list<string> list){}
};

void test_initialization_list()
{
	std::string a[] = { "Hello", "world" }; // 正确：初始化数组变量
	
	std::vector<std::string> v = { "hello", "world" };
	
	foo1(a);
	//foo1({ "foo", "bar" });   // 编译错误：cannot convert argument 1 from 'initializer-list' to 'std::string []'
	foo2({ "foo", "bar" });     // 正确

	int aa[] = { 1, 2, 3 };     // 用初始化列表进行的赋值风格的初始化

	complex<double> zz(1, 2.0); // 函数风格的初始化, 既可以认为是一个初始化，也可以认为是一个函数调用


	SequenceClass someVar1 = { 1, 2, 3, 4 };         //单一对象初始化，调用初始化列表构造函数
	SequenceClass someVar2 = { "hello", "world" };   //同上
	SequenceClass vsc1[]   = { 1, 2, 3, 4 };         //数组初始化，每个元素调用SequenceClass(int i = 0)构造函数
	SequenceClass vsc2[]   = { { 1, 2 }, { 3, 4 } }; //数组初始化，每个元素调用初始化列表构造函数

	BasicStruct var1{ 5, 3.2f };

	std::vector<int> vec1{ 4 };  //调用初始化列表构造函数，此时vec1中只有一个元素：4
	std::vector<int> vec2( 4 );  //调用std::vector接受一个大小参数的构造函数，此时vec2有4个大小空间，每个元素值为默认

}

int main()
{
	test_initialization_list();

	getchar();
	return 0;
}