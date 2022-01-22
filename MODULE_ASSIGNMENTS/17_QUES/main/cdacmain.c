#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>

//when other task are not running the idle task will run...


TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;

const uint32_t first_bit=(1 << 0);
const uint32_t second_bit=(1 << 1);
const uint32_t all_bit=(first_bit | second_bit);
EventGroupHandle_t x;

void sensortask_1(void *pvparameters)
{
    int sensor_data=0;
    while(1)
    {
        sensor_data++;
        printf("SENSOR TASK  RUNNING: %d\n",sensor_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        if(sensor_data==5)
        {
            vTaskDelete(NULL);
            xEventGroupSetBits(x,first_bit);
        }
        
        
    }
}
void Alarmtask_1(void *pvparameters)
{
    int alarm_data=0; 
    while(1)
    {
        alarm_data++;
        printf("ALARM DATA %d\n",alarm_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        if(alarm_data==5)
        {
            vTaskDelete(NULL);
            xEventGroupSetBits(x,second_bit);
        }
    }
}
void app_main()
{
    x=xEventGroupCreate();
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
    EventBits_t great;
    great = xEventGroupWaitBits(x,all_bit,pdTRUE,pdTRUE,pdMS_TO_TICKS(5000));
    printf("EVENT  %d\n",great);
    while(1)
    {
        printf("IDLE TASK\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}