#include <iostream>
#include <memory>
#include <chrono>
#include <functional>
using namespace std;
//#include <boost/chrono/chrono.hpp>
//#include <boost/chrono/system_clocks.hpp>
// AOP : Aspect Oriented Programming, 意为：面向切面编程.
// 通过预编译方式和运行期动态代理实现程序功能的统一维护的一种技术。
// AOP是OOP的延续，是软件开发中的一个热点，也是Spring框架中的一个重要内容，是函数式编程的一种衍生范型。
// 利用AOP可以对业务逻辑的各个部分进行隔离，从而使得业务逻辑各部分之间的耦合度降低，提高程序的可重用性，同时提高了开发的效率。
// see http://www.cnblogs.com/qicosmos/p/3154174.html
// 这种模式可以在不改变原有代码逻辑的情况下， 只在接口调用处组织切面，即可对被调接口进行一系列注册、记录、监听等行为管理。

template <typename WrappedType, typename DerivedAspect>
class BaseAspect
{
protected:
	WrappedType* m_wrappedPtr; //被织入的对象

	//获取派生的切面对象
	DerivedAspect* GetDerived()
	{
		return static_cast<DerivedAspect*>(this);
	}

	//被织入对象的删除器，用来自动触发切面中的After方法
	struct AfterWrapper
	{
		DerivedAspect* m_derived;
		AfterWrapper(DerivedAspect* derived) : m_derived(derived) {};
		void operator()(WrappedType* p)
		{
			m_derived->After(p);
		}
	};
public:
	explicit BaseAspect(WrappedType* p) : m_wrappedPtr(p) {};


	void Before(WrappedType* p) {
		// Default does nothing
	};

	void After(WrappedType* p) {
		// Default does nothing
	}

	//重载指针运算符用来织入切面（Before和After）
	std::shared_ptr<WrappedType> operator->()
	{
		GetDerived()->Before(m_wrappedPtr);
		return std::shared_ptr<WrappedType>(m_wrappedPtr, AfterWrapper(GetDerived()));
	}
};

//织入切面的工厂函数, 返回包含被织入对象的切面
template <template <typename> class Aspect, typename WrappedType>
Aspect<WrappedType> MakeAspect(WrappedType* p)
{
	return Aspect<WrappedType>(p);
}

template<typename WrappedType>
class TimeElapsedAspect : public BaseAspect< WrappedType, TimeElapsedAspect<WrappedType> >
{
	typedef  BaseAspect<WrappedType, TimeElapsedAspect<WrappedType> > BaseAspect;
	typedef std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double> > time_point;

	time_point m_tmBegin;
public:
	TimeElapsedAspect(WrappedType* p) : BaseAspect(p) {}


	void Before(WrappedType* p)
	{
		m_tmBegin = std::chrono::system_clock::now();
	}

	void After(WrappedType* p)
	{
		time_point end = std::chrono::system_clock::now();

		std::cout << "Time: " << (end - m_tmBegin).count() << std::endl;
	}
};

template <typename WrappedType>
class LoggingAspect : public BaseAspect<WrappedType, LoggingAspect<WrappedType> >
{
	typedef  BaseAspect<WrappedType, LoggingAspect<WrappedType> > BaseAspect;
public:
	LoggingAspect(WrappedType* p) : BaseAspect(p) {}

	void Before(WrappedType* p)
	{
		std::cout << "entering" << std::endl;
	}

	void After(WrappedType* p)
	{
		std::cout << "exiting" << std::endl;
	}

};

class IX
{
public:
	IX(){}
	virtual ~IX(){}

	virtual void g() = 0;
private:

};

class X : public IX
{
public:
	void g()
	{
		std::cout << "it is a test" << std::endl;
	}

};

void TestAop()
{
	std::shared_ptr<IX> p(new X());
	MakeAspect<TimeElapsedAspect>(p.get())->g();
	MakeAspect<LoggingAspect>(p.get())->g();
}

// ------------------------------------------------------------ //
struct Aspect
{
	template<typename Func>
	Aspect(const Func& f) : m_func(f)
	{

	}

	template<typename T>
	void Invoke(T&& value)
	{
		value.Before();
		m_func();
		value.After();
	}

	template<typename Head, typename... Tail>
	void Invoke(Head&& head, Tail&&... tail)
	{
		head.Before();
		Invoke(std::forward<Tail>(tail)...);
		head.After();
	}
private:
	Aspect(const Aspect&) = delete;
	Aspect& operator=(const Aspect&) = delete;

private:
	std::function<void()> m_func;
};

template <typename T> 
using identity_t = T;

template<typename... AP>
void Invoke(const std::function<void()>& f)
{

	Aspect msp(f);
	//msp.Invoke(AP()...);    // gcc is ok
	msp.Invoke(identity_t<AP>()...);   // vs203 is ok
}

struct AA
{
	void Before()
	{
		cout << "Before from AA" << endl;
	}

	void After()
	{
		cout << "After from AA" << endl;
	}
};

struct BB
{
	void Before()
	{
		cout << "Before from BB" << endl;
	}

	void After()
	{
		cout << "After from BB" << endl;
	}
};

struct CC
{
	void Before()
	{
		cout << "Before from CC" << endl;
	}

	void After()
	{
		cout << "After from CC" << endl;
	}
};

struct TT
{
	void g()
	{
		cout << "real g function" << endl;
	}

	void h(int a)
	{
		cout << "real h function: " << a << endl;
	}
};

struct DD
{
	void Before()
	{

	}

	void After()
	{

	}
};

void GT()
{
	cout << "real GT function" << endl;
}

void HT(int a)
{
	cout << "real HT function: " << a << endl;
}

void TestAOP()
{
	TT tt;
	std::function<void()> ff = std::bind(&TT::g, &tt);
	//组合了两个切面AA BB
	Invoke<AA, BB>([&ff](){ ff(); }); //织入成员函数
	cout << "-------------\n";

	Invoke<AA, BB>([&tt](){ tt.g(); }); //织入对象
	cout << "-------------\n";

	int aa = 3;
	Invoke<AA, BB>(&GT); //织入方法
	cout << "-------------\n";

	Invoke<AA, BB>([aa](){HT(aa); });//织入带参的方法
	cout << "-------------\n";

	//织入带参数的成员函数和对象
	std::function<void(int)> ff1 = std::bind(&TT::h, &tt, std::placeholders::_1);
	Invoke<AA, BB, CC, DD>([&ff1, aa](){ff1(aa); }); //组合了四个切面
	cout << "-------------\n";

	Invoke<AA, BB>([&tt, aa](){tt.h(aa); });
	cout << "-------------\n";
}

int main()
{
	TestAop();
	cout << "------------------------------------\n";

	TestAOP();

	system("pause");
}