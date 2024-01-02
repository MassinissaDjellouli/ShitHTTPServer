#include "StringUtils.h"
std::list<std::string> ShitHTTP::StringUtils::split(std::string toSplit, std::string delimiter) {
	std::list<std::string> list;
	char nextToken;
	char* nextTokenP = &nextToken;
	char* ptr = strtok_s((char*)toSplit.c_str(), delimiter.c_str(), &nextTokenP);
	while (ptr != NULL)
	{
		if (ptr != NULL)
		{
			list.push_back(ptr);
			ptr = strtok_s(NULL, delimiter.c_str(), &nextTokenP);
		}
	}
	return list;
}