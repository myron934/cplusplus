/*
 * IServer.cpp
 *
 *  Created on: 2017年3月27日
 *      Author: myron
 */

#include <sdo/net/IServer.h>
#include <iostream>
namespace sdo {
namespace net {
IServer::IServer(const boost::shared_ptr<IOServiceAgent>& io_agent,
		unsigned int port, int time_out_millisec) :
		io_agent_(io_agent), acceptor_(io_agent->getIOService()), time_out_millisec_(
				time_out_millisec), port_(port),started_(false) {

}

IServer::IServer(io_service& io_ser,
		const boost::shared_ptr<IOServiceAgent>& io_agent, unsigned int port,
		int time_out_millisec) :
		io_agent_(io_agent),acceptor_(io_ser), time_out_millisec_(time_out_millisec), port_(port),started_(false) {
}

int IServer::start() {
	if(started_) return 0;
	boost::system::error_code ec;
	acceptor_.open(ip::tcp::v4(),ec);
	if(ec){
		return -1;
	}
	acceptor_.set_option(ip::tcp::acceptor::reuse_address(true),ec);
	acceptor_.set_option(ip::tcp::no_delay(true),ec);
	acceptor_.bind(ip::tcp::endpoint(ip::tcp::v4(),port_),ec);
	if(ec){
		return -2;
	}
	acceptor_.listen(socket_base::max_connections,ec);
	if(ec){
		return -3;
	}
	started_=true;
	doAccept();
	return 0;
}
void IServer::doAccept() {
	boost::shared_ptr<Connection> conn=Connection::newInstance(0,'s',io_agent_->getIOService(),time_out_millisec_);
	acceptor_.async_accept(conn->getSocket(),boost::bind(&IServer::onAccept,this,_1,conn));
}

void IServer::onAccept(const boost::system::error_code& ec,boost::shared_ptr<Connection> conn) {
	doAccept();
	if(ec){

	}
	else{
		conn->setHeartPacket(heart_packet_);
		conn->setConnectionCompleteHandler(boost::bind(&IServer::connectionCompleteHandler,this,_1,_2));
		conn->setConnectionClosedHandler(boost::bind(&IServer::connectionCloseHandler,this,_1,_2));
		conn->setReadProcessHandler(boost::bind(&IServer::readProgressHandler,this,_1,_2));
		conn->setReadCompleteHandler(boost::bind(&IServer::readCompleteHandler,this,_1,_2,_3));
		if(0!=conn->start()){
//			conn_set_.erase(conn);
		}
	}

}
} /* namespace net */
} /* namespace sdo */


