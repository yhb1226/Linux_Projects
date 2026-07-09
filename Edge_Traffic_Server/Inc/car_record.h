#ifndef __CAR_RECORD_H
#define __CAR_RECORD_H

#include <stdint.h>

#define COLOR_MAX_LEN   20
#define ID_MAX_LEN      32     
#define BRAND_MAX_LEN   32

typedef struct 
{
    char car_color[COLOR_MAX_LEN];  //颜色
    char car_id[ID_MAX_LEN];        //车牌
    char car_brand[BRAND_MAX_LEN];  //品牌

}Vehicle_Feature;


#endif