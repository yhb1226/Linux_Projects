#include "array_table.h"
#include <string.h>

// 全局变量定义
array_table_t packing_car[MAX_CAR];
int count_car = 0;

int add_car(const char *id, const char *brand, const char *color) {
    if (count_car >= MAX_CAR) {
        return -1;
    }

    strncpy(packing_car[count_car].car_id,    id,    ID_MAX_LEN - 1);
    strncpy(packing_car[count_car].car_brand, brand, BRAND_MAX_LEN - 1);
    strncpy(packing_car[count_car].car_color, color, COLOR_MAX_LEN - 1);

    // 确保字符串结尾
    packing_car[count_car].car_id[ID_MAX_LEN - 1]       = '\0';
    packing_car[count_car].car_brand[BRAND_MAX_LEN - 1] = '\0';
    packing_car[count_car].car_color[COLOR_MAX_LEN - 1] = '\0';

    count_car++;
    return 0;
}

//返回结构体中变量指针地址的形式更加有利于直接拿到返回的地址信息，然后在别处直接使用拿到返回的地址信息把对应的数据给取出来
array_table_t *find_car(const char *id) {
    for (int i = 0; i < count_car; i++) {
        if (strcmp(packing_car[i].car_id, id) == 0) {
            return &packing_car[i];
        }
    }
    return NULL;
}