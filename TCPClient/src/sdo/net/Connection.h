/*
 * Connection.h
 *
 *  Created on: 2017年3月23日
 *      Author: myron
 */

#ifndef CONNECTION_H_
#define CONNECTION_H_
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
using namespace boost::asio;
namespace sdo {
namespace net {
class Connection:public boost::enable_shared_from_this<Connection>, private boost::noncopyable {
public:
	static boost::shared_ptr<Connection> newInstance(int id,char conn_type,io_service& service,unsigned int time_out_millisec=10000);
	virtual ~Connection();

	int asyncConnect(const std::string& ip, const unsigned int port, unsigned int time_out_millisec=10000);
	int asyncConnect(const std::string& ip, const unsigned int port,boost::function<void (boost::shared_ptr<Connection>, const boost::system::error_code&)>& handler, unsigned int time_out_millisec=10000);
	int asyncConnect(const std::string& address, const std::string& service, unsigned int time_out_millisec=10000);
	int asyncConnect(const std::string& address, const std::string& service, boost::function<void (boost::shared_ptr<Connection>, const boost::system::error_code&)>& handler, unsigned int time_out_millisec=10000);
	int start();
	int stop();
	ip::tcp::socket& getSocket(){return socket_;}
	int getConnectionId(){return conn_id_;}
	int isStarted(){return started_;}
	char getType(){return connection_type_;}
	int doWrite(const char* buffer, size_t bytes);
	int doWrite(streambuf& buf);
	void setHeartPacket(const boost::shared_ptr<streambuf>& buf){
		heart_packet_=buf;
	}
	/**
	 *设置判断数据包是否读取完整的函数
	 *@param func 判断函数，入参1是读取到的数据； 入参2是数据长度； 返回剩余还需要读取的数据长度，读取完成返回0
	 */
	void setReadProcessHandler(const boost::function<size_t (const char*, size_t )>& func){
		read_progress_handler_=func;
	}
	/**
	 * 设置数据处理函数，当数据包发送完成以后回调
	 * @param fun 数据处理回调函数. 入参1 当前连接指针； 入参2 数据包； 入参3, 数据包长度
	 */
	void setReadCompleteHandler(const boost::function<void (boost::shared_ptr<Connection> conn, const char*, size_t)>& func){
		read_complete_handler_=func;
	}

	const std::string& getIp() const {
		return ip_;
	}

	unsigned int getPort() const {
		return port_;
	}

	void setConnectionClosedHandler(
			const boost::function<void(boost::shared_ptr<Connection>,const boost::system::error_code&)>& connectionClosedHandler) {
		connection_closed_handler_ = connectionClosedHandler;
	}

	void setConnectionCompleteHandler(
			const boost::function<void(boost::shared_ptr<Connection>,const boost::system::error_code&)>& connectionCompleteHandler) {
		connection_complete_handler_ = connectionCompleteHandler;
	}

private:
	Connection(int id,char conn_type,io_service& service,unsigned int time_out_millisec=10000):conn_id_(id),connection_type_(conn_type),started_(0),socket_(service),timer_(service),time_out_millisec_(time_out_millisec),port_(0),resolver_(service){}
	int doRead();
	void onRead(const boost::system::error_code& ec, size_t bytes);
	void onWrite(const boost::system::error_code& ec, size_t bytes);
	void doCheckPing();
	void onCheckPing(const boost::system::error_code& ec);
	size_t readProgress(const boost::system::error_code& ec, size_t bytes);
	void onConnectTimeout(const boost::system::error_code& ec);
	void onConnectedByIp(const boost::system::error_code& ec);
	void onConnectedByAddr(const boost::system::error_code& ec, ip::tcp::resolver::iterator it);
	void onResolved(const boost::system::error_code& ec, ip::tcp::resolver::iterator it);

	int conn_id_;//每个connection都有一个id
	char connection_type_;//服务端连接:s 客户端连接: c
	bool started_;//是否已启动
	boost::shared_ptr<streambuf> heart_packet_;
	ip::tcp::socket socket_;
	boost::posix_time::ptime last_ping_;//最后一次ping的时间
	deadline_timer timer_;//用来检查心跳
	int time_out_millisec_;//超时时长(毫秒)
	streambuf read_buffer_;//读数据buff
	streambuf write_buffer_;//写数据buff
	boost::mutex mtx_;
	boost::function<size_t (const char*, size_t )> read_progress_handler_; //进度函数,判断包是否完整
	boost::function<void (boost::shared_ptr<Connection>, const char*, size_t)> read_complete_handler_;//数据处理函数
	boost::function<void (boost::shared_ptr<Connection>, const boost::system::error_code&)> connection_closed_handler_;//连接关闭时的回调函数
	boost::function<void (boost::shared_ptr<Connection>, const boost::system::error_code&)> connection_complete_handler_; //连接建立完成时的回调函数
	std::string ip_;
	unsigned int port_;
	ip::tcp::resolver resolver_;
};

} /* namespace net */
} /* namespace sdo */

#endif /* CONNECTION_H_ */
