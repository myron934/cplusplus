/*
 * AsynServer.h
 *
 *  Created on: 2017年1月23日
 *      Author: myron
 */

#ifndef ASYNSERVER_H_
#define ASYNSERVER_H_
#include <boost/asio.hpp>
class AsynServer : private boost::noncopyable{
public:
	AsynServer();
	virtual ~AsynServer();
};

#endif /* ASYNSERVER_H_ */
