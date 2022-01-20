#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/semphr.h>


SemaphoreHandle_t sem;
TaskHandle_t xHandle_1;
TaskHandle_t xHandle_2;


void sensortask_1(void *pvparameters)
{
    int sensor_data=0;
    while(1)
    {
        sensor_data++;
        printf("SENSOR TASK  RUNNING: STACK SIZE %d\n",sensor_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        if(sensor_data==10)
        {
            xSemaphoreGive(sem);
            vTaskDelay(1000/ portTICK_PERIOD_MS);
        }
        
    }
}
void Alarmtask_1(void *pvparameters)
{
    int rece_data=50; 
    while(1)
    {
        //rece_data++;
        xSemaphoreTake(sem,portMAX_DELAY);
        printf("RECEIVED DATA %d\n",rece_data);
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    sem=xSemaphoreCreateBinary();
    BaseType_t result;
    
    result=xTaskCreate(sensortask_1,"sensortask_1",2048,NULL,5,&xHandle_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarmtask_1,"Alarmtask_1",2048,NULL,5,&xHandle_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    xSemaphoreTake(sem,portMAX_DELAY);
}