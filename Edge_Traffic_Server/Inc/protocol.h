#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#define  NUMBER_MAGIC       0X20041226
#define  NUMBER_VERSION     1

#include "car_record.h"
#include "pack.h" 

enum message_type{
    MESSAGE_SEND = 0X01,    //数据发送
    MESSAGE_RECEIVE = 0X02, //数据接收
    MESSAGE_ERROR = 0X03,   //数据出错
    MESSAGE_YES = 0XFF      //数据确认
};


typedef struct {
    uint32_t magic;         //魔数
    uint8_t  version;
    uint8_t  msg_type;      //消息类型
    uint16_t flags;
    uint32_t payload_len;   // 载荷长度（不含头）
} __attribute__((packed)) message_header_t;


//信息上报的载荷结构体
typedef struct 
{
    char car_color[COLOR_MAX_LEN];  //颜色
    char car_id[ID_MAX_LEN];        //车牌
    char car_brand[BRAND_MAX_LEN];  //品牌

}Vehicle_Feature_Payload;


#endif