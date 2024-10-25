#ifndef __MC_H
#define __MC_H

#include "struct_typedef.h"

extern void MC_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num);
extern void MC_unable(void);
extern void MC_restart(uint16_t dma_buf_num);


#endif

