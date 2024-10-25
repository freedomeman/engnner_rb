#include "DM_config.h"

extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;



uint8_t Data_Enable[8]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC};		//电机使能命令
uint8_t Data_Failure[8]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD};		//电机失能命令
uint8_t Data_Save_zero[8]={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE};	//电机保存零点命令

void DM_Enable(uint8_t DM_id )
{
    uint32_t send_mail_box;
    static CAN_TxHeaderTypeDef   Tx_Header;
    Tx_Header.StdId=DM_id;
	Tx_Header.ExtId=0;
	Tx_Header.IDE=0;
	Tx_Header.RTR=0;
	Tx_Header.DLC=0x08;

     HAL_CAN_AddTxMessage(&can2, &Tx_Header, Data_Enable, &send_mail_box);
}

void DM_Failure(uint8_t DM_id )
{
    uint32_t send_mail_box;
    static CAN_TxHeaderTypeDef   Tx_Header;
    Tx_Header.StdId=DM_id;
	Tx_Header.ExtId=0;
	Tx_Header.IDE=0;
	Tx_Header.RTR=0;
	Tx_Header.DLC=0x08;

     HAL_CAN_AddTxMessage(&can2, &Tx_Header, Data_Failure, &send_mail_box);
}

void DM_Save_zero(uint8_t DM_id )
{
    uint32_t send_mail_box;
    static CAN_TxHeaderTypeDef   Tx_Header;
    Tx_Header.StdId=DM_id;
	Tx_Header.ExtId=0;
	Tx_Header.IDE=0;
	Tx_Header.RTR=0;
	Tx_Header.DLC=0x08;

     HAL_CAN_AddTxMessage(&can2, &Tx_Header, Data_Save_zero, &send_mail_box);
}

