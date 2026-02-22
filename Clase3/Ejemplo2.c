#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"

void app_main() {
  printf("Clase GPIO OUTPUT!\n");
  
    gpio_config_t io_configuration = {
      .pin_bit_mask = ((1ULL<<GPIO_NUM_18) |(1ULL<<GPIO_NUM_4)|(1ULL<<GPIO_NUM_5)) ,
      .mode=GPIO_MODE_OUTPUT
    };

  ESP_ERROR_CHECK(gpio_config(&io_configuration));


  while (true) {
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_18,1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,1));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_5,0));
    vTaskDelay(500 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_18,0));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,0));
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_5,1));

    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}
