#ifndef __PACK_H
#define __PACK_H

#include "car_record.h"
#include "protocol.h"

int message_send (Vehicle_Feature_Payload *p, uint8_t *buf, int max_len);
int message_receive (Vehicle_Feature_Payload *p, uint8_t *buf, int buf_len);
int message_head (int max_len, uint8_t message_type, uint8_t *payload, uint8_t *out_buf,int payload_len);



#endif
