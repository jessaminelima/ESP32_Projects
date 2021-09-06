
/* Lib C */
#include <stdio.h>


/* FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/* Drivers */
#include "driver/gpio.h"

/* Logs */
#include "esp_log.h"

#include "sdkconfig.h"

/* Definições Gerais */
static const char *TAG = "ESP";

/* Task responsável em inverter o estado lógico do led building*/
void toggle_task (void *pvParameter)
{
    /* Configura a GPIO2 do ESP32 como GPIO-OUTPUT */
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(GPIO_NUM_2, 0);
        /* Bloqueia intencionalmente esta task por 1s */
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_NUM_2, 1);
        /* Bloqueia intencionalmente esta task por 1s */
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    /* Task toogle */
    xTaskCreate(toggle_task, "toggle_task", 1024, NULL, 1, NULL);
    ESP_LOGI(TAG,"Start Task Toggle");
}
