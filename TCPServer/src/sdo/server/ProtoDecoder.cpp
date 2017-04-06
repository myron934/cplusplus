/*
 * ProtoDecoder.cpp
 *
 *  Created on: 2017年4月5日
 *      Author: weiminglun.myron
 */

#include <sdo/server/ProtoDecoder.h>

namespace sdo {
namespace server {
ProtoDecoder::ProtoDecoder(const char* data, const int data_len) {
    if(header_.ParseFromArray(data,data_len)){
        header_len_=header_.ByteSize();
    }
    else{
        header_len_=0;
    }
}

ProtoDecoder::~ProtoDecoder() {
}

int ProtoDecoder::load(const char* data, int data_len) {
    if(header_.ParseFromArray(data,data_len)){
        header_len_=header_.ByteSize();
        return 0;
    }
    header_len_=0;
    return -1;
}

/**
 * 清除数据
 */
void ProtoDecoder::clear() {
    header_.Clear();
}

} /* namespace server */
} /* namespace sdo */
