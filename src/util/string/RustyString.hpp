/**
 * @file RustyString.hpp
 * @author JoaoAJMatos (github.com/JoaoAJMatos)
 * 
 * @brief This file provides a set of functions to manipulate strings 
 * 
 * @version 0.1
 * @date 2022-07-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef RUSTYSTRING_HPP
#define RUSTYSTRING_HPP

#include <algorithm>
#include <cctype>
#include <locale>

namespace util
{
namespace string
{
      // trim from start (in place)
	inline void ltrim(std::string &s)
	{
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch)
		{
			return !(std::isspace(ch) || ch == '\0');
		}));
	}

      // trm from end (in place)
	inline void rtrim(std::string &s)
	{
		s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch)
		{
			return !(std::isspace(ch) || ch == '\0');
		}).base(), s.end());
	}

	// trim from both ends (in place)
	inline void trim(std::string &s)
	{
		ltrim(s);
		rtrim(s);
	}

	// trim from start (copying)
	inline std::string ltrim_copy(std::string s)
	{
		ltrim(s);
		return s;
	}

	// trim from end (copying)
	inline std::string rtrim_copy(std::string s)
	{
		rtrim(s);
		return s;
	}

	// trim from both ends (copying)
	inline std::string trim_copy(std::string s)
	{
		trim(s);
		return s;
	}
}
}
#endif