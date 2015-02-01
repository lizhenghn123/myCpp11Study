#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <assert.h>
using namespace std;

void test_tuple1()
{
	{
		const char *str = "hello world!";
		std::tuple<const char*, int> tp = std::make_tuple(str, strlen(str));

		const char *data = std::get<0>(tp);
		size_t len = std::get<1>(tp);
		assert(strcmp(str, data) == 0);
		assert(len == strlen(str)); 
	}
	{
		int n = 1;
		auto tp = std::make_tuple(std::ref(n), n); //ref表示引用
		n = 7;
		assert(std::get<0>(tp) == 7 && std::get<1>(tp) == 1);
	}
	{
		auto tp = std::make_tuple(1, "Test", 3.14);   // tp = tuple<int, string, double>
		assert(std::get<0>(tp) == 1 && std::get<1>(tp) == "Test" && std::get<2>(tp) == 3.14);
	}
	{
		auto tp = std::make_tuple(1, string("Test"), 3.14);          // tp = tuple<int&, string&, double&>
		int a; string s; double d;
		std::tie(a, s, d) = tp;

		auto tp1 = std::make_tuple(1, string("Test"), 3.14);
		int a1;  double d1;
		std::tie(a1, std::ignore, d1) = tp;   //用std::ignore占位符来表示不解某个位置的值
		assert(a1 == 1 && d1 == 3.14);
	}
	{
		auto tp = std::make_tuple(1, 2);
		std::get<0>(tp) += 100;
		assert(std::get<0>(tp) == 101 && std::get<1>(tp) == 2);
	}
	{
		std::tuple<float, std::string> tuple1(3.14, "pi");
		std::tuple<int, char> tuple2(65, 'a');
		auto mytuple = std::tuple_cat(tuple1, tuple2);
		std::cout << std::get<0>(mytuple) << "\t";
		std::cout << std::get<1>(mytuple) << "\t";
		std::cout << std::get<2>(mytuple) << "\t";
		std::cout << std::get<3>(mytuple) << "\t";
		std::cout << "\n";
	}
}

template<class Tuple, std::size_t N>
struct TuplePrinter 
{
	static void print(const Tuple& t)
	{
		TuplePrinter<Tuple, N - 1>::print(t);
		std::cout << ", " << std::get<N - 1>(t);
	}
};

template<class Tuple>
struct TuplePrinter<Tuple, 1>
{
	static void print(const Tuple& t)
	{
		std::cout << std::get<0>(t);
	}
};

template<class... Args>
void print_tuple(const std::tuple<Args...>& t)
{
	std::cout << "(";
	TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
	std::cout << ")\n";
}

namespace detail
{
	// 根据tuple元素值获取其对应的索引位置， 查找时是从后向前查找，如有相同元素，则只能找到最后一个的位置
	template<int I, typename T, typename... Args>
	struct find_index
	{
		static int find(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<I - 1>(t) == val) ? I - 1 :
				find_index<I - 1, T, Args...>::find(t, std::forward<T>(val));
		}
	};

	template<typename T, typename... Args>
	struct find_index<0, T, Args...>
	{
		static int find(std::tuple<Args...> const& t, T&& val)
		{
			return (std::get<0>(t) == val) ? 0 : -1;
		}
	};
}

template<typename T, typename... Args>
int find_index(std::tuple<Args...> const& t, T&& val)
{
	return detail::find_index<sizeof...(Args), T, Args...>::find(t, std::forward<T>(val));
}

void test_tuple2()
{
	{
		auto tp = std::make_tuple(1, 3.14);
		std::tuple_element<0, decltype(tp)>::type first = std::get<0>(tp);
		std::tuple_element<1, decltype(tp)>::type second = std::get<1>(tp);
		assert(first == 1 && second == 3.14);
		assert(std::tuple_size<decltype(tp)>::value == 2);   // 获取tuple的大小
		print_tuple(tp);
	}
	{
		std::tuple<int, int, int, int> a(2, 3, 1, 4);
		std::cout << find_index(a, 2) << std::endl; // print 0
		std::cout << find_index(a, 3) << std::endl; // print 1
		std::cout << find_index(a, 1) << std::endl; // print 2
		std::cout << find_index(a, 4) << std::endl; // print 3
		std::cout << find_index(a, 5) << std::endl; // print -1 (not found)
	}
	{
		std::tuple<int, int, int, int> a(1, 3, 1, 4);
		std::cout << find_index(a, 1) << std::endl; // print 2
	}
}

int main()
{
	test_tuple1();
	test_tuple2();

	system("pause");
	return 0;
}