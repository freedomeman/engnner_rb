

#include "Low_Pass_Filter.h"


void lowPassFilter_int(Low_Pass_Filter * lowPassFilter , float one , float two )
{
    lowPassFilter->alpha[0] = one;
    lowPassFilter->alpha[1] = two;
    lowPassFilter->alpha[2] = 1-one-two;
}



float lowPassFilter(Low_Pass_Filter * lowPassFilter , float in )
{

    lowPassFilter->input[0] = lowPassFilter->input[1];
    lowPassFilter->input[1] = in;
    return in*lowPassFilter->alpha[0] + lowPassFilter->input[0]*lowPassFilter->alpha[1] + lowPassFilter->input[1]*lowPassFilter->alpha[2];
}