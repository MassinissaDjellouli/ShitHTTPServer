#include <iostream>
#include "HTTPServer.h";

using namespace ShitHTTP;

int main() {

	int osFlag;
	#if __linux__
	osFlag = 0;
	#elif _WIN32
	osFlag = 1;
	#else
	osFlag = 2;
	#endif
	HTTPServer* s = HTTPServer::create(osFlag);
}