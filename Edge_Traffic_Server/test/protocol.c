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
    


    return 0;
}
