#include <iostream>
#include "range.hpp"
using namespace std;

void test_range()
{
	cout << "Range(15):";
	for (auto i : Range(15)){
		cout << " " << i;  // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14
	}
	cout << endl;

	cout << "Range(2,6):";
	for (auto i : Range(2, 6)){
		cout << " " << i;  // 2 3 4 5
	}
	cout << endl;

	cout << "Range(10.5, 15.5):";
	for (float i : Range(10.5, 15.5)){
		cout << " " << i;  // 10.5 11.5 12.5 13.5 14.5
	}
	cout << endl;

	cout << "Range(35,27,-1):";
	for (int i : Range(35, 27, -1)){
		cout << " " << i;  // 35 34 33 32 31 30 29 28
	}
	cout << endl;

	cout << "Range(2,8,0.5):";
	for (float i : Range(2, 8, 0.5)){
		cout << " " << i;  // 2 2.5 3 3.5 4 4.5 5 5.5 6 6.5 7 7.5
	}
	cout << endl;

	cout << "Range(8,7,-0.1):";
	for (auto i : Range(8, 7, -0.1)){
		cout << " " << i;  // 8 7.9 7.8 7.7 7.6 7.5 7.4 7.3 7.2 7.1
	}
	cout << endl;

	cout << "Range('a', 'z'):";
	for (auto i : Range('a', 'z'))
	{
		cout << " " << i;  // a b c d e f g h i j k l m n o p q r s t u v w x y
	}
	cout << endl;
}

int main()
{
	test_range();

	system("pause");
	return 0;
}