#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <string>
using namespace std;

#pragma warning(disable:4996)


class StopWatch
{
public:
	StopWatch() : m_begin(std::chrono::high_resolution_clock::now()) {}
	void reset() { m_begin = std::chrono::high_resolution_clock::now(); }

	double elapsed() const  //默认输出秒
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	double elapsed_mill() const  //毫秒
	{
		return std::chrono::duration_cast<chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	
	int64_t elapsed_micro() const //微秒
	{
		return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	
	int64_t elapsed_nano() const //纳秒
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}
	
	int64_t elapsed_seconds() const //秒
	{
		return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	int64_t elapsed_minutes() const
	{
		return std::chrono::duration_cast<std::chrono::minutes>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

	int64_t elapsed_hours() const
	{
		return std::chrono::duration_cast<std::chrono::hours>(std::chrono::high_resolution_clock::now() - m_begin).count();
	}

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> m_begin;
};

void test_time()
{
	StopWatch watch;
	std::this_thread::sleep_for(std::chrono::seconds(1));		 
	std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
	std::cout << watch.elapsed() << "\n";
	
	std::chrono::milliseconds ms{ 3 };
	// 6000 microseconds constructed from 3 milliseconds
	std::chrono::microseconds us = 2 * ms; //6000微秒
	// 30Hz clock using fractional ticks
	std::chrono::duration<double, std::ratio<1, 30>> hz30(3.5);
	std::cout << "3 ms duration has " << ms.count() << " ticks\n" << "6000 us duration has " << us.count() << " ticks\n"; // 3  6000

	std::chrono::minutes t1(10); //10 分钟
	std::chrono::seconds t2(60); //60 秒
	std::chrono::seconds t3 = t1 - t2;
	std::cout << t3.count() << " second" << std::endl;  // 540

	typedef std::chrono::duration<int, std::ratio<60 * 60 * 24>> days_type;  //注意这里的std::ratio
	std::chrono::time_point<std::chrono::system_clock, days_type> today = std::chrono::time_point_cast<days_type>(std::chrono::system_clock::now());
	std::cout << today.time_since_epoch().count() << " days since epoch" << std::endl; //返回当前时间距离1970年1月1日有多少天

	using namespace std::chrono;
	system_clock::time_point now = system_clock::now();
	std::time_t last = system_clock::to_time_t(now - std::chrono::hours(24));
	std::time_t next = system_clock::to_time_t(now - std::chrono::hours(24));
	tm *t = std::localtime(&next);
	std::cout << "One day ago, the time was " << (t->tm_year + 1900) << '-' << t->tm_mon + 1 << "-" << t->tm_mday + 1 << " "
		<< t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << "\n";

	{
		std::chrono::steady_clock::time_point t1 = std::chrono::system_clock::now();
		std::cout << "Hello World\n";
		std::chrono::steady_clock::time_point t2 = std::chrono::system_clock::now();
		std::cout << (t2 - t1).count() << " tick count\n";
		std::cout << std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() << " microseconds\n";
	}
	{
		auto t = chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		cout << std::put_time(std::localtime(&t), "%Y-%m-%d %X\n");
		cout << std::put_time(std::localtime(&t), "%Y-%m-%d %H.%M.%S\n");
	}
}

int main()
{
	test_time();

	getchar();
	return 0;
}