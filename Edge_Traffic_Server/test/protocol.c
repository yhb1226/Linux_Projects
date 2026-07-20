#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "pack.h"
#include "array_table.h"
#include <arpa/inet.h>

int main()
{
    // ----- 第一辆车 -----
    Vehicle_Feature_Payload orig1;
    strcpy(orig1.car_brand, "奔驰");
    strcpy(orig1.car_color, "黑色");
    strcpy(orig1.car_id, "京A.99999");

    uint8_t buf1[256];
    int len1 = message_send(&orig1, buf1, sizeof(buf1));
    assert(len1 > 0);

    Vehicle_Feature_Payload restored1;
    memset(&restored1, 0, sizeof(restored1));
    int ret1 = message_receive(&restored1, buf1, len1);
    assert(ret1 == len1);

    int add_ret1 = add_car(restored1.car_id, restored1.car_brand, restored1.car_color);
    assert(add_ret1 == 0);

    // ----- 第二辆车 -----
    Vehicle_Feature_Payload orig2;
    strcpy(orig2.car_brand, "奥迪");
    strcpy(orig2.car_color, "白色");
    strcpy(orig2.car_id, "沪B.67890");

    uint8_t buf2[256];
    int len2 = message_send(&orig2, buf2, sizeof(buf2));
    assert(len2 > 0);

    Vehicle_Feature_Payload restored2;
    memset(&restored2, 0, sizeof(restored2));
    int ret2 = message_receive(&restored2, buf2, len2);
    assert(ret2 == len2);

    int add_ret2 = add_car(restored2.car_id, restored2.car_brand, restored2.car_color);
    assert(add_ret2 == 0);

    // ----- 第三辆车 -----
    Vehicle_Feature_Payload orig3;
    strcpy(orig3.car_brand, "保时捷");
    strcpy(orig3.car_color, "红色");
    strcpy(orig3.car_id, "鄂A42673");

    uint8_t buf3[256];
    int len3 = message_send(&orig3, buf3, sizeof(buf3));
    assert(len3 > 0);

    Vehicle_Feature_Payload restored3;
    memset(&restored3, 0, sizeof(restored3));
    int ret3 = message_receive(&restored3, buf3, len3);
    assert(ret3 == len3);

    int add_ret3 = add_car(restored3.car_id, restored3.car_brand, restored3.car_color);
    assert(add_ret3 == 0);


    array_table_t *found = find_car("沪B.67890");
    if (found != NULL) {
        printf("找到：%s %s\n", found->car_brand, found->car_color);
    }








    /*
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

    */
    

    return 0;
}
