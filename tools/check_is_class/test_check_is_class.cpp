#include <iostream>
#include <string>
#include "check_is_class.hpp"
using namespace std;

class T1
{
	int i;
};
struct T2
{


};

void test_check_is_class()
{
	std::cout << std::is_class<T1>::value << "\t" << std::is_class<T2>::value << "\t"
		<< std::is_class<int>::value << "\t" << std::is_class<std::string>::value << "\n";

	std::cout << ZL::is_class<T1>::value << "\t" << ZL::is_class<T2>::value << "\t"
		<< ZL::is_class<int>::value << "\t" << ZL::is_class<std::string>::value << "\n";
}

int main()
{
	test_check_is_class();

	system("pause");
	return 0;
}

