#include "pid.h"


/*
初始化pid参数
pid结构体的地址，角度：电机编码器角度或陀螺仪角度 ， 模式：0，速度；1，位置 速度，角度环：电机的转速或陀螺仪的角速度，速度环：电机转速 
最大输入 ， 最大积分输出 ， 最大输出
*/
void pid_int(PID * pid , float * angle , float * angle_last ,uint8_t mode , 
             float * speed ,float * speed_last
            , float max_iout , float max_out )
{

    pid = 0;

    pid->angle = angle;
    pid->angle_last = angle_last;
    pid->pid_mode = mode;
    pid->speed = speed;
    pid->speed_last = speed_last;
    pid->max_iout = max_iout;
    pid->max_out = max_out;

}




float pid_calc(PID * pid)
{

    

    pid->error_last = pid->error;
    if (pid->pid_mode == PID_MODE_ANGLE)
    {
        pid->error = *pid->angle - *pid->angle_last;
        pid->differential = *pid->speed;
        /* code */
    }
    else
    {
        pid->error = *pid->speed - *pid->speed_last;
        pid->differential = pid->error - pid->error_last;
    }

    pid->i_out = pid->ki*pid->points;

    if (pid->i_out > pid->max_iout)
    {
        pid->i_out = pid->max_iout;
        /* code */
    }
    if (pid->i_out < -pid->max_iout)
    {
        pid->i_out = -pid->max_iout;
        /* code */
    }

    pid->pid_out = pid->kp*pid->error + pid->kd*pid->differential + pid->i_out;

    if (pid->pid_out > pid->max_out)
    {
        pid->pid_out = pid->max_out;
        /* code */
    }
    if (pid->pid_out < -pid->max_out)
    {
        pid->pid_out = -pid->max_out;
        /* code */
    }
    
    return pid->pid_out;

    
}