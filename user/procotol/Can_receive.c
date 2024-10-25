#include "Can_receive.h"
#include "uint_switch_float.h"

/*
初始化can外设
*/
void Can_receive_init(void)
{
    can_filter_init();

}

/*
获取抬升和前伸电机的参数
*/
void get_upthrow_stick_motor_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive)
{
    can_receive->GM3508_message[num].last_ecd = can_receive->GM3508_message[num].ecd;
    can_receive->GM3508_message[num].ecd = (uint16_t)(data[0] << 8 | data[1]);
    can_receive->GM3508_message[num].speed_rpm = (uint16_t)(data[2] << 8 | data[3]);
    can_receive->GM3508_message[num].given_current = (uint16_t)(data[4] << 8 | data[5]);
    can_receive->GM3508_message[num].temperate = data[6];
}

/*
获取机械臂上2006电机的参数
*/
void get_arm_GM2006_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive)
{
    can_receive->GM2006_message[num].last_ecd = can_receive->GM2006_message[num].ecd;
    can_receive->GM2006_message[num].ecd = (uint16_t)(data[0] << 8 | data[1]);
    can_receive->GM2006_message[num].speed_rpm = (uint16_t)(data[2] << 8 | data[3]);
    can_receive->GM2006_message[num].given_current = (uint16_t)(data[4] << 8 | data[5]);
    can_receive->GM2006_message[num].temperate = data[6];
}

/*
获取机械臂上DM410电机的参数
*/
void get_amr_DM4310_measure(uint8_t num, uint8_t data[8] , Can_receive * can_receive)
{

	can_receive->DM4310_message[num].id = (data[0])&0x0F;
	can_receive->DM4310_message[num].state = (data[0])>>4;
	can_receive->DM4310_message[num].p_int=(data[1]<<8)|data[2];
	can_receive->DM4310_message[num].v_int=(data[3]<<4)|(data[4]>>4);
	can_receive->DM4310_message[num].t_int=((data[4]&0xF)<<8)|data[5];
	can_receive->DM4310_message[num].pos = uint_to_float(can_receive->DM4310_message[num].p_int, P_MIN, P_MAX, 16); // (-12.5,12.5)
	can_receive->DM4310_message[num].vel = uint_to_float(can_receive->DM4310_message[num].v_int, V_MIN, V_MAX, 12); // (-45.0,45.0)
	can_receive->DM4310_message[num].tor = uint_to_float(can_receive->DM4310_message[num].t_int, T_MIN, T_MAX, 12);  // (-18.0,18.0)
	can_receive->DM4310_message[num].Tmos = (float)(data[6]);
	can_receive->DM4310_message[num].Tcoil = (float)(data[7]);
}

/*
向抬升和前伸电机发送数据
参数 ：upthrow_L 抬升左； upthrow_R 抬升右 ； stick_out_L 前伸左 ； stick_out_R 前伸右 ； can_receive 全局变量指针
*/
void can_cmd_upthrow_stick_motor(int16_t upthrow_L, int16_t upthrow_R, int16_t stick_out_L ,int16_t stick_out_R , Can_receive * can_receive)
{
    uint32_t send_mail_box;
    can_receive->can_tx_message.StdId = upthrow_stick_ctrl;
    can_receive->can_tx_message.IDE = CAN_ID_STD;
    can_receive->can_tx_message.RTR = CAN_RTR_DATA;
    can_receive->can_tx_message.DLC = 0x08;
    can_receive->can_send_data[0] = upthrow_L >>8;
    can_receive->can_send_data[1] = upthrow_L;
    can_receive->can_send_data[2] = upthrow_R >> 8;
    can_receive->can_send_data[3] = upthrow_R;
    can_receive->can_send_data[4] = stick_out_L >> 8;
    can_receive->can_send_data[5] = stick_out_L;
    can_receive->can_send_data[6] = stick_out_R >> 8 ;
    can_receive->can_send_data[7] = stick_out_R;

    HAL_CAN_AddTxMessage(&can2, &can_receive->can_tx_message, can_receive->can_send_data, &send_mail_box);
}

/*
向机械臂上2006电机发送数据
参数： joint4_ms 关节4 ； joint5_ms 关节6 ； 全局变量指针 can_receive
*/
void can_cmd_arm_GM2006_motor(int16_t joint4_ms, int16_t joint5_ms,  Can_receive * can_receive)
{
    uint32_t send_mail_box;
    can_receive->can_tx_message.StdId = joint_GM2006_ctrl;
    can_receive->can_tx_message.IDE = CAN_ID_STD;
    can_receive->can_tx_message.RTR = CAN_RTR_DATA;
    can_receive->can_tx_message.DLC = 0x08;
    can_receive->can_send_data[0] = joint4_ms >>8;
    can_receive->can_send_data[1] = joint4_ms;
    can_receive->can_send_data[2] = joint5_ms >> 8;
    can_receive->can_send_data[3] = joint5_ms;
    can_receive->can_send_data[4] = 0;
    can_receive->can_send_data[5] = 0;
    can_receive->can_send_data[6] = 0;
    can_receive->can_send_data[7] = 0;

    HAL_CAN_AddTxMessage(&can1, &can_receive->can_tx_message, can_receive->can_send_data, &send_mail_box);
}

/*
向机械臂上DM4310电机发送数据
参数； 全局变量指针 can_receive , 第几关节 num（0对joint1 , 1对joint2 , 2对joint3）
*/
void can_cmd_joint_DM4310_motor(Can_receive * can_receive , uint8_t num)
{
	
	uint16_t id = can_receive->DM4310_send_struct[num].motor_id +can_receive->DM4310_send_struct[num].mode;
    uint32_t send_mail_box;
    can_receive->can_tx_message.StdId = id;
    can_receive->can_tx_message.IDE = CAN_ID_STD;
    can_receive->can_tx_message.RTR = CAN_RTR_DATA;
    can_receive->can_tx_message.DLC = 0x08;


	can_receive->DM4310_send_struct[num].pos_tmp = float_to_uint(can_receive->DM4310_send_struct[num].pos_set,  P_MIN,  P_MAX,  16);
	can_receive->DM4310_send_struct[num].vel_tmp = float_to_uint(can_receive->DM4310_send_struct[num].vel_set,  V_MIN,  V_MAX,  12);
	can_receive->DM4310_send_struct[num].kp_tmp  = float_to_uint(can_receive->DM4310_send_struct[num].kp_set,   KP_MIN, KP_MAX, 12);
	can_receive->DM4310_send_struct[num].kd_tmp  = float_to_uint(can_receive->DM4310_send_struct[num].kd_set,   KD_MIN, KD_MAX, 12);
	can_receive->DM4310_send_struct[num].tor_tmp = float_to_uint(can_receive->DM4310_send_struct[num].tor_set, T_MIN,  T_MAX,  12);

	can_receive->can_send_data[0] = (can_receive->DM4310_send_struct[num].pos_tmp >> 8);
	can_receive->can_send_data[1] = can_receive->DM4310_send_struct[num].pos_tmp;
	can_receive->can_send_data[2] = (can_receive->DM4310_send_struct[num].vel_tmp >> 4);
	can_receive->can_send_data[3] = ((can_receive->DM4310_send_struct[num].vel_tmp&0xF)<<4)|(can_receive->DM4310_send_struct[num].kp_tmp>>8);
	can_receive->can_send_data[4] = can_receive->DM4310_send_struct[num].kp_tmp;
	can_receive->can_send_data[5] = (can_receive->DM4310_send_struct[num].kd_tmp >> 4);
	can_receive->can_send_data[6] = ((can_receive->DM4310_send_struct[num].kd_tmp&0xF)<<4)|(can_receive->DM4310_send_struct[num].tor_tmp>>8);
	can_receive->can_send_data[7] = can_receive->DM4310_send_struct[num].tor_tmp;
	
	HAL_CAN_AddTxMessage(&can1, &can_receive->can_tx_message, can_receive->can_send_data, &send_mail_box);
}

/*
获取抬升和前伸电机的数据地址
*/
const GM_motor_message * get_upthrow_stick_measure_point(uint8_t num , Can_receive *  can_receive)
{
    return &  can_receive->GM3508_message[num];
}

/*
获取机械臂部分2006电机的数据地址
*/
const GM_motor_message *get_arm_GM2006_measure_point(uint8_t num , Can_receive * can_receive)
{
    return & can_receive->GM2006_message[num];
}

/*
获取机械臂部分4310电机的数据地址
*/
const DM_motor_fbpara_t *get_joint_DM4310_measure_point(uint8_t num , Can_receive * can_receive)
{
    return & can_receive->DM4310_message[num];
}





