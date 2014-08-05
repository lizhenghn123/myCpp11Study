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
		typedef char YES;
		typedef struct { char a[2]; } NO;

		template <typename C>
		static YES test_t(int C::*);

		template <typename C>
		static NO test_t(...);
	public:
		enum { value = sizeof(test_t<T>(0)) == sizeof(YES) };
	};

} /* namespace ZL */

#endif /* ZL_CHECKISCLASS_H */
