#ifndef  __MODEFINE_CONTROL_H
#define  __MODEFINE_CONTROL_H

#include "struct_typedef.h"


#define MC_RX_BUF_NUM        40

#define MC_FRAME_LENGTH      30

typedef struct 
{
    int16_t joint[6];




} MC_t;


void modefine_control_init(void);
const MC_t *get_modefine_control_point(void);

const MC_t *get_modefine_control_last_point(void);


void MC_unpack(uint8_t num);




#endif
