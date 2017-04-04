/*
 * Connection.cpp
 *
 *  Created on: 2017年3月23日
 *      Author: myron
 */

#include <sstream>
#include <cstring>
#include <boost/bind.hpp>
#include <iostream>
#include <boost/thread/lock_guard.hpp>
#include <sdo/log/LogHelper.h>
#include <sdo/net/Connection.h>
namespace sdo {
namespace net {
Connection::~Connection(){
	LOG_ENTER_FUNCTION
	stop();
}

/**
 * 作为客户端链接时主动调用这个方法连接服务器
 *@param ip ip地址
 *@param port 端口号
 */
int Connection::asyncConnect(const std::string& ip,
		const unsigned int port, unsigned int time_out_millisec) {
	boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(ip),port);
	socket_.async_connect(ep,boost::bind(&Connection::onConnectedByIp,shared_from_this(),boost::asio::placeholders::error));
	timer_.expires_from_now(boost::posix_time::millisec(time_out_millisec));
    timer_.async_wait(boost::bind(&Connection::onConnectTimeout,shared_from_this(),_1));
    {
        boost::mutex::scoped_lock lock(mtx_);
        time_out_=false;
    }
	return 0;
}

/**
 * 作为客户端链接时主动调用这个方法连接服务器
 *@param ip ip地址
 *@param port 端口号
 *@param handler 链接成功或者失败后的处理函数
 */
int Connection::asyncConnect(const std::string& ip, const unsigned int port,
		boost::function<void(boost::shared_ptr<Connection>,	const boost::system::error_code& )>& handler, unsigned int time_out_millisec) {
	connection_complete_handler_=handler;
	asyncConnect(ip,port,time_out_millisec);
	return 0;
}

/**
 * 作为客户端链接时主动调用这个方法连接服务器
 *@param address 网址: 如 www.baidu.com
 *@param service 协议或者字符串格式的端口号如 http; 8080
 *@param handler 链接成功或者失败后的处理函数
 */
int Connection::asyncConnect(const std::string& address,
		const std::string& service,
		boost::function<void(boost::shared_ptr<Connection>,	const boost::system::error_code&)>& handler, unsigned int time_out_millisec) {
	connection_complete_handler_=handler;
	asyncConnect(address,service,time_out_millisec);
	return 0;
}

/**
 * 作为客户端链接时主动调用这个方法连接服务器
 *@param address 网址: 如 www.baidu.com
 *@param service 协议或者字符串格式的端口号如 http; 8080
 */
int Connection::asyncConnect(const std::string& address,
		const std::string& service, unsigned int time_out_millisec) {
    LOG_ENTER_FUNCTION
	ip::tcp::resolver::query query(address,service);
	resolver_.async_resolve(query,boost::bind(&Connection::onResolved, shared_from_this(),boost::asio::placeholders::error,placeholders::iterator,time_out_millisec));
	timer_.expires_from_now(boost::posix_time::millisec(time_out_millisec));
    timer_.async_wait(boost::bind(&Connection::onConnectTimeout,shared_from_this(),_1));
    {
        boost::mutex::scoped_lock lock(mtx_);
        time_out_=false;
    }
	return 0;
}

/**
 * 调用asyncConnect超时后调用
 * 如果超时没连上,则主动关闭socket
 */
void Connection::onConnectTimeout(const boost::system::error_code& ec) {
    LOG_ENTER_FUNCTION
    //timer正常执行,说明超时
    if(!ec){
        {
            boost::mutex::scoped_lock lock(mtx_);
            time_out_=true;
        }
        boost::system::error_code  err;
        socket_.close(err);
        err=boost::asio::error::make_error_code(boost::asio::error::timed_out);
//        err.assign(boost::asio::error::timed_out,boost::system::system_category());
        if(!connection_complete_handler_.empty()){
            connection_complete_handler_(shared_from_this(),err);
        }
    }
}

/**
 * 解析网址/域名的
 */
void Connection::onResolved(const boost::system::error_code& ec, ip::tcp::resolver::iterator it,unsigned int time_out_millisec){
    LOG_ENTER_FUNCTION
    {
        boost::mutex::scoped_lock lock(mtx_);
        if(time_out_) return;
    }
	if(!ec){
	    ip::tcp::endpoint ep = *it;
	    std::cout<<ep.address().to_string()<<":"<<ep.port()<<std::endl;
		socket_.async_connect(ep,boost::bind(&Connection::onConnectedByAddr,shared_from_this(),boost::asio::placeholders::error,++it));
	}
	else if(boost::system::errc::operation_canceled!=ec.value()){
		if(!connection_complete_handler_.empty()){
			connection_complete_handler_(shared_from_this(),ec);
		}
	}
}

/**
 * 通过ip连接完成后回调
 */
void Connection::onConnectedByIp(const boost::system::error_code& ec) {
    LOG_ENTER_FUNCTION
    boost::system::error_code err;
    timer_.cancel(err);
    {
        boost::mutex::scoped_lock lock(mtx_);
        if(time_out_) return;
    }
	if(!ec){
		start();
	}
	if(!connection_complete_handler_.empty()){
		connection_complete_handler_(shared_from_this(),ec);
	}
}

/**
 * 通过网址连接完成后回调
 */
void Connection::onConnectedByAddr(const boost::system::error_code& ec, ip::tcp::resolver::iterator it){
    LOG_ENTER_FUNCTION
    boost::system::error_code err;
    timer_.cancel(err);
    {
        boost::mutex::scoped_lock lock(mtx_);
        if(time_out_) return;
    }
	if(!ec){
		start();
		if(!connection_complete_handler_.empty()){
			connection_complete_handler_(shared_from_this(),ec);
		}
	}
	else if(it!=ip::tcp::resolver::iterator()){
		boost::system::error_code ignore_ec;
		socket_.close(ignore_ec);
		ip::tcp::endpoint ep = *it;
		socket_.async_connect(ep,boost::bind(&Connection::onConnectedByAddr,shared_from_this(),boost::asio::placeholders::error,++it));
	}
	else if(!connection_complete_handler_.empty()){
		connection_complete_handler_(shared_from_this(),ec);
	}
}

/**
 * 开始收发数据. 当作为服务端连接时,accept成功后调用;作为客户端连接不需要主动调用这个方法
 *  在调用该方法之前,要保证TCP链接已经建立完毕
 */
int Connection::start() {
	LOG_ENTER_FUNCTION
	if(started_) return 0;
	if(!socket_.is_open()) return -1;
	started_=true;
	ip::tcp::socket::reuse_address ra(true);
	socket_.set_option(ra);
	boost::system::error_code ec;
	boost::asio::ip::tcp::endpoint ep = socket_.remote_endpoint(ec);
	if (ec){
		ip_="";
		port_=0;
	}
	else{
		ip_=ep.address().to_string(ec);
		port_=ep.port();
	}
	last_ping_=boost::posix_time::microsec_clock::local_time();
	doRead();
    doCheckPing();
    return 0;
}

/**
 * 停止socket
 */
int Connection::stop() {
	LOG_ENTER_FUNCTION
	if(!started_) return 0;
	started_=false;
	socket_.close();
	boost::system::error_code ignore_err;
	timer_.cancel(ignore_err);
	return 0;
}

/**
 * 异步读取对方发送过来的数据
 * 同时刷新心跳包计时
 */
int Connection::doRead() {
	LOG_ENTER_FUNCTION
	if ( !started_ ) return -1;
//	async_read_until( socket_, read_buffer_, "\n", boost::bind(&Connection::onRead,shared_from_this(),_1,_2));
	async_read(socket_, read_buffer_,
			boost::bind(&Connection::readProgress,shared_from_this(),_1,_2),
			boost::bind(&Connection::onRead,shared_from_this(),_1,_2));
	return 0;
}

/**
 * 读取到一个完整数据包后异步调用
 * @param err 错误描述
 * @param bytes 读取到的数据字节数
 */
void Connection::onRead(const boost::system::error_code& ec, size_t bytes) {
	LOG_ENTER_FUNCTION
	if (ec){
	    stop();
	    if(!connection_closed_handler_.empty()){
	    	connection_closed_handler_(shared_from_this(),ec);
	    }
	    return;
	}
	//服务端链接收到一个完整数据包,刷新心跳时间
	last_ping_ = boost::posix_time::microsec_clock::local_time();
	const char* data=buffer_cast<const char*>(read_buffer_.data());
	if(!read_complete_handler_.empty()){
	    read_complete_handler_(shared_from_this(),data, bytes);
	}
	read_buffer_.consume(bytes);
	//处理完继续进入读取状态
	doRead();
}

/**
 * 异步发送数据(线程安全的)
 * @param buffer 要发送的数据buffer
 */
int Connection::doWrite(const char* buffer, size_t bytes) {
	LOG_ENTER_FUNCTION
	if ( !started_ ) return -1;
	boost::lock_guard<boost::mutex> lock(mtx_);
	std::ostream os(&write_buffer_);
	os.write(buffer,bytes);
//	std::cout<<"write buffer size:"<<write_buffer_.size()<<std::endl;
	async_write(socket_,write_buffer_, boost::bind(&Connection::onWrite,shared_from_this(),_1,_2));
	return 0;
}

int Connection::doWrite(streambuf& buf){
	LOG_ENTER_FUNCTION
	if ( !started_ ) return -1;
	boost::lock_guard<boost::mutex> lock(mtx_);
	std::ostream os(&write_buffer_);
	os<<&buf;
	async_write(socket_,write_buffer_, boost::bind(&Connection::onWrite,shared_from_this(),_1,_2));
	return 0;
}

/**
 * 异步写数据完成后调用
 * @param err 错误描述
 * @param bytes 已发送的字节数
 */
void Connection::onWrite(const boost::system::error_code& ec, size_t bytes) {
	LOG_ENTER_FUNCTION
	if (ec){
		stop();
		if(!connection_closed_handler_.empty()){
			connection_closed_handler_(shared_from_this(),ec);
		}
	}
}

/**
 * 从当前时间开始超时心跳开始计时
 */
void Connection::doCheckPing() {
	LOG_ENTER_FUNCTION
	timer_.expires_from_now(boost::posix_time::millisec(time_out_millisec_));
	timer_.async_wait(boost::bind(&Connection::onCheckPing,shared_from_this(),_1));
}

/**
 * 超时计时到点后采取的操作. 服务端可能会主动断开链接; 客户端可能发送心跳包
 */
void Connection::onCheckPing(const boost::system::error_code& ec) {
	LOG_ENTER_FUNCTION
	if (ec){
		return;
	}
	boost::posix_time::ptime now=boost::posix_time::microsec_clock::local_time();
	//超时以后,如果是服务端链接,且长时间没有收到客户端数据,会主动断开链接;如果是客户端链接,则会主动发心跳包
	if('s'==connection_type_&&(now-last_ping_).total_milliseconds()>=time_out_millisec_){
        if(!connection_closed_handler_.empty()){
            connection_closed_handler_(shared_from_this(),ec);
        }
        stop();
		return;
	}
	else if('c'==connection_type_&&NULL!=heart_packet_.get()){//作为客户端,则定时发送心跳
	    const char* heart_packet=buffer_cast<const char*>(heart_packet_->data());
        doWrite(heart_packet,heart_packet_->size());
    }
	doCheckPing();
}

/**
 * 创建实例
 *@param id 当前链接唯一标识（目前设置中未用到，可以瞎传）
 *@param conn_type 连接类型 客户端传 c; 服务端传 s
 *@param service boost::asio::io_service
 *@param 超时时间（毫秒）
 */
boost::shared_ptr<Connection> Connection::newInstance(int id, char conn_type,
		io_service& service, unsigned int time_out_millisec) {
	boost::shared_ptr<Connection> instance(new Connection(id,conn_type,service,time_out_millisec));
		return instance;
}

/**
 * 用来判断异步读取数据是否读取到完整的包
 * @param err 错误描述,用来判断是否出错
 * @param bytes 读取到的总字节数
 * @return 还剩下需要读取的字节数. 如果读取完成, 返回0; 否则返回还需要读取的字节数
 */
size_t Connection::readProgress(const boost::system::error_code& ec, size_t bytes) {
	LOG_ENTER_FUNCTION
	if(ec) return 0;
	const char* data=buffer_cast<const char*>(read_buffer_.data());
//	std::string ping(data,bytes);
	//没有回调函数或者是心跳包
//	if(read_progress_handler_.empty()||ping==request_ping_||ping==response_ping_) return 0;
	if(read_progress_handler_.empty()) return 1;
	return read_progress_handler_(data,bytes);
}

} /* namespace net */
} /* namespace sdo */


