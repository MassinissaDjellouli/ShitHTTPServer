#include <iostream>
#include "HTTPServer.h";
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
using namespace ShitHTTP;

HTTPServer* instance;
void my_handler(sig_atomic_t s) {
	std::cout << "CTRL + C catched. Closing sockets... \n";
	if (instance == nullptr) {
		exit(0);
	}
	instance->close();
}
int main() {

	signal(SIGINT, my_handler);
	instance = HTTPServer::create(8080);
	instance->startHandlingRequests();
}