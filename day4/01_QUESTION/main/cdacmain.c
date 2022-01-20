#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandleTaskLog_1;
TaskHandle_t xHandleTaskLog_2;

void task_1(void *pvparameters)
{
    while(1)
    {
        printf("TASK 1 RUNNING\n");
       // vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void task_2(void *pvparameters)
{
    while(1)
    {
        printf("TASK 2 RUNNING\n");
       // vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}
void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(task_1,"task_1",1024,NULL,5,&xHandleTaskLog_1);

    if(result==pdPASS)
    {
        printf("task_1 created\n");
    }
    result=xTaskCreate(task_2,"task_2",1024,NULL,3,&xHandleTaskLog_2);

    if(result==pdPASS)
    {
        printf("task_2 created\n");
    }
    
}