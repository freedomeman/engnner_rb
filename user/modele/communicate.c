
#include "modefine_control.h"
#include "main.h"
#include "usart.h"
#include "dma.h"


extern DMA_HandleTypeDef hdma_usart6_rx;


void communicate_init(void)
{
    modefine_control_init();
}

void communicate_run(void)
{


    
    
}


/*
usart6的中断处理函数，我们主要读取dma缓冲区的数据，并对数据进行解析
*/
 void USART6_IRQHandler(void)
    {
        if (huart6.Instance->SR & UART_FLAG_RXNE) //接收到数据
        {
            __HAL_UART_CLEAR_PEFLAG(&huart6);
        }
        else if (USART6->SR & UART_FLAG_IDLE)
        {
            static uint16_t this_time_rx_len = 0;

            __HAL_UART_CLEAR_PEFLAG(&huart6);

            if ((hdma_usart6_rx.Instance->CR & DMA_SxCR_CT) == RESET)
            {
                /* Current memory buffer used is Memory 0 */

                // disable DMA
                //失效DMA
                __HAL_DMA_DISABLE(&hdma_usart6_rx);

                // get receive data length, length = set_data_length - remain_length
                //获取接收数据长度,长度 = 设定长度 - 剩余长度
                this_time_rx_len = MC_RX_BUF_NUM - hdma_usart6_rx.Instance->NDTR;

                // reset set_data_lenght
                //重新设定数据长度
                hdma_usart6_rx.Instance->NDTR = MC_RX_BUF_NUM;

                // set memory buffer 1
                //设定缓冲区1
                hdma_usart6_rx.Instance->CR |= DMA_SxCR_CT;

                // enable DMA
                //使能DMA
                __HAL_DMA_ENABLE(&hdma_usart6_rx);

                if (this_time_rx_len == MC_FRAME_LENGTH)
                {
                    MC_unpack(0);
                    //记录数据接收时间
                    //detect_hook(DBUS_TOE);
                }
            }
            else
            {
                /* Current memory buffer used is Memory 1 */
                // disable DMA
                //失效DMA
                __HAL_DMA_DISABLE(&hdma_usart6_rx);

                // get receive data length, length = set_data_length - remain_length
                //获取接收数据长度,长度 = 设定长度 - 剩余长度
                this_time_rx_len = MC_RX_BUF_NUM - hdma_usart6_rx.Instance->NDTR;

                // reset set_data_lenght
                //重新设定数据长度
                hdma_usart6_rx.Instance->NDTR = MC_RX_BUF_NUM;

                // set memory buffer 0
                //设定缓冲区0
                DMA2_Stream1->CR &= ~(DMA_SxCR_CT);

                // enable DMA
                //使能DMA
                __HAL_DMA_ENABLE(&hdma_usart6_rx);

                if (this_time_rx_len == MC_FRAME_LENGTH)
                {
                    //处理自定义控制器数据
                    MC_unpack(1);
                    //记录数据接收时间
                    //detect_hook(DBUS_TOE);
                }
            }
        }
    }

