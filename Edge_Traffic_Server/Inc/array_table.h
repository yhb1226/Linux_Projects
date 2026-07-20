#ifndef __ARRAY_TABLE_H
#define __ARRAY_TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR       1000
#define COLOR_MAX_LEN 20
#define ID_MAX_LEN    30
#define BRAND_MAX_LEN 20


typedef struct array_table{
    
    char car_color[COLOR_MAX_LEN];  //颜色
    char car_id[ID_MAX_LEN];        //车牌
    char car_brand[BRAND_MAX_LEN];  //品牌

}array_table_t;



#endif

