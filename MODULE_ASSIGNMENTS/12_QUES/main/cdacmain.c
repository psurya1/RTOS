#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>


TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;



void Alarmtask_1(void *pvparameters)
{
    int count=0;
    while(1)
    {
       
        printf("ALARM TASK  RUNNING\n");
        taskENTER_CRITICAL(NULL);
        count++;
        printf("I am in critical section\n");
        if(count==2)
        {
            taskEXIT_CRITICAL(NULL);
        }
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    BaseType_t result;
    
    
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}