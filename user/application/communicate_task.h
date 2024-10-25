#ifndef COMMUNICATE_TASK_H
#define COMMUNICATE_TASK_H


#include "struct_typedef.h"
#include "cmsis_os.h"
#include "main.h"


#define COMMUNICATE_TASK_INIT_TIME 30

#define COMMUNICATE_CONTROL_TIME_MS 2

void communicate_task(void const *pvParameters);


#endif
