//============================================================================
// Name        : TCPServer.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <sdo/net/Connection.h>
#include <sdo/net/IOServiceAgent.h>
#include <sdo/server/BaseServer.h>
using namespace std;
using namespace sdo::net;
int main() {
	boost::shared_ptr<IOServiceAgent> io_agent(new IOServiceAgent);
	io_agent->init(5,5);
	io_service io_ser;
	sdo::server::BaseServer server(io_ser,io_agent,8081,10000);
	server.start();
	io_ser.run();
//	while(true){
//
//	}
	return 0;
}
