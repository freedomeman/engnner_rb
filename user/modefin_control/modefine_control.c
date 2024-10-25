#include "mc.h"
#include "struct_typedef.h"
#include "modefine_control.h"
#include "string.h"




uint8_t mc_data[2][MC_RX_BUF_NUM];

MC_t mc;
MC_t mc_last;

/*
初始化自定义控制器的接收
*/
void modefine_control_init(void)
{
    MC_init(mc_data[0] , mc_data[1] , MC_RX_BUF_NUM);
}

/*
获取自定义控制器的原生数据指针
*/
const MC_t *get_modefine_control_point(void)
{
    return &mc;
}


/*
获取上一次自定义控制器的原生数据指针
*/
const MC_t *get_modefine_control_last_point(void)
{
    return &mc_last;
}


/*
返回值：无
参数：num使用的缓存区数组的编号
功能：解析自定义控制器的数据
*/
void MC_unpack(uint8_t num)
{
    if (mc_data[num] == NULL)
    {
        return;
    }
    mc_last = mc;
    mc.joint[0] = (mc_data[num][0]<<8 | mc_data[num][1]);
    mc.joint[1] = (mc_data[num][2]<<8 | mc_data[num][3]);
    mc.joint[2] = (mc_data[num][4]<<8 | mc_data[num][5]);
    mc.joint[3] = (mc_data[num][6]<<8 | mc_data[num][7]);
    mc.joint[4] = (mc_data[num][8]<<8 | mc_data[num][9]);
    mc.joint[5] = (mc_data[num][10]<<8 | mc_data[num][11]);
    


}

