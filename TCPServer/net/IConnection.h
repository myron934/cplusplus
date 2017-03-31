/*
 * IConnection.h
 *
 *  Created on: 2017年1月23日
 *      Author: myron
 */

#ifndef ICONNECTION_H_
#define ICONNECTION_H_
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
using namespace boost::asio;


namespace com {
namespace sdo {
/**
 * 连接的基类，实现了基础的连接，读写数据，发送心跳包的函数.
 * 客户端连接和服务器端的连接处理略有不同，因此客户端连接和服务器端连接可以根据需求重载里面的部分函数
 */
class IConnection :public boost::enable_shared_from_this<IConnection>, private boost::noncopyable{
public:
	virtual ~IConnection();
	virtual void start();
	virtual void stop();
	ip::tcp::socket& getSocket(){return socket_;}
	int getConnectionId(){return conn_id_;}
	int isStarted(){return started_;}
	char getType(){return connection_type_;}
	virtual void doRead();
	virtual void doWrite(const char* buffer, size_t bytes);
	virtual void setReadProcessHandler(boost::function<size_t (const char*, size_t )>);
	virtual void setReadCompleteHandler(boost::function<void (boost::shared_ptr<IConnection> conn, const char*, size_t)>);

	void setPing(const std::string& ping) {ping_ = ping;}

	//	static boost::shared_ptr<IConnection> newInstance(int id,io_service& service,unsigned int time_out_sec=10000);

protected:
	IConnection(int id,char conn_type,io_service& service,unsigned int time_out_sec=10000):conn_id_(id),connection_type_(conn_type),started_(0),ping_("@_PING_@"),socket_(service),timer_(service),time_out_sec_(time_out_sec){}
	virtual void onRead(const boost::system::error_code& err, size_t bytes);
	virtual void onWrite(const boost::system::error_code& err, size_t bytes);
	virtual void doCheckPing();
	virtual void onCheckPing(const boost::system::error_code& err);
	virtual size_t readProgress(const boost::system::error_code& err, size_t bytes);


	int conn_id_;//每个connection都有一个id
	char connection_type_;//服务端连接:s 客户端连接: c
	bool started_;//是否已启动
	std::string ping_;
	ip::tcp::socket socket_;
	boost::posix_time::ptime last_ping_;//最后一次ping的时间
	deadline_timer timer_;//用来检查心跳
	int time_out_sec_;//超时时长(毫秒)
	streambuf read_buffer_;//读数据buff
	streambuf write_buffer_;//写数据buff
	boost::function<size_t (const char*, size_t )> read_progress_handler_;
	boost::function<void (boost::shared_ptr<IConnection> conn, const char*, size_t)> read_complete_handler_;
};
} /* namespace sdo */
} /* namespace com */
#endif /* ICONNECTION_H_ */
