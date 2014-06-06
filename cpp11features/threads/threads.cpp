#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
using namespace std;
//http://cpp1x.org/Thread.html  http://zh.cppreference.com/w/cpp/thread

//          std::thread
/***
std::thread的成员函数：
join   :阻塞调用线程(这里是住线程)，直到该线程运行结束。
swap   : 把两个线程的相关操作(underlying handles)互换。
detach : 允许线程对象继续独立的运行。Detach 的线程不再可连接(你不用等它们了)。

std::this_thread提供的函数
get_id    : 返回当前线程的 ID；
yield     : 告诉调度程序，运行其他线程(在你处于忙等待的时候非常有用)；
sleep_for : 阻塞当前线程直到指定的时段(sleep_duration)；
sleep_util: 阻塞当前线程直到指定的时间(sleep_time)；
***/
void func1()
{
	std::cout << "func1()\n";
}

// 和上面的无參函数func1同名，会导致两个函数都无法作为thread的线程函数
// cannot convert argument 1 from 'overloaded-function' to 'std::thread &&'
//void func1(int& a) 
//{
//	std::cout << "func(int& a)\n";
//}

//可以给线程函数传递任意多的参数
void func2(int i, double d, const std::string& s)
{
	std::cout << i << ", " << d << ", " << s << "\n";
	std::cout << "func2()\n";
}

//以引用方式传递，注意线程函数默认都是以值方式传递的，除非使用 std::ref 或者std::cref 进行转换
void func3(int& a)
{
	a ++;
	std::cout << "func3()\n";
}

int func4(const int& a)
{
	std::cout << "func4()\n";
	return a + 100;
}

class SomeClass
{
public:
	int PrintString(const std::string& str) { std::cout << str << "\n";  return 1; }
};

void test_thread()
{
	std::cout << "test_thread id: " << std::this_thread::get_id() << "\n";
	{
		std::thread t(func1); //记住：这里不能有重载，也即不能有两个同名函数func1，即使函数签名不一样
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		t.join();
		std::cout << t.get_id() << "\t" << std::this_thread::get_id() << "\n";
		//t.detach();
		std::cout << "-----------------------\n";
	}
	{   //传递多个参数
		std::thread t(func2, 1, 12.50, "sample");
		t.join();
		std::cout << "-----------------------\n";
	}
	{	//按引用方式传参时，传递的参数必须使用 std::ref 或者std::cref 进行转换		
		int a = 42;
		std::thread t(func3, std::ref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//按const引用方式传参		
		int a = 42;
		std::thread t(func4, std::cref(a));
		t.join();
		std::cout << a << std::endl;
		std::cout << "-----------------------\n";
	}
	{	//绑定类成员函数为线程执行函数
		
		SomeClass sc;
		std::string str("Hello,World!");
		std::thread t(&SomeClass::PrintString, &sc, std::cref(str));
		t.join();		
		std::cout << "-----------------------\n";
	}
}


//          std::mutex
/***
C++11 在 <mutex> 头文件中提供了四种 mutex 来做同步操作:
mutex           : 提供了核心函数 lock(), unlock() 和 非阻塞的 trylock_() 函数(判断 mutex 是否可用)；
recursive_mutex : 允许相同线程多次获得mutex；
timed_mutex     : 和mutex类相似，但是它有自己的两个核心方法trylock__for()和rylock__until(),用来尝试在指定的时间段或者时间点获取mutex；
recursive_timed_mutex : timed_mutex 和 recursive_mutex 的综合体
***/
std::mutex glock_;
void func()
{
	std::lock_guard<std::mutex> locker(glock_);
	//glock_.lock();
	std::cout << "entered thread " << std::this_thread::get_id() << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(rand() % 10));
	std::cout << "leaving thread " << std::this_thread::get_id() << std::endl;
	//glock_.unlock();
}

void test_mutex()
{
	srand((unsigned int)time(0));

	std::thread t1(func);
	std::thread t2(func);
	std::thread t3(func);

	t1.join();
	t2.join();
	t3.join();
}

//           safe container
template <typename T>
class container
{
public:
	void add(T element)
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		elements_.push_back(element);
	}

	void addrange(int num, ...)
	{
		va_list arguments;

		va_start(arguments, num);
		for (int i = 0; i < num; i++)
		{
			std::lock_guard<std::recursive_mutex> locker(lock_);
			add(va_arg(arguments, T));
		}
		va_end(arguments);
	}

	void dump()
	{
		std::lock_guard<std::recursive_mutex> locker(lock_);
		std::copy(elements_.begin(), elements_.end(), std::ostream_iterator<T>(std::cout, "\t"));
		std::cout << "\n";
	}
private:
	std::recursive_mutex lock_; //这里不能使用mutex，因为addrange里调用add时多次获取锁，会造成死锁，当然也有其他办法（抽取函数）
	std::vector<T> elements_;
};

void test_safe_vector()
{
	container<int> cc;
	cc.add(1);
	cc.addrange(5, 3, 4, 5, 6, 9);
	cc.dump();
}

//         dead lock
class SomeType
{
public:
	std::mutex mutex_;
};

void ChangeTwoObj(SomeType& lhs, SomeType& rhs)
{
	//lhs.mutex_.lock();  //这种情况下容易造成死锁
	//rhs.mutex_.lock();
	std::lock(lhs.mutex_, rhs.mutex_); // Ok, 不会死锁

	//do something .....

	lhs.mutex_.unlock();
	rhs.mutex_.unlock();
	std::cout << "ChangeTwoObj Over\n";
}

void test_deadlock()
{
	SomeType s1, s2;

	std::thread t1(ChangeTwoObj, std::ref(s1), std::ref(s2));
	std::thread t2(ChangeTwoObj, std::ref(s2), std::ref(s1));
	t1.join();
	t2.join();
}


//         condition variable
/***
注意：
std::condition_variable只适用于std::unique_lock<std::mutex>。
condition_variable_any可以运行在任何用户定义的锁，以满足BasicLockable要求。
condition_variable_any提供了类似std::condition_variable的功能，它是一个可以用来锁定一些线程的同步原语。
***/
void test_condition_variable()
{
	std::queue<int> produced_nums;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;
	bool notified = false;

	std::thread producer([&]() {
		for (int i = 0; i < 5; ++i) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			std::unique_lock<std::mutex> lock(m);
			std::cout << "producing " << i << '\n';
			produced_nums.push(i);
			notified = true;
			cond_var.notify_one();
		}

		done = true;
		cond_var.notify_one();
	});

	std::thread consumer([&]() {
		std::unique_lock<std::mutex> lock(m);
		while (!done) {
			while (!notified) {  // loop to avoid spurious wakeups
				cond_var.wait(lock);
			}
			while (!produced_nums.empty()) {
				std::cout << "consuming " << produced_nums.front() << '\n';
				produced_nums.pop();
			}
			notified = false;
		}
	});

	producer.join();
	consumer.join();
}

//         Futures
void test_future()
{

}


int main()
{
	test_thread();
	std::cout << "- - - - - - - - - - - - -\n";

	test_mutex();
	std::cout << "- - - - - - - - - - - - -\n";

	test_safe_vector();
	std::cout << "- - - - - - - - - - - - -\n";

	test_deadlock();
	std::cout << "- - - - - - - - - - - - -\n";

	test_condition_variable();
	std::cout << "- - - - - - - - - - - - -\n";

	test_future();
	std::cout << "- - - - - - - - - - - - -\n";

	getchar();
	return 0;
}