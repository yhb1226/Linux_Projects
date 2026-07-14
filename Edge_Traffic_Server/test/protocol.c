#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pack.h"
#include <arpa/inet.h>

int main()
{
    Vehicle_Feature_Payload orig;
    strcpy(orig.car_brand,"奔驰");
    strcpy(orig.car_color,"黑色");
    strcpy(orig.car_id,"京A.99999");

    uint8_t buf[256];

    //收发消息测试
    int len = message_send(&orig, buf, sizeof(buf));
    assert(len > 0);

    Vehicle_Feature_Payload restore;
    memset(&restore, 0, sizeof(restore));
    int ret = message_receive(&restore, buf, sizeof(buf));
    assert(ret == len);
    assert(strcmp(orig.car_brand, restore.car_brand) == 0);
    assert(strcmp(orig.car_color, restore.car_color) == 0);
    assert(strcmp(orig.car_id,restore.car_id) == 0);
    printf("Test1 passed: pack/unpack consistency\n");

    //完整消息组装
    uint8_t message_buf[512];
    int ret_out = pack_message(sizeof(message_buf), MESSAGE_SEND, buf, message_buf, len);
    assert(ret_out > 0);
    assert((size_t)ret_out == sizeof(message_header_t) + len);
    message_header_t*hdr = (message_header_t*)message_buf;//声明测试包头信息的结构体指针，指向的是message_buf包头中的数据
    assert(ntohl(hdr->magic) == NUMBER_MAGIC);
    assert(hdr->version == NUMBER_VERSION);
    assert(hdr->msg_type == MESSAGE_SEND);
    assert(hdr->flags == 0);
    assert(ntohl(hdr->payload_len) == (uint32_t)len);
    printf("包头+有效载荷消息测试成功\n");

    //缓冲区是否合适测试
    uint8_t error_buf[5];
    assert(message_send(&orig, error_buf, sizeof(error_buf)) == -1);
    assert(message_receive(&restore, buf, 10) == -1);
    printf("边界测试成功\n");


    return 0;
}
