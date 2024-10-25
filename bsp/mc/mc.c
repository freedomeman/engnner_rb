#include "main.h" 
#include "mc.h"
#include "struct_typedef.h"

extern UART_HandleTypeDef huart6;
extern DMA_HandleTypeDef hdma_usart6_rx;


/*
返回值：无；
参数：rx1_buf 缓存区一 ， rx2_buf 缓存区2 ，dma_buf_num 缓存区长度
功能：配置usart6的dma通道
*/
void MC_init(uint8_t *rx1_buf, uint8_t *rx2_buf, uint16_t dma_buf_num)
{
     //enable the DMA transfer for the receiver request
    //使能DMA串口接收
    SET_BIT(huart6.Instance->CR3, USART_CR3_DMAR);

    //enalbe idle interrupt
    //使能空闲中断
    __HAL_UART_ENABLE_IT(&huart6, UART_IT_IDLE);

    //disable DMA
    //失效DMA
    __HAL_DMA_DISABLE(&hdma_usart6_rx);
    while(hdma_usart6_rx.Instance->CR & DMA_SxCR_EN)
    {
        __HAL_DMA_DISABLE(&hdma_usart6_rx);
    }

    hdma_usart6_rx.Instance->PAR = (uint32_t) & (USART6->DR);
    //memory buffer 1
    //内存缓冲区1
    hdma_usart6_rx.Instance->M0AR = (uint32_t)(rx1_buf);
    //memory buffer 2
    //内存缓冲区2
    hdma_usart6_rx.Instance->M1AR = (uint32_t)(rx2_buf);
    //data length
    //数据长度
    hdma_usart6_rx.Instance->NDTR = dma_buf_num;
    //enable double memory buffer
    //使能双缓冲区
    SET_BIT(hdma_usart6_rx.Instance->CR, DMA_SxCR_DBM);

    //enable DMA
    //使能DMA
    __HAL_DMA_ENABLE(&hdma_usart6_rx);
}


/*
功能：失能dma
*/
void MC_unable(void)
{
    __HAL_UART_DISABLE(&huart6);
}


/*
返回值：无
参数： dma_buf_num缓存区长度
功能： 重新开启dma
*/

void MC_restart(uint16_t dma_buf_num)
{
    __HAL_UART_DISABLE(&huart6);
    __HAL_DMA_DISABLE(&hdma_usart6_rx);

    hdma_usart6_rx.Instance->NDTR = dma_buf_num;

    __HAL_DMA_ENABLE(&hdma_usart6_rx);
    __HAL_UART_ENABLE(&huart6);

}
