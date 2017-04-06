/*
 * ProtoDecoder.h
 *
 *  Created on: 2017年4月5日
 *      Author: weiminglun.myron
 */

#ifndef SDO_SERVER_PROTODECODER_H_
#define SDO_SERVER_PROTODECODER_H_
#include <sdo/protobuf/header.pb.h>
namespace sdo {
namespace server {
class ProtoDecoder {
public:
    ProtoDecoder():header_len_(0){};
    ProtoDecoder(const char* data, int data_len);
    virtual ~ProtoDecoder();
    int load(const char* data, int data_len);
    void clear();
    const sdo::protobuf::header& getHeader() const{
        return header_;
    }
    int getHeaderLen() const{
        return header_len_;
    }

    sdo::protobuf::header header_;
    int header_len_;
};

} /* namespace server */
} /* namespace sdo */

#endif /* SDO_SERVER_PROTODECODER_H_ */
