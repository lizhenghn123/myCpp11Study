#include <iostream>
#include <functional>
#include <string>
#include <assert.h>
using namespace std;

// 将变参的类型连接在一起作为字符串并返回出来

template< typename First, typename... Rest>
struct ConnectArgs //<First, Rest...>
{
	static string GetName()
	{
		return typeid(First).name() + string("_") + ConnectArgs<Rest...>::GetName();
	}
};

template<typename Last>
struct ConnectArgs<Last>
{
	static string GetName()
	{
		return typeid(Last).name();
	}
};


string GetNameofArgsType()
{
	return "";
}

template <typename First>
string GetNameofArgsType()
{
	return std::string(typeid(First).name());
}

template <typename First, typename Second, typename... Args>
string GetNameofArgsType()
{
	return GetNameofArgsType<First>() + "_" + GetNameofArgsType<Second, Args...>();
}

void TestConnectArgs()
{
	auto str = ConnectArgs<int, double, int*>::GetName();
	cout << str << "\n";

	str = GetNameofArgsType<int, double, int*>();
	cout << str << "\n";

	str = ConnectArgs<int, double, string>::GetName();
	cout << str << "\n";

	str = GetNameofArgsType<int, double, string>();
	cout << str << "\n";

}

int main()
{
	TestConnectArgs();
	cout << "*************************\n";

	system("pause");
}