//EJEMPLO 4 RTOS
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>

//void vTaskFunction(void *pvParameters), 

void blink_Led1(void *p){

  ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_4,GPIO_MODE_OUTPUT));

  while(1){
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,1));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,0));
    vTaskDelay(1000 / portTICK_PERIOD_MS);

  }

}
void blink_Led2(void *p){


  ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_18,GPIO_MODE_OUTPUT));

  while(1){
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_18,1));
    vTaskDelay(2000 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_18,0));
    vTaskDelay(2000 / portTICK_PERIOD_MS);
    
  }
}
void blink_Led3(void *p){


  ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_5,GPIO_MODE_OUTPUT));

  while(1){
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_5,1));
    vTaskDelay(500 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_5,0));
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
  }
}
void blink_Led4(void *p){


  ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_16,GPIO_MODE_OUTPUT));

  while(1){
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_16,1));
    vTaskDelay(250 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_16,0));
    vTaskDelay(250 / portTICK_PERIOD_MS);
    
  }
}
// /xTaskCreate(
//                             TaskFunction_t pvTaskCode,
//                             const char * const pcName,     /*lint !e971 Unqualified char types are allowed for strings and single characters only. */
//                             const uint32_t usStackDepth,
//                             void * const pvParameters,
//                             UBaseType_t uxPriority,
//                             TaskHandle_t * const pxCreatedTask)

void app_main() {

  xTaskCreate(&blink_Led1,"LED1",2048,NULL,1,NULL);
  xTaskCreate(&blink_Led2,"LED2",2048,NULL,1,NULL);
  xTaskCreate(&blink_Led3,"LED3",2048,NULL,1,NULL);
  xTaskCreate(&blink_Led4,"LED4",2048,NULL,1,NULL);

}
