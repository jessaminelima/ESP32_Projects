/* Lib C */
#include <stdio.h>
#include <stdint.h>  

/* FreeRTOS */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

/* Drivers */
#include "driver/gpio.h"

/* Logs */
#include "esp_log.h"

/* Definições Gerais */
static const char * TAG = "ESP";

/* Variável Da Fila */
QueueHandle_t xQueue_button; 

/* Protótipos */
void task_print(void * pvParameter);

/* Task responsável em inverter o estado lógico do led building*/
void task_blink(void *pvParameter)
{
	ESP_LOGI(TAG, "task_led run...");

	/* Configura a GPIO2 do ESP32 como GPIO-OUTPUT */
    gpio_pad_select_gpio(GPIO_NUM_2);
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
/*
 * Task Responsável pela leitura de button; Quando button for
 * pressionado, o valor de count será enviado para a fila e, logo após, 
 * count será incrementado em uma unidade;
 */
void task_button(void * pvParameter)
{
	/* uint32_t é um typedef padrão definido em stdint.h */
	uint32_t count = 0; 
	uint32_t status = 0;

	ESP_LOGI(TAG, "task_button run...");
    /*
     * Configuração da GPIO 15 como saída;
     */
    gpio_pad_select_gpio(GPIO_NUM_15);
    gpio_set_direction(GPIO_NUM_15, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_15, GPIO_PULLUP_ONLY);	

	/* As Tasks normalmente possuem um loop sem saída */
	while(1)
	{
		/* Botão pressionado? */
		if(gpio_get_level(GPIO_NUM_15) == 0 && status == 0)
		{
			/* Delay necessário para não processar o bounce causado pelo acionamento do botão */
			vTaskDelay(100 / portTICK_PERIOD_MS); 
			
            /* O botão ainda está sendo pressionado? Sim, então... */
			if(gpio_get_level(GPIO_NUM_15) == 0 && status == 0)
			{

				ESP_LOGI(TAG, "Button foi pressionado");
				/*
				 * Envia na fila o valor da variável count.
				 * count somente será incrementado caso seja enviado na fila 
				 * seu antigo valor;
				 */
				if(xQueueSend(xQueue_button, &count, (10/portTICK_PERIOD_MS)) == pdPASS)
				{
					ESP_LOGI(TAG, "Count = %d enviado na Fila", count);
                    count++;
				}
				status = 1; 				
			}

		}
		/* Botão Solto, porém já foi pressionado? */
		if(gpio_get_level(GPIO_NUM_15) == 1 && status == 1)
		{
			/* Delay necessário para não processar o bounce causado pelo acionamento do botão */
			vTaskDelay(100 / portTICK_PERIOD_MS); 

			/* O botão ainda está realmente solto? Sim, então... */
			if(gpio_get_level(GPIO_NUM_15) == 1 && status == 1)
			{
				ESP_LOGI(TAG, "Button foi solto");
				status = 0; 
			}
		}
		/* Bloqueia esta task por 10ms */
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
	/* 
     * Este comando não deveria ser executado... Caso algo estranho aconteça, 
	 * esta task será deletada; O parametro NULL informa que é para desalocar
	 * da memória ESTA task;
	 */
    vTaskDelete(NULL);	
}
/*
 * Esta task é responsável em receber o valor de count
 * por meio da leitura da fila e imprimir na saída do console.
 */
void task_print(void * pvParameter)
{
	uint32_t count; 

	ESP_LOGI(TAG, "task_print run...");

	while(1)
	{
		/* Aguarda a chegada de algum valor na fila */
		xQueueReceive(xQueue_button, &count, portMAX_DELAY); 	
		ESP_LOGI(TAG, "Count = %d foi recebido", count);	
		
		/* Bloqueia intencionalmente esta task por 10ms */
		vTaskDelay(10/portTICK_PERIOD_MS);
	}
	/* Este comando não deve ser executado... */
    vTaskDelete(NULL);
}

void app_main(void)
{
	/*
	 * Realiza a alocação dinâmica da fila na memória RAM do ESP32.
	 * Neste caso foi criado um fila com 5 elementos do tipo unsigned int 32 bits.
	 */
	if((xQueue_button = xQueueCreate(5, sizeof(uint32_t))) == NULL)
	{
		ESP_LOGI(TAG, "error - nao foi possivel alocar xQueue_button");
		/* app_main será finalizada e o programa finalizado */
		return;
	} 
	/* configMINIMAL_STACK_SIZE é um #define que informa para o FreeRTOS qual o tamanho mínimo
     * necessário para rodar uma task. Por meio do menuconfig é possível saber o tamanho de configMINIMAL_STACK_SIZE; 
	 */
    if(xTaskCreate(task_blink, "task_blink", 4048, NULL, 5, NULL) != pdTRUE)
	{
		ESP_LOGI(TAG, "error - nao foi possivel alocar task_led");	
		return;		
	}
	/* Task button */
	if(xTaskCreate(task_button, "task_button", 4048, NULL, 5, NULL ) != pdTRUE)
	{
		ESP_LOGI(TAG, "error - nao foi possivel alocar task_button");	
		return;		
	}	
	/* Task_print e task_adc contém a função printf (ESP_LOGI). Portanto, foi aumentado o stack para 2k */
	if(xTaskCreate(task_print, "task_print", 4048, NULL, 5, NULL ) != pdTRUE)
	{
		ESP_LOGI(TAG, "error - nao foi possivel alocar task_print");	
		return;		
	}	
}





