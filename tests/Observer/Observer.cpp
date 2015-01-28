#include <iostream>
#include <string>
#include <map>
#include <functional>    // for bind, function
using namespace std;

// 使用C++11中的bind，function及变长模版参数实现的观察者/通知者模型
// 类似于C#中的委托
// Subject 支持注册的观测者为函数、函数对象、lambda表达式，而非基于虚函数的类体系
template < typename Func >
class Subject
{
public:
	typedef int ObserverId;
public:
	Subject() : watcherId_(0)
	{

	}

	ObserverId addObserver(const Func& func)
	{
		return addObserver_(func);
	}

	ObserverId addObserver(Func&& func)
	{
		return addObserver_(func);
	}

	template <typename F>
	void replace(ObserverId key, F&& f)
	{
		watcherList_.emplace(key, std::move(f));
	}

	template <typename F>
	void replace(ObserverId key, const F& f)
	{
		watcherList_.emplace(key, f);
	}

	void removeObserver(ObserverId id)
	{
		watcherList_.erase(id);
	}

	template < typename ... Args>
	void notify(Args&&...args)
	{
		for (auto it : watcherList_)
		{
			it.second(std::forward<Args>(args)...);
		}
	}

	void clear()
	{
		watcherList_.clear();
	}

	ObserverId operator+=(const Func& func)
	{
		return addObserver_(func);
	}

	ObserverId operator+=(Func&& func)
	{
		return addObserver_(func);
	}

private:
	template <typename F>
	ObserverId addObserver_(F&& func)
	{
		watcherList_[++watcherId_] = func;
		return watcherId_;
	}

private:
	ObserverId watcherId_;
	map<ObserverId, Func> watcherList_;

};


void print_argc(int a, string s)
{
	cout << "print_argc : (" << a << ") (" << s << ")\n";
}

struct tes
{
	int a;
	string s;

	void set(int a, string s)
	{
		this->a = a;
		this->s = s;
	}
	void print() 
	{
		cout << "print_tes : (" << a << ") (" << s << ")\n";
	}
};

#include <memory>
#include <typeindex>
struct Any
{
	Any(void) : m_tpIndex(std::type_index(typeid(void))){}
	Any(Any& that) : m_ptr(that.Clone()), m_tpIndex(that.m_tpIndex) {}
	Any(Any && that) : m_ptr(std::move(that.m_ptr)), m_tpIndex(that.m_tpIndex) {}

	//创建智能指针时，对于一般的类型，通过std::decay来移除引用和cv符，从而获取原始类型
	template<typename U> Any(U && value) : m_ptr(new Derived < typename std::decay<U>::type>(forward<U>(value))),
		m_tpIndex(type_index(typeid(typename std::decay <U>::type))){}

	bool IsNull() const { return !bool(m_ptr); }

	template<class U> bool Is() const
	{
		return m_tpIndex == type_index(typeid(U));
	}

	//将Any转换为实际的类型
	template<class U>
	U& AnyCast()
	{
		if (!Is<U>())
		{
			cout << "can not cast " << typeid(U).name() << " to " << m_tpIndex.name() << endl;
			throw bad_cast();
		}

		auto derived = dynamic_cast<Derived<U>*> (m_ptr.get());
		return derived->m_value;
	}

	Any& operator=(const Any& a)
	{
		if (m_ptr == a.m_ptr)
			return *this;

		m_ptr = a.Clone();
		m_tpIndex = a.m_tpIndex;
		return *this;
	}

private:
	struct Base;
	typedef std::unique_ptr<Base> BasePtr;

	struct Base
	{
		virtual ~Base() {}
		virtual BasePtr Clone() const = 0;
	};

	template<typename T>
	struct Derived : Base
	{
		template<typename U>
		Derived(U && value) : m_value(forward<U>(value)) { }

		BasePtr Clone() const
		{
			return BasePtr(new Derived<T>(m_value));
		}

		T m_value;
	};

	BasePtr Clone() const
	{
		if (m_ptr != nullptr)
			return m_ptr->Clone();

		return nullptr;
	}

	BasePtr m_ptr;
	std::type_index m_tpIndex;
};

int main()
{
	{
		Any n;
		auto r = n.IsNull();//true
		string s1 = "hello";
		n = s1;
		n = "world";
		n.AnyCast<int>(); //can not cast int to string
		Any n1 = 1;
		n1.Is<int>(); //true
	}
	Subject< std::function<void(int, string)> > subject;

	auto key1 = subject.addObserver(print_argc);

	tes t;
	auto key2 = subject.addObserver([&t](int a, string s){ t.a = a; t.s = s; });

	cout << "********** notify 1 **********\n";
	subject.notify(1, "hello world");
	t.print();

	subject.removeObserver(key1);
	cout << "********** notify 2 **********\n";
	subject.notify(2, "changed");
	t.print();

	cout << "********** notify 3 **********\n";
	subject.clear();
	
	auto key3 = subject.addObserver([&t](int a, string s){ t.a = a * a; t.s = s; t.print(); });
	auto key4 = subject.addObserver(std::bind(&tes::set, &t, std::placeholders::_1, std::placeholders::_2));

	subject.notify(3, "bind_function");
	t.print();

	system("pause");
}