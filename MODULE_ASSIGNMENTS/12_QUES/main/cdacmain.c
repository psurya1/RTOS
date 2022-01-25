#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>

EventGroupHandle_t sensor;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;

const uint32_t first_bit=(1<<0);
const uint32_t all_bit=first_bit;

void Alarmtask_1(void *pvparameters)
{
    uint32_t result;
    
       
    printf("ALARM TASK  RUNNING\n");
    taskENTER_CRITICAL();
    {
        printf("I am in critical section\n");
        result = xEventGroupWaitBits(sensor,all_bit,pdTRUE,pdTRUE,pdMS_TO_TICKS(5000));
        printf("BIT OUT%d\n",result);
    }
    taskEXIT_CRITICAL();
    //vTaskDelay(1000/ portTICK_PERIOD_MS);
    

    
}
void Delaytask_1(void *pv)
{
    int count =0;
    while(1)
    {
        count++;
        printf("DALEY TASK RUNNING\n");
        if(count==3)
        {
            xEventGroupSetBits(sensor,first_bit);
        } 
    }
}
void app_main()
{
    sensor =xEventGroupCreate();
    BaseType_t result;
    
    
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_1);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    result=xTaskCreate(Delaytask_1,"Delaytask_1",2048,NULL,5,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}
