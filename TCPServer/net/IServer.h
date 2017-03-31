/*
 * IServer.h
 *
 *  Created on: 2017年3月27日
 *      Author: myron
 */

#ifndef ISERVER_H_
#define ISERVER_H_
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include "Connection.h"
#include "IOServiceAgent.h"
using namespace boost::asio;
namespace com {
namespace sdo {
namespace net {

class IServer {
public:
	IServer(const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
	IServer(io_service& io_ser, const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
	virtual ~IServer() {}
	int start();
	virtual size_t readProgressHandler(const char* data, size_t bytes){ return 1;};
	virtual void readCompleteHandler(boost::shared_ptr<Connection> conn, const char* data, size_t bytes){};
	virtual void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){};
	virtual void connectionCompleteHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){};
	virtual void setHeartPacket(const boost::shared_ptr<streambuf>& buf){
		heart_packet_=buf;
	}

	bool isStarted() const {
		return started_;
	}

private:
	void doAccept();
	void onAccept(const boost::system::error_code& ec,boost::shared_ptr<Connection> conn);

private:
	std::set<boost::shared_ptr<Connection> > conn_set_;
	boost::shared_ptr<IOServiceAgent> io_agent_;
	ip::tcp::acceptor acceptor_;
	int time_out_millisec_;
	boost::shared_ptr<streambuf> heart_packet_; //心跳包
	unsigned int port_;
	bool started_;
};

} /* namespace net */
} /* namespace sdo */
} /* namespace com */

#endif /* ISERVER_H_ */
