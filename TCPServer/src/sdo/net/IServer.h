/*
 * IServer.h
 *
 *  Created on: 2017年3月27日
 *      Author: myron
 */

#ifndef SDO_NET_ISERVER_H_
#define SDO_NET_ISERVER_H_
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>
#include <sdo/net/Connection.h>
#include <sdo/net/IOServiceAgent.h>
using namespace boost::asio;
namespace sdo {
namespace net {

class IServer: private boost::noncopyable {
public:
	IServer(const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
	IServer(io_service& io_ser, const boost::shared_ptr<IOServiceAgent>& io_agent,unsigned int port,int time_out_millisec=10000);
	virtual ~IServer() {}
	int start();
	/**
	 * 用于判断是否读到一个完整的数据包
	 *@param data 目前读取到的数据
	 *@param bytes 目前读取到的数据长度
	 *@return data's length that need to read left
	 */
	virtual size_t readProgressHandler(const char* data, size_t bytes){ return 1;};
	/**
	 * 读取到完整包数据后回调的处理函数. 当然, 如果读取到一个错误的包,也要在此处理
	 *@param conn 当前链接
	 *@param 包数据
	 *@param 数据长度
	 */
	virtual void readCompleteHandler(boost::shared_ptr<Connection> conn, const char* data, size_t bytes){};
	/**
	 * 链接被关闭时触发
	 */
	virtual void connectionCloseHandler(boost::shared_ptr<Connection> conn, const boost::system::error_code& ec){};
	/**
	 * 建立链接成功后触发. 只有在客户端链接的时候回用到.因此服务端可以不做实现
	 */
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

#endif /* ISERVER_H_ */
