#include "pack.h"
#include "protocol.h"
#include <string.h>
#include <arpa/inet.h> // 网络编程头文件,转换字节序
#include <endian.h>    //大小端转换

//发送网络字节序列
int message_send (Vehicle_Feature_Payload *p, uint8_t *buf, int max_len)
{
    int total_len = COLOR_MAX_LEN + ID_MAX_LEN + BRAND_MAX_LEN;
    if(total_len < max_len)
    return -1;

    int offset = 0;
    //转换网络字节序,机器语言->大端
    //int color_be = htobe64(p->car_color);
    //定长数组直接拷贝
    memcpy(buf + offset,p->car_color, COLOR_MAX_LEN);//此处car_color等三个都已经是数组了
    offset += COLOR_MAX_LEN;

    memcpy(buf + offset, p->car_id,ID_MAX_LEN);
    offset += ID_MAX_LEN;

    memcpy(buf + offset, p->car_brand,BRAND_MAX_LEN);
    offset += BRAND_MAX_LEN;

    return offset;
    
}

//接收网络字节序列
int message_receive (Vehicle_Feature *p, uint8_t buf, int max_len)
{
    int total_len = COLOR_MAX_LEN + ID_MAX_LEN + BRAND_MAX_LEN;;
    if(max_len < total_len)
    return -1;

    int offset = 0;

    memcpy(p->car_color, buf + offset, COLOR_MAX_LEN);
    p->car_color[COLOR_MAX_LEN - 1] = '\0'; // 确保结束符
    offset += COLOR_MAX_LEN;

    memcpy(p->car_id, buf + offset, ID_MAX_LEN);
    p->car_id[ID_MAX_LEN - 1] = '\0'; // 确保结束符
    offset += ID_MAX_LEN;

    memcpy(p->car_brand, buf + offset, BRAND_MAX_LEN);
    offset += BRAND_MAX_LEN;
    p->car_brand[BRAND_MAX_LEN] = '\0'; // 确保结束符


    return offset;

}

//发送数据包头
int message_head (int max_len, uint8_t message_type, uint8_t *payload, uint8_t *out_buf,int payload_len)
{
    int total_len = payload_len + sizeof(message_header_t);
    if(max_len < total_len)
    return -1;

    message_header_t hdr;
    hdr.flags = 0;                      //标志位
    hdr.magic = htonl(NUMBER_MAGIC);   //魔数，htonl()将魔数转变为大端序
    hdr.msg_type = message_type;       //规定发送数据类型
    hdr.payload_len = htonl(payload_len);
    hdr.version = NUMBER_VERSION;

    memcpy(out_buf, &hdr, sizeof(hdr));
    memcpy(out_buf + sizeof(hdr), payload, payload_len);

    return total_len;

}


