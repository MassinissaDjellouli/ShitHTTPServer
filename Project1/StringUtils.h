#pragma once
#include <iostream>
#include <list>
namespace ShitHTTP{
	class StringUtils
	{
	public:
		static std::list<std::string> split(std::string toSplit, std::string delimiter);
	};
}

