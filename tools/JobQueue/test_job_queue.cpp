#include <iostream>
#include <vector>
#include "JobQueue.h"
using namespace std;


void test_ojb_queue()
{
	{
		ZL::JobQueue<int> queue;
		queue.Push(1);
		queue.Push(3);
		queue.Push(2);
		queue.Push(0);

		int p = -1;
		while (true)
		{
			if (queue.TryPop(p))
				std::cout << p << "\n";
			else
				break;
		}
		std::cout << "================\n";
	}
	{
		ZL::FiloJobQueue<int> queue;
		queue.Push(1);
		queue.Push(3);
		queue.Push(2);
		queue.Push(0);

		int p = -1;
		while (true)
		{
			if (queue.TryPop(p))
				std::cout << p << "\n";
			else
				break;
		}
		std::cout << "================\n";
	}
	{
		//ZL::JobQueue<int, std::priority_queue<int>, ZL::tagPRIO > queue;
		ZL::PrioJobQueue<int> queue;
		queue.Push(1);
		queue.Push(3);
		queue.Push(2);
		queue.Push(0);

		int p = -1;
		while (true)
		{
			if (queue.TryPop(p))
				std::cout << p << "\n";
			else
				break;
		}
		std::cout << "================\n";
	}
}

int main()
{
	test_ojb_queue();

	std::cout << "OK\n";
	getchar();
	return 0;
}