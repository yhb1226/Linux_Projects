#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include "pack.h" 


typedef struct {
    uint32_t magic;         //魔数
    uint8_t  version;
    uint8_t  msg_type;      //消息类型
    uint16_t flags;
    uint32_t payload_len;   // 载荷长度（不含头）
} __attribute__((packed)) message_header_t;



#endif