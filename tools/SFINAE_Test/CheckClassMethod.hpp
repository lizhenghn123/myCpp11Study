// ***********************************************************************
// Filename         : CheckClassMethod.hpp
// Author           : LIZHENG
// Created          : 2014-08-04
// Description      : 模板技巧(SFINAE)实现的检测类成员函数功能
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-08-04
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_CHECKCLASSMETHOD_HPP
#define ZL_CHECKCLASSMETHOD_HPP

/********
SFINAE : Substitution failure is not an error, 匹配失败并不是一个错误. SFINAE 是一种专门利用编译器匹配失败的trick.
********/

// 用于检测类型ClassType是否含有成员函数const char* ToString()const;
template<typename ClassType>
struct HasToStringFunction
{
	typedef struct { char a[2]; } Yes;
	typedef struct { char a[1]; } No;

	template<typename FooType, const char* (FooType::*)()const>
	struct FuncMatcher;

	template<typename FooType>
	static Yes Tester(FuncMatcher<FooType, &FooType::ToString>*);

	template<typename FooType>
	static No Tester(...);

	enum
	{
		Value = sizeof(Tester<ClassType>(NULL)) == sizeof(Yes)
	};
};


#endif  /* ZL_CHECKCLASSMETHOD_HPP */