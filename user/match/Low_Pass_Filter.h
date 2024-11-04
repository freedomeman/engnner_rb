#ifndef __LOW_PASS_FILTER
#define __LOW_PASS_FILTER



typedef struct 
{
    float alpha[3];
    float input[2];
    /* data */
}Low_Pass_Filter; 

void lowPassFilter_int(Low_Pass_Filter * lowPassFilter , float one , float two );

float lowPassFilter(Low_Pass_Filter * lowPassFilter , float in );

#endif
