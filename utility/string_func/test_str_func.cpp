#include <iostream>
#include "strFunc.hpp"
using namespace std;

int main()
{
	string str1 = ZL::ToStr(100.123);
	wstring wstr1 = ZL::ToStr<double, wchar_t>(100.123);
	cout << str1 << "\n";
	wcout << wstr1 << "\n";

	string str2 = " fg t5rt $%^   !  ";
	ZL::Trim(str2);  // "fg t5rt $%^   !"
	cout << str2 << "\n";
	str2 = " fg t5rt $%^   !  ";
	ZL::TrimAll(str2);  // "fgt5rt$%^!"
	cout << str2 << "\n";

	str2 = "ttdgfh t34 0-tt";
	ZL::Erase(str2, 't');   // dgfh 34 0-
	cout << str2 << "\n";

	str2 = "ttd gfht t34 0-tt";
	ZL::Replace(str2, std::string("tt"), std::string("123"));   // 123dgfh t34 0-123
	cout << str2 << "\n";

	std::vector<std::string> vec;
	str2 = "ttd gfht t34 0-tt";
	ZL::Split(str2, vec, std::string("t"), true);   // " d gfh     34 0-"
	
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<string>(std::cout, " "));
	cout << "\n";

	vec.clear();
	str2 = "ttd gfht t34 0-tt";
	ZL::Split(str2, vec, std::string("t"), false); // "d gfh   34 0 -"
	std::copy(vec.begin(), vec.end(), std::ostream_iterator<string>(std::cout, " "));
	cout << "\n";

	system("pause");
	return 0;
}