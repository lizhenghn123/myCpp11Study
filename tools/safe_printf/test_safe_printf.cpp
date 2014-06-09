#include <iostream>
#include <string>
#include "safe_printf.hpp"
using namespace std;

void test_safe_printf()
{
	ZL::safe_printf("Hello World\n");
	ZL::safe_printf("My name is %s, age is %d, live in %s\n", "lizheng", 26, "Beijing");

	std::string str = __FILE__;
	ZL::safe_printf("This file is %s\n", str.c_str());
}


int main()
{
	test_safe_printf();
	 
	system("pause");
	return 0;
}