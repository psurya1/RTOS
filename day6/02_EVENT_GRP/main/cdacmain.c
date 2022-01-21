#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/event_groups.h>

TaskHandle_t temp;
TaskHandle_t press;
TaskHandle_t calb;
EventGroupHandle_t sensor;
const uint32_t temp_event_bit=(1 << 0);
const uint32_t pres_event_bit=(1 << 1);
const uint32_t all_bit=(temp_event_bit | pres_event_bit);

void TemperatureTask(void *pv)
{
    while(1)
    {
        printf("temperature task\n");
        xEventGroupSetBits(sensor,temp_event_bit);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void PressureTask(void *pv)
{
    while(1)
    {
        printf("pressure task\n");
        xEventGroupSetBits(sensor,pres_event_bit);
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}
void CalibrationTask(void *pv)
{
    EventBits_t result;
    while(1)
    {
        printf("calibration task\n");
        result = xEventGroupWaitBits(sensor,all_bit,pdTRUE,pdTRUE,pdMS_TO_TICKS(5000));
        printf("RESULT %d\n",result);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    sensor =xEventGroupCreate();
    xTaskCreate(TemperatureTask,"TemperatureTask",2048,NULL,5,&temp);
    xTaskCreate(PressureTask,"PressureTask",2048,NULL,5,&press);
    xTaskCreate(CalibrationTask,"CalibrationTask",2048,NULL,5,&calb);
}