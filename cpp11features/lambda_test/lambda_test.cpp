#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <assert.h>
using namespace std;

//                          Lambda
/***
C++11开始支持匿名函数，也即Lambda函数，Lambda表达式格式如下：
		[capture](parameters)->return-type{body}
如果 parameters没有值的话，括号可以省略。如果body只有一个返回状态或者返回值为void，return-type 经常被省略掉。如下：
		[capture]{body}
一些 lambda 函数举例：
	[](int x, int y) { return x + y; } // implicit return type from 'return' statement
	[](int& x) { ++x; }   // no return statement -> lambda function's return type is 'void'
	[]() { ++global_x; }  // no parameters, just accessing a global variable
	[]{ ++global_x; }     // the same, so () can be omitted
没有return-type的时候，C++11使用decltype来解析返回值类型，当然也可以显式指定：
	[](int x, int y) -> int { int z = x + y; return z; }
lambda函数可以使用lambda函数外面的标志符。这些变量的集合通常被成为闭包，闭包在lambda表达式的[]中定义，允许是值或者引用。如下所示：
	[]        // 不使用任何外部变量，如果使用，就会报错no variables defined. Attempting to use any external variables in the lambda is an error.
	[&]       // 捕获所有要使用的外部变量，且以引用方式传递 any external variable is implicitly captured by reference if used
	[=]       // 捕获所有要使用的外部变量，且以传值方式传递 any external variable is implicitly captured by value if used
	[x, &y]   // x以传值方式使用，y以引用方式 x is captured by value, y is captured by reference
	[&, x]    // x以传值方式使用，其他以引用方式 x is explicitly captured by value. Other variables will be captured by reference
	[=, &x]   // x以引用方式使用，其他以传值方式 x is explicitly captured by reference. Other variables will be captured by value
***/

void test_lambda()
{
	{
		std::vector<int> vec{ 1, 2, 3, 4, 5 };
		int total = 0;
		std::for_each(vec.begin(), vec.end(), [&total](int x) { total += x; });
		std::cout << total << "\n==========\n";   // 15 = 1 + 2 + 3 + 4 + 5

		//查找大于2小于10的元素的个数 : 两种方式对比
		auto f = std::bind(std::logical_and<bool>(), bind(std::greater<int>(), std::placeholders::_1, 2),
												     bind(std::less_equal<int>(), std::placeholders::_1, 10));
		int count1 = count_if(vec.begin(), vec.end(), f);

		int count2 = count_if(vec.begin(), vec.end(), [](int x){return x>2 && x<10; });
		assert(count1 == count2);
	}
	{	//对于不同的参数，传值或传引用可以混和使用。 比方说，用户可以让所有的参数都以传引用的方式使用，但带有一个传值使用的参数：
		std::vector<int> vec{ 1, 2, 3, 4, 5 };
		int value = 5, total = 0;
		//total 以引用的方式传入lambda 函数，而value则是传值。
		std::for_each(std::begin(vec), std::end(vec), [&, value](int x) { total += (x * value); });
		std::cout << total << "\n==========\n"; // 75 = 1*5 + 2*5 + 3*5 + 4*5 + 5*5
	}
	{
		struct Sc
		{
			int GetFour(){ return 4; }
			void AddFour(int& x){ x += 4; }
			void test_lambda()
			{
				std::vector<int> vec{ 1, 2, 3, 4, 5 };
				{
					int value = 5, total = 0;
					std::for_each(vec.begin(), vec.end(), [&total, &value, this](int x) {
						total += x * value * this->GetFour();
					});
					std::cout << total << "\n"; // 300 = 1*5*4 + 2*5*4 + 3*5*4 + 4*5*4 + 5*5*4
				}
				{
					int value = 5, total = 0;
					//调用成员函数，需要捕获this才可以
					std::for_each(vec.begin(), vec.end(), [&total, &value, this](int x) {
						total += x * value;
						this->AddFour(total);
					});
					std::cout << total << "\n==========\n"; // 95 = 1*5+4 + 2*5+4 + 3*5+4 + 4*5+4 + 5*5+4
				}
			}
		};
		Sc sc;
		sc.test_lambda();
	}
}

//lambda函数实现是依赖于类型的函数对象(function object)；类型的名字只有编译器可用。
//如果想把 lambda 函数作为参数来用的话，类型必须是一个模板类型，或者必须创建一个 std::function 或者一个相似的对象去抓取 lambda 值。 
//auto 关键可以用来存储 lambda 函数。  
// http://cpp1x.org/Lambda-Function-And-Expressions.html

double eval(std::function<double(double)> f, double x = 2.0){ return f(x); }

void test_lambda2()
{
	//下面的例子存储匿名函数在变量、vectors，和 arrays 中，然后把他们的名字当参数传递使用：
	
	std::function<double(double)> f0 = [](double x){ return 1; };
	auto                          f1 = [](double x){ return x; };
	decltype(f0)                  fa[3] = { f0, f1, [](double x){ return x*x; } };
	std::vector<decltype(f0)>     fv = { f0, f1 };
	fv.push_back([](double x){return x*x; });
	for (int i = 0; i<fv.size(); i++)  
		std::cout << fv[i](2.0) << "\n";
	std::cout << "==========\n";
	for (int i = 0; i<3; i++)          
		std::cout << fa[i](2.0) << "\n";
	std::cout << "==========\n";
	for (auto &f : fv)             
		std::cout << f(2.0) << "\n";
	std::cout << "==========\n";
	for (auto &f : fa)             
		std::cout << f(2.0) << "\n";
	std::cout << "==========\n";

	std::cout << eval(f0) << "\n";
	std::cout << eval(f1) << "\n";
	std::cout << eval([](double x){return x*x; }) << "\n";
		
	//lambda 如果[] 为空的话，可以隐式转换成一个函数指针和对应的函数指针相同，所以下面是合法的：
	auto my_onheap_lambda_func = new auto([=](int x) { /*...*/ });
	auto a_lambda_func = [](int x) { /*...*/ };
	void(*func_ptr)(int) = a_lambda_func;
	func_ptr(4); //calls the lambda.
}
int main()
{
	test_lambda();
	test_lambda2();

	getchar();
	return 0;
}