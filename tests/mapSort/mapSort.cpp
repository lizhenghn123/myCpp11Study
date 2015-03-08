#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

/// see http://www.cnblogs.com/qicosmos/p/3286057.html

struct Person
{
	string name;
	int age;
	string city;
};


multimap<int, Person> GroupByAge(const vector<Person>& vt)
{
	multimap<int, Person> map;
	std::for_each(vt.begin(), vt.end(), [&map](const Person& person)
	{
		map.insert(make_pair(person.age, person));
	});

	return map;
}

multimap<string, Person> GroupByName(const vector<Person>& vt)
{
	multimap<string, Person> map;
	std::for_each(vt.begin(), vt.end(), [&map](const Person& person)
	{
		map.insert(make_pair(person.name, person));
	});

	return map;
}

//multimap<T, Person> GroupBy(const vector<Person>& vt, const std::function<T(const Person&)> keySlector)
vector<Person> vt = {
		{ "aa", 20, "shanghai" }, { "bb", 25, "beijing" }, { "cc", 25, "nanjing" }, { "dd", 20, "nanjing" } };

template<typename Fn>
multimap<typename std::result_of<Fn(Person)>::type, Person> GroupBy(const vector<Person>& vt, const Fn& keySlector)
{
	// key的类型
	//typedef typename std::result_of<Fn(const Person&)>::type ketype;
	//typedef  decltype(std::declval<Fn>()(std::declval<const Person&>())) ketype;
	//typedef decltype(Fn(Person)) ketype;
	//typedef decltype(keySlector(Person())) ketype;
	typedef typename std::result_of<Fn(Person)>::type ketype;
	multimap<ketype, Person> map;
	std::for_each(vt.begin(), vt.end(), [&](const Person& person)
	{
		map.insert(std::make_pair(keySlector(person), person)); //keySlector返回值就是键值，通过keySelector擦除了类型
	});

	return map;
}

int main()
{
	 vector<Person> vecs = {
			{ "aa", 20, "shanghai" }, { "bb", 25, "beijing" }, { "cc", 25, "nanjing" }, { "dd", 20, "nanjing" } };

	{
		GroupByAge(vecs);
		GroupByName(vecs);
	}

	{
		GroupBy(vecs, [](const Person& person){ return person.age; });  //按年龄分组
		
		GroupBy(vecs, [](const Person& person){ return person.name; }); //按姓名分组
		
		GroupBy(vecs, [](const Person& person){ return person.city; }); //按城市分组
	}

	system("pause");
}
