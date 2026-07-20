#include "array_table.h"

int count_car = 0;

array_table_t packing_car[MAX_CAR]; //最多能统计的汽车数的总上限

int add_car (const char *color, const char *id, const char *brand)
{
    if(count_car > MAX_CAR) {return -1;}
    

    strncpy(packing_car[count_car].car_color, color, COLOR_MAX_LEN - 1);
    strncpy(packing_car[count_car].car_id, id, ID_MAX_LEN - 1);
    strncpy(packing_car[count_car].car_brand, brand, BRAND_MAX_LEN-1);

    count_car++;

    return 0;

}