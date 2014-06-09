#include <iostream>
#include <vector>
#include "JobQueue.h"
using namespace std;


void test_ojb_queue()
{
	{
		JobQueue<int> queue;
		queue.Push(1);
		queue.Push(3);
		queue.Push(2);

		int p = 0;
		while (true)
		{
			if (queue.Pop(p))
				std::cout << p << "\n";
			else
				break;
		}
		std::cout << "================\n";
	}
	{
		//JobQueue<int, std::priority_queue<int> > queue;
		//queue.Push(1);
		//queue.Push(3);
		//queue.Push(2);

		//int p = 0;
		//while (true)
		//{
			//if (queue.Pop(p))
			//	std::cout << p << "\n";
			//else
			//	break;
		//}
		//std::cout << "================\n";
	}
}

int main()
{
	test_ojb_queue();

	std::cout << "OK\n";
	getchar();
	return 0;
}