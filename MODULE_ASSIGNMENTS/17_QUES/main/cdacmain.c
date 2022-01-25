#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>

//when other task are not running the idle task will run...

volatile uint32_t ulIdleCycleCount = 0;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;

void sensortask_1(void *pvparameters)
{
    while(1)
    {
        printf("SENSOR TASK  RUNNING \n");
        printf("SPARE TIME :%ld\n",ulIdleCycleCount);
        vTaskDelay(250/ portTICK_PERIOD_MS);
        
    }
}
void Alarmtask_1(void *pvparameters)
{ 
    while(1)
    {
        printf("ALARM TASK RUNNING \n");
        printf("SPARE TIME :%ld\n",ulIdleCycleCount);
        vTaskDelay(250/ portTICK_PERIOD_MS);
        
    }
}
void idletask(void *pv)                                              //idle task
{
    ulIdleCycleCount++;
}
void app_main()
{
    BaseType_t result;
    
    
    result=xTaskCreate(sensortask_1,"sensortask_1",2048,NULL,15,&xHandle_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    result=xTaskCreate(idletask,"idletask",2048,NULL,0,NULL);
    
}