#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <windows.h>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
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

//         std::call_once
std::once_flag once_init;
int one = 0, two = 0;
void only_call_once()
{
	one++;
	std::cout << "only_call_once\n";
}
void add_num()
{
	std::call_once(once_init, &only_call_once); //可以用来实现单例程序
	two++;
	std::cout << "add_num\n";
}
void test_call_once()
{
	const int thread_num = 5;
	std::thread threads[thread_num];
	for (int i = 0; i < thread_num; ++i)
	{
		threads[i] = std::thread(add_num);
	}
	for (auto& th : threads)
	{
		th.join();
	}

	std::cout << one << "\t" << two << "\n";  // 1 5
}

//         Futures: promise、future
/***  http://www.cnblogs.com/haippy/p/3280643.html
promise对象可以保存某一类型T的值，该值可被future对象读取（可能在另外一个线程中），因此promise也提供了一种线程同步的手段。
在promise对象构造时可以和一个共享状态（通常是std::future）相关联，并可以在相关联的共享状态(std::future)上保存一个类型为 T 的值。
可以通过 get_future 来获取与该 promise 对象相关联的 future 对象，调用该函数之后，两个对象共享相同的共享状态(shared state):
	promise 对象是异步 Provider，它可以在某一时刻设置共享状态的值。
	future 对象可以异步返回共享状态的值，或者在必要的情况下阻塞调用者并等待共享状态标志变为 ready，然后才能获取共享状态的值。
***/
void print_int(std::future<int>& fut) {
	int x = fut.get(); // 获取共享状态的值.
	std::cout << "value: " << x << '\n'; // value: 10.
}

void test_future_promise()
{
	std::promise<int> prom;					  // 生成一个 std::promise<int> 对象.
	std::future<int> fut = prom.get_future(); // 和 future 关联.
	std::thread t(print_int, std::ref(fut));  // 将 future 交给另外一个线程t.
	prom.set_value(10);						  // 设置共享状态的值, 此处和线程t保持同步.

	t.join();
}
/***
std::packaged_task 包装一个可调用的对象，并且允许异步获取该可调用对象产生的结果，从包装可调用对象意义上来讲，std::packaged_task 与 std::function 类似，
只不过 std::packaged_task 将其包装的可调用对象的执行结果传递给一个 std::future 对象（该对象通常在另外一个线程中获取 std::packaged_task 任务的执行结果）。

std::packaged_task 对象内部包含了两个最基本元素，
	一、被包装的任务(stored task)，任务(task)是一个可调用的对象，如函数指针、成员函数指针或者函数对象，
	二、共享状态(shared state)，用于保存任务的返回值，可以通过 std::future 对象来达到异步访问共享状态的效果。
可以通过 std::packged_task::get_future 来获取与共享状态相关联的 std::future 对象。在调用该函数之后，两个对象共享相同的共享状态，具体解释如下：
	std::packaged_task 对象是异步 Provider，它在某一时刻通过调用被包装的任务来设置共享状态的值。
	std::future 对象是一个异步返回对象，通过它可以获得共享状态的值，当然在必要的时候需要等待共享状态标志变为 ready.
	std::packaged_task 的共享状态的生命周期一直持续到最后一个与之相关联的对象被释放或者销毁为止。
***/
// count down taking a second for each value:
int countdown(int from, int to)
{
	for (int i = from; i != to; --i) 
	{
		std::cout << i << '\n';
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}
	std::cout << "Finished!\n";
	return from - to;
}

void test_future_packaged_task()
{
	{
		std::packaged_task<int(int, int)> task(countdown);  // 设置 packaged_task
		std::future<int> ret = task.get_future();			// 获得与 packaged_task 共享状态相关联的 future 对象.

		std::thread th(std::move(task), 10, 0);				//创建一个新线程完成计数任务.

		int value = ret.get();								// 等待任务完成并获取结果.
		std::cout << "The countdown lasted for " << value << " seconds.\n";
		th.join();
	}
	{
		std::packaged_task<int(int)> tsk([](int x) { return x * 3; }); // package task
		std::future<int> fut = tsk.get_future();		// 获取 future 对象.
		std::thread(std::move(tsk), 100).detach();		// 生成新线程并调用packaged_task.
		int value = fut.get();							// 等待任务完成, 并获取结果.
		std::cout << "The triple of 100 is " << value << ".\n";
	}
}

/***
std::future 可以用来获取异步任务的结果，因此可以把它当成一种简单的线程间同步的手段。
一个有效的 std::future 对象通常由以下三种 Provider 创建，并和某个共享状态相关联。Provider 可以是函数或者类，他们分别是：
	std::async 函数；
	std::promise::get_future，get_future 为 promise 类的成员函数；
	std::packaged_task::get_future，此时 get_future为 packaged_task 的成员函数；
***/
int do_get_value() { return 10; }
bool do_check_prime(int x) 
{
	for (int i = 2; i < x; ++i)
		if (x % i == 0)
			return false;
	return true;
}
double ThreadTask(int n) 
{
	std::cout << std::this_thread::get_id() << " start computing..." << std::endl;
	double ret = 0;
	for (int i = 0; i <= n; i++) 
		ret += std::sin(i);
	std::cout << std::this_thread::get_id()	<< " finished computing..." << std::endl;
	return ret;
}
void do_print_ten(char c, int ms)
{
	for (int i = 0; i < 10; ++i) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
		std::cout << c;
	}
}
void test_future()
{
	{
		std::future<int> fut = std::async(do_get_value);
		std::shared_future<int> shared_fut = fut.share();

		// 共享的 future 对象可以被多次访问.
		std::cout << "value: " << shared_fut.get() << '\n';
		std::cout << "its double: " << shared_fut.get() * 2 << '\n';
	}
	{
		// call function asynchronously:
		std::future < bool > fut = std::async(do_check_prime, 194232491);
		std::cout << "Checking...\n";
		fut.wait();		//被阻塞当前线程，直到共享状态的标志变为 ready
		std::cout << "194232491 ";
		if (fut.get())  // guaranteed to be ready (and not block) after wait returns
			std::cout << "is prime.\n";
		else
			std::cout << "is not prime.\n";
	}
	{
		// call function asynchronously:
		std::future < bool > fut = std::async(do_check_prime, 194232491);

		std::cout << "Checking...\n";
		std::chrono::milliseconds span(10); // 设置超时间隔.

		// 如果超时，则输出"."，继续等待
		while (fut.wait_for(span) == std::future_status::timeout) //阻塞，直至等待了span的时间后wait_until()返回
			std::cout << '.';

		std::cout << "\n194232491 ";
		if (fut.get()) // guaranteed to be ready (and not block) after wait returns
			std::cout << "is prime.\n";
		else
			std::cout << "is not prime.\n";
	}
	{
		std::future<double> f(std::async(std::launch::async, ThreadTask, 100000000)); //async相当于一个线程调用
#if 0
		while (f.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1))!= std::future_status::ready) 
		{
			std::cout << "task is running...\n";
		}
#else
		while (f.wait_for(std::chrono::seconds(1))!= std::future_status::ready) 
		{
			std::cout << "task is running...\n";
		}
#endif
		std::cout << f.get() << std::endl;
	}
	{
		std::cout << "with launch::async:\n";
		std::future < void >foo =
			std::async(std::launch::async, do_print_ten, '*', 100);
		std::future < void >bar =
			std::async(std::launch::async, do_print_ten, '@', 200);
		// async "get" (wait for foo and bar to be ready):
		foo.get();
		bar.get();
		std::cout << "\n\n";

		std::cout << "with launch::deferred:\n";
		foo = std::async(std::launch::deferred, do_print_ten, '*', 100);
		bar = std::async(std::launch::deferred, do_print_ten, '@', 200);
		// deferred "get" (perform the actual calls):
		foo.get();
		bar.get();
		std::cout << '\n';
	}
}

int main()
{
	//test_thread();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_mutex();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_safe_vector();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_deadlock();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_condition_variable();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_call_once();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_future_promise();
	std::cout << "- - - - - - - - - - - - -\n";

	//test_future_packaged_task();
	std::cout << "- - - - - - - - - - - - -\n";

	test_future();
	std::cout << "- - - - - - - - - - - - -\n";

	getchar();
	return 0;
}