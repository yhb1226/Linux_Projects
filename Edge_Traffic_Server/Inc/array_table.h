#ifndef __ARRAY_TABLE_H
#define __ARRAY_TABLE_H

#include "car_record.h"

#define MAX_CAR       1000
#define COLOR_MAX_LEN 20


typedef struct {
    char car_color[COLOR_MAX_LEN];
    char car_id[ID_MAX_LEN];
    char car_brand[BRAND_MAX_LEN];
} array_table_t;

// 全局变量（在 .c 中定义）
extern array_table_t packing_car[MAX_CAR];
extern int count_car;

// 函数声明
int add_car(const char *id, const char *brand, const char *color);
array_table_t *find_car(const char *id);

#endif