#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
using namespace std;

//std::unordered_set、std::unordered_multiset、std::unordered_map、std::unordered_multimap
//都是hash容器，其key都是以hash值进行增删改查的。

struct X{ int i, j, k; };

struct hash_X
{
	size_t operator()(const X &x) const
	{
		return hash<int>()(x.i) ^ hash<int>()(x.j) ^ hash<int>()(x.k);
	}
};

std::unordered_map<X, int, hash_X> my_map; //自定义hash函数

void test_map()
{
	{
		std::unordered_map<std::string, int> months;
		months["january"] = 31;
		months["february"] = 28;
		months["march"] = 31;
		months["april"] = 30;
		months["may"] = 31;
		months["june"] = 30;
		months["july"] = 31;
		months["august"] = 31;
		months["september"] = 30;
		months["october"] = 31;
		months["november"] = 30;
		months["december"] = 31;
		std::cout << "september -> " << months["september"] << std::endl;
		std::cout << "april     -> " << months["april"] << std::endl;
		std::cout << "december  -> " << months["december"] << std::endl;
		std::cout << "february  -> " << months["february"] << std::endl;
		std::cout << "\n==============\n";
	}
	{
		std::unordered_multimap<std::string, int> mm;
		mm.insert(std::make_pair("lizheng", 1));
		mm.insert(std::make_pair("lizheng", 2));
		mm.insert(std::make_pair("lizheng", 3));
		mm.insert(std::make_pair("gmail", 0));
		for (auto& itr : mm)
			std::cout << itr.first << "\t" << itr.second << "\n";
		std::cout << "\n==============\n";
	}
}

void test_set()
{
	{
		std::unordered_set<int> st = { 10, 20, 2, 3, 4, 4, 5, 6 };
		for (auto& itr : st)
			std::cout << itr << "\t";    //注意输出只有一个4： 2  10  4  20  3  5  6
		std::cout << "\n==============\n";
	}
	{
		std::unordered_multiset<int> mst = { 10, 1, 20, 3, 3, 3, 4, 5, 6 };
		for (auto& itr : mst)
			std::cout << itr << "\t";
		std::cout << "\n==============\n";
	}
}

int main()
{
	test_map();
	test_set();

	getchar();
	return 0;
}