#include "communicate_task.h"
#include "communicate.h"



void communicate_task(void const *pvParameters)
{
  vTaskDelay(COMMUNICATE_TASK_INIT_TIME);

  communicate_init();

  while (1)
  {
    communicate_run();

    vTaskDelay(COMMUNICATE_CONTROL_TIME_MS);
  }
}
