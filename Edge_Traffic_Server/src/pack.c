#include "pack.h"
#include <string.h>
#include <arpa/inet.h> // 网络编程头文件,转换字节序
#include <endian.h>    //大小端转换

//发送网络字节序列
int message_send (Vehicle_Feature *p,uint8_t buf)
{
    
    int offset = 0;
    //转换网络字节序,机器语言->大端
    //int color_be = htobe64(p->car_color);
    //定长数组直接拷贝
    memcpy(buf + offset,p->car_color, COLOR_MAX_LEN);
    offset += COLOR_MAX_LEN;

    memcpy(buf + offset, p->car_id,ID_MAX_LEN);
    offset += ID_MAX_LEN;

    memcpy(buf + offset, p->car_brand,BRAND_MAX_LEN);
    offset += BRAND_MAX_LEN;

    return offset;
    
}

//接收网络字节序列
int message_receive (Vehicle_Feature *p,uint8_t buf)
{

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

