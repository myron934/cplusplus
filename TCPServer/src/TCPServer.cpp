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
#include <sdo/server/ProtoBufServer.h>
using namespace std;
using namespace sdo::net;
int main() {
	boost::shared_ptr<IOServiceAgent> io_agent(new IOServiceAgent);
	io_agent->init(1,5);
	io_service io_ser;
	sdo::server::ProtoBufServer server(io_agent,8081,20000);
	if(0!=server.start()){
	    cout<<"启动失败"<<endl;
	    return -1;
	}
	io_agent->joinAll();
	return 0;
}
