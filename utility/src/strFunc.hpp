// ***********************************************************************
// Filename         : strFunc.hpp
// Author           : LIZHENG
// Created          : 2014-08-16
// Description      : 字符串辅助函数
//
// Last Modified By : LIZHENG
// Last Modified On : 2014-08-16
// 
// Copyright (c) lizhenghn@gmail.com. All rights reserved.
// ***********************************************************************
#ifndef ZL_STRFUNC_FILE_H
#define ZL_STRFUNC_FILE_H
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <functional>

namespace ZL
{ 
	/** 任意类型转为字符串 */
	template < typename T, typename CharT = char >
	inline std::basic_string<CharT> ToStr(const T& t)
	{
		std::basic_stringstream<CharT> oss;  //std::ostringstream oss;
		oss << t;
		return oss.str();
	}

	/** 去掉字符串中左边的空格 */
	template< typename CharT >
	inline void TrimLeft(std::basic_string<CharT>& str)
	{
		str.erase(0, str.find_first_not_of(' '));
	}

	/** 去掉字符串中右边的空格 */
	template< typename CharT >
	inline void TrimRight(std::basic_string<CharT>& str)
	{
		str.erase(str.find_last_not_of(' ') + 1);
	}

	/** 去掉字符串中两端的空格 */
	template< typename CharT >
	inline void Trim(std::basic_string<CharT>& str)
	{
		TrimLeft(str);
		TrimRight(str);
	}

	/** 去掉字符串中的所有空格 */
	template< typename CharT >
	inline void TrimAll(std::basic_string<CharT>& str)
	{
		str.erase(std::remove_if(str.begin(), str.end(),
			std::bind2nd(std::equal_to<CharT>(), ' ')), str.end());
	}

	/** 去掉字符串中的特定字符 */
	template<typename CharT>
	inline void Erase(std::basic_string<CharT>& str, const CharT& charactor)
	{
		str.erase(std::remove_if(str.begin(), str.end(),
			std::bind2nd(std::equal_to<CharT>(), charactor)), str.end());
	}

	/** 字符串替换 */
	template<typename CharT>
	inline void Replace(std::basic_string<CharT>& str, const std::basic_string<CharT>& strDeliter,
						  const std::basic_string<CharT>& strDest)
	{
		while (true)
		{
			CharT pos = str.find(strDeliter);

			if (pos != std::basic_string<CharT>::npos)
				str.replace(pos, strDeliter.size(), strDest);
			else
				break;
		}
	}
	
	/** 字符串分隔，如果有连续的delim，是否插入空串 */
	template< typename CharT >
	inline void Split(const std::basic_string<CharT>& str, std::vector<std::basic_string<CharT>>& result, 
						const std::basic_string<CharT>& delim = " ", bool insertEmpty = false)
	{
		if (str.empty() || delim.empty())
			return;

		std::string::const_iterator substart = str.begin(), subend;
		while (true)
		{
			subend = std::search(substart, str.end(), delim.begin(), delim.end());
			std::string temp(substart, subend);

			if (!temp.empty())
			{
				if (insertEmpty)
					result.push_back("");
				result.push_back(temp);
			}
			if (subend == str.end())
				break;

			substart = subend + delim.size();
		}
	}

} /* namespace ZL */

#endif  /* ZL_STRFUNC_FILE_H */