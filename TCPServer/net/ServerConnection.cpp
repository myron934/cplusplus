/*
 * ServerConnection.cpp
 *
 *  Created on: 2017年1月30日
 *      Author: myron
 */

#include "ServerConnection.h"
#include <sstream>
#include <cstring>
#include <boost/bind.hpp>
#include <iostream>
#include "LogHelper.h"
namespace com {
namespace sdo {

/**
 *超时后,客户端没有再发起请求,服务端采取断开链接操作
 */
void ServerConnection::onCheckPing(const boost::system::error_code& err) {
	LOG_ENTER_FUNCTION
	if(err){
		std::cout<<err.message()<<std::endl;
		return;
	}
	if(!started_) return;
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
size_t ServerConnection::readProgress(const boost::system::error_code& err, size_t bytes) {
    LOG_ENTER_FUNCTION
    if(err) return 0;
    last_ping_ = boost::posix_time::microsec_clock::local_time();
    if(read_progress_handler_.empty()) return 0;
    return read_progress_handler_(buffer_cast<const char*>(read_buffer_.data()),bytes);
}

boost::shared_ptr<ServerConnection> ServerConnection::newInstance(int id,
		io_service& service, unsigned int time_out_sec) {
	boost::shared_ptr<ServerConnection> instance(new ServerConnection(id,service,time_out_sec));
	return instance;
}

} /* namespace sdo */
} /* namespace com */

