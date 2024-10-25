#ifndef  CAN_RECEIVE_H
#define  CAN_RECEIVE_H

#include "cmsis_os.h"
#include "can.h"
#include "main.h"
#include "bsp_can.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

#define can1 hcan1
#define can2 hcan2




typedef enum
{
    //CAN1
    //GM3508id
    upthrow_L = 0x201,//抬升电机id
    upthrow_R = 0x202,

    stick_out_L = 0x203,//伸出电机id
    stick_out_R = 0x204,

    upthrow_stick_ctrl = 0x200,//控制id

    //CAN2
    //GM2006
    joint4 = 0x201,
    joint5 = 0x202,

    joint_GM2006_ctrl = 0x200, //控制id

    //DM4310
    joint3 = 0x03,
    joint2 = 0x04,
    joint1 = 0x05,
} can_msg_id_e;


typedef struct 
{
  uint16_t ecd; // 读出的编码器角度
  int16_t speed_rpm; // 读出的当前转速
  int16_t given_current; // 给的电流值
  uint8_t temperate; // 读出的温度
  int16_t last_ecd; // 上一次的编码器值
    /* data */
}GM_motor_message;


//达妙电机
//mit模式
#define P_MAX 0
#define V_MAX 0
#define T_MAX 0
#define KP_MAX 0
#define KD_MAX 0

#define P_MIN 0
#define V_MIN 0
#define T_MIN 0
#define KP_MIN 0
#define KD_MIN 0

// 电机回传信息结构体
typedef struct 
{
	int id;
	int state;
	int p_int;
	int v_int;
	int t_int;
	int kp_int;
	int kd_int;
	float pos;
	float vel;
	float tor;
	float Kp;
	float Kd;
	float Tmos;
	float Tcoil;
}DM_motor_fbpara_t;

// 电机参数设置结构体
typedef struct 
{
    uint16_t motor_id;
	int8_t mode;
    uint16_t pos_tmp;
    uint16_t kp_tmp;
    uint16_t tor_tmp;
    uint16_t vel_tmp;
    uint16_t kd_tmp;
	float pos_set;
	float vel_set;
	float tor_set;
	float kp_set;
	float kd_set;
}DM_motor_ctrl_t;


typedef struct Can_receive
{


    GM_motor_message GM3508_message[3];
    GM_motor_message GM2006_message[2];
    DM_motor_fbpara_t DM4310_message[3];

    CAN_TxHeaderTypeDef can_tx_message;

    DM_motor_ctrl_t DM4310_send_struct[3];
    uint8_t can_send_data[8];


}Can_receive;



void get_upthrow_stick_motor_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive);

void get_arm_GM2006_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive);

void get_amr_DM4310_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive);

void can_cmd_upthrow_stick_motor(int16_t upthrow_L, int16_t upthrow_R, int16_t stick_out_L ,int16_t stick_out_R , Can_receive * can_receive);

void can_cmd_arm_GM2006_motor(int16_t joint4_ms, int16_t joint5_ms,  Can_receive * can_receive);

void can_cmd_joint_DM4310_motor(Can_receive * can_receive , uint8_t num);

const GM_motor_message * get_upthrow_stick_measure_point(uint8_t num , Can_receive *  can_receive);

const GM_motor_message *get_arm_GM2006_measure_point(uint8_t num , Can_receive * can_receive);

const DM_motor_fbpara_t *get_joint_DM4310_measure_point(uint8_t num , Can_receive * can_receive);



#endif

