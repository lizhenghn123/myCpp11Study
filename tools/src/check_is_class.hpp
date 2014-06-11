// ***********************************************************************
// Filename         : check_is_class.hpp
// Author           : LIZHENG
// Created          : 2014-06-09
// Description      : 判断一个类型是否是类类型，注意，std::is_class即是该功能
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-06-09
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_CHECKISCLASS_H
#define ZL_CHECKISCLASS_H

namespace ZL
{
	template <typename T>
	class is_class
	{
		typedef char one;
		typedef struct { char a[2]; } two;

		template <typename C>
		static one test(int C::*);

		template <typename C>
		static two test(...);
	public:
		enum { value = sizeof(test<T>(0)) == sizeof(one) };
	};

} /* namespace ZL */

#endif /* ZL_CHECKISCLASS_H */