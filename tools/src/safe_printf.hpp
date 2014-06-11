// ***********************************************************************
// Filename         : safe_printf.hpp
// Author           : LIZHENG
// Created          : 2014-06-09
// Description      : C++实现的类型安全的printf函数
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-08
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_SAFEPRINTF_FILE_H
#define ZL_SAFEPRINTF_FILE_H
#include <iostream>

namespace ZL
{
	//! C++实现的类型安全的printf函数
	template<typename T, typename... Args>
	void safe_printf(const char* str, T value, Args... args)
	{
		while (*str)
		{
			if (*str == '%' && *(++str) != '%')
			{
				std::cout << value;
				safe_printf(*str ? ++str : str, args...); // 即便当 *s == 0 也会产生调用，以检测更多的类型参数。
				return;
			}
			std::cout << *str++;
		}
		throw std::logic_error("extra arguments provided to printf");
	}

	void safe_printf(const char *str)
	{
		while (*str)
		{
			if (*str == '%' && *(++str) != '%')
				throw std::runtime_error("invalid format string: missing arguments");
			std::cout << *str++;
		}
	}

} /* namespace ZL */

#endif /* ZL_SAFEPRINTF_FILE_H */