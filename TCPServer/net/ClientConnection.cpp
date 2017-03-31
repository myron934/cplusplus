/*
 * ClientConnection.cpp
 *
 *  Created on: 2017年1月30日
 *      Author: myron
 */

#include "ClientConnection.h"
#include <sstream>
#include <cstring>
#include <boost/bind.hpp>
#include <iostream>
#include "LogHelper.h"
namespace com {
namespace sdo {


/**
 * 写数据. 写完更新计时
 *@param buffer 要发送的数据包
 */
void ClientConnection::doWrite(const char* buffer, size_t bytes) {
	LOG_ENTER_FUNCTION
	if ( !started_ ) return;
	std::ostream os(&write_buffer_);
	os.write(buffer,bytes);
	async_write(socket_,write_buffer_, boost::bind(&ClientConnection::onWrite,this,_1,_2));
//	客户端发送数据完成以后,就重新计时,避免发送不必要的心跳包
	last_ping_ = boost::posix_time::microsec_clock::local_time();
}

/**
 * 异步写数据完成后调用
 *@param err 错误描述
 *@param bytes 已发送的字节数
 */
void ClientConnection::onWrite(const boost::system::error_code& err, size_t bytes) {
    LOG_ENTER_FUNCTION
    if (err){
        std::cerr<<__FILE__<<":"<<__LINE__<<"->"<<__FUNCTION__<<" "<<err.message()<<std::endl;
        stop();
    }
}

/**
 * 连接到服务器.
 * @param ep 地址和端口
 * @return 成功返回0 , 否则返回-1
 */
int ClientConnection::connect(ip::tcp::endpoint& ep) {
	LOG_ENTER_FUNCTION
	ep_=ep;
	return connect();
}

/**
 * 使用默认的地址和端口连接到服务器.
 * @return 成功返回0 , 否则返回-1
 */
int ClientConnection::connect() {
	boost::system::error_code err;
	socket_.connect(ep_,err);
	if(err){
		std::cout<<err.message()<<std::endl;
		return -1;
	}
	else return 0;
}

/**
 * 读取到一个完整数据包后异步调用
 * @param err 错误描述
 * @param bytes 读取到的数据字节数
 */
void ClientConnection::onRead(const boost::system::error_code& err, size_t bytes) {
    LOG_ENTER_FUNCTION
    if (err){
    	std::cout<<err.message()<<std::endl;
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
 * 发送心跳包
 * 当发现超过一定时间没有与服务器进行数据交互(发送数据),则发送心跳包
 */
void ClientConnection::onCheckPing(const boost::system::error_code& err) {
	LOG_ENTER_FUNCTION
	if(err){
		std::cout<<__FILE__<<":"<<__LINE__<<"->"<<__FUNCTION__<<"."<<err.message()<<std::endl;
		return;
	}
	if(!started_) return;
	boost::posix_time::ptime now=boost::posix_time::microsec_clock::local_time();
	if((now-last_ping_).total_milliseconds()>=time_out_sec_){
		doWrite(ping_.c_str(),ping_.length());
	}
	doCheckPing();
}

boost::shared_ptr<ClientConnection> ClientConnection::newInstance(int id,
		io_service& service, unsigned int time_out_sec) {
	boost::shared_ptr<ClientConnection> instance(new ClientConnection(id,service,time_out_sec));
		return instance;
}

} /* namespace sdo */
} /* namespace com */

