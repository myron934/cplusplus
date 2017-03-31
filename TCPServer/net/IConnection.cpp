/*
 * IConnection.cpp
 *
 *  Created on: 2017年1月23日
 *      Author: myron
 */

#include "IConnection.h"
#include <sstream>
#include <cstring>
#include <boost/bind.hpp>
#include "LogHelper.h"
#include <iostream>
namespace com {
namespace sdo {

IConnection::~IConnection(){
	LOG_ENTER_FUNCTION
	stop();
}

/**
 * 启动链接
 */
void IConnection::start() {
	LOG_ENTER_FUNCTION
	if(started_) return;
	started_=true;
	ip::tcp::socket::reuse_address ra(true);
	socket_.set_option(ra);
	last_ping_=boost::posix_time::microsec_clock::local_time();
	doRead();
    doCheckPing();
}

/**
 * 停止socket
 */
void IConnection::stop() {
	LOG_ENTER_FUNCTION
	if(!started_) return;
	started_=false;
	socket_.close();
	boost::system::error_code ignore_err;
	timer_.cancel(ignore_err);
}

/**
 * 异步读取对方发送过来的数据
 * 同时刷新心跳包计时
 */
void IConnection::doRead() {
	LOG_ENTER_FUNCTION
	if ( !started_ ) return;
//	async_read_until( socket_, read_buffer_, "\n", boost::bind(&IConnection::onRead,shared_from_this(),_1,_2));
	async_read(socket_, read_buffer_,
			boost::bind(&IConnection::readProgress,shared_from_this(),_1,_2),
			boost::bind(&IConnection::onRead,shared_from_this(),_1,_2));
}

/**
 * 读取到一个完整数据包后异步调用
 * @param err 错误描述
 * @param bytes 读取到的数据字节数
 */
void IConnection::onRead(const boost::system::error_code& err, size_t bytes) {
	LOG_ENTER_FUNCTION
	if ( err){
	    stop();
	    return;
	}
	const char* data=buffer_cast<const char*>(read_buffer_.data());
	std::string ping(data,ping_.length());
	if(ping!=ping_&&!read_complete_handler_.empty()){
	    read_complete_handler_(shared_from_this(),data, bytes);
	}
	read_buffer_.consume(bytes);
	//处理完继续进入读取状态
	doRead();
}

/**
 * 异步发送数据
 * @param buffer 要发送的数据buffer
 */
void IConnection::doWrite(const char* buffer, size_t bytes) {
	LOG_ENTER_FUNCTION
	if ( !started_ ) return;
	std::ostream os(&write_buffer_);
	os.write(buffer,bytes);
	std::cout<<"write buffer size:"<<write_buffer_.size()<<std::endl;
	async_write(socket_,write_buffer_, boost::bind(&IConnection::onWrite,shared_from_this(),_1,_2));

}

/**
 * 异步写数据完成后调用
 * @param err 错误描述
 * @param bytes 已发送的字节数
 */
void IConnection::onWrite(const boost::system::error_code& err, size_t bytes) {
	LOG_ENTER_FUNCTION
	if ( err){
		std::cerr<<__FILE__<<":"<<__LINE__<<"->"<<__FUNCTION__<<" "<<err.message()<<std::endl;
		stop();
	}
}

/**
 * 从当前时间开始超时心跳开始计时
 */
void IConnection::doCheckPing() {
	LOG_ENTER_FUNCTION
	timer_.expires_from_now(boost::posix_time::millisec(time_out_sec_));
	timer_.async_wait(boost::bind(&IConnection::onCheckPing,shared_from_this(),_1));
}

/**
 * 超时计时到点后采取的操作. 服务端可能会主动断开链接; 客户端可能发送心跳包
 */
void IConnection::onCheckPing(const boost::system::error_code& err) {
	LOG_ENTER_FUNCTION
	if(err){
		std::cout<<__FILE__<<":"<<__LINE__<<"->"<<__FUNCTION__<<"."<<err.message()<<std::endl;
		return;
	}
	boost::posix_time::ptime now=boost::posix_time::microsec_clock::local_time();
	if((now-last_ping_).total_milliseconds()>=time_out_sec_){
		std::cout<<"time out! connection stopped"<<std::endl;
		stop();
		return;
	}
	doCheckPing();
}

/**
 * 用来判断异步读取数据是否读取到完整的包
 * @param err 错误描述,用来判断是否出错
 * @param bytes 读取到的总字节数
 * @return 还剩下需要读取的字节数. 如果读取完成, 返回0; 否则返回还需要读取的字节数
 */
size_t IConnection::readProgress(const boost::system::error_code& err, size_t bytes) {
	LOG_ENTER_FUNCTION
	if(err) return 0;
	const char* data=buffer_cast<const char*>(read_buffer_.data());
	std::string ping(data,ping_.length());
	if(read_progress_handler_.empty()||ping==ping_) return 0;
	return read_progress_handler_(data,bytes);
}

/**
 * 创建实例
 * @param id 当前链接唯一标识（目前设置中未用到，可以瞎传）
 * @param service boost::asio::io_service
 * @param 超时时间（毫秒）
 */
//boost::shared_ptr<IConnection> IConnection::newInstance(int id,io_service& service,unsigned int time_out_sec) {
//	boost::shared_ptr<IConnection> instance(new IConnection(id,service,time_out_sec));
//	return instance;
//}

/**
 *设置判断数据包是否读取完整的函数
 *@param func 判断函数，入参1是读取到的数据； 入参2是数据长度； 返回剩余还需要读取的数据长度，读取完成返回0
 */
void IConnection::setReadProcessHandler(boost::function<size_t(const char*, size_t)> func) {
    read_progress_handler_=func;
}

/**
 * 设置数据处理函数，当数据包发送完成以后回调
 * @param fun 数据处理回调函数. 入参1 当前连接指针； 入参2 数据包； 入参3, 数据包长度
 */
void IConnection::setReadCompleteHandler(boost::function<void(boost::shared_ptr<IConnection> conn, const char*, size_t)> func) {
    read_complete_handler_=func;
}

} /* namespace sdo */
} /* namespace com */


