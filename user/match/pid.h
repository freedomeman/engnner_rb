#ifndef __PID_H
#define __PID_H


#include "struct_typedef.h"


#define PID_MODE_SPEED  0
#define PID_MODE_ANGLE  1


typedef struct PID
{
    float kp;
    float ki;
    float kd;

    uint8_t pid_mode;

    float max_out;
    float max_iout;
    float max_in;

    float pid_in;
    float pid_out;

    float error;
    float error_last;
    float points;
    float differential;
    float i_out;

    float * speed;
    float * angle;
    float * speed_last;
    float * angle_last;
}PID;
    
    /* data */


void pid_int(PID * pid , float * angle , float * angle_last ,uint8_t mode , 
             float * speed ,float * speed_last
            , float max_iout , float max_out );


float pid_calc(PID * pid);


#endif

