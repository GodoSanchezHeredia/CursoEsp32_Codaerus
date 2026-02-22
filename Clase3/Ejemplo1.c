
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"

void app_main() {
  printf("Clase GPIO OUTPUT!\n");
  //ESP_ERROR_CHECK-> evaluamos errores
  ESP_ERROR_CHECK(gpio_set_direction(GPIO_NUM_4,GPIO_MODE_OUTPUT));

  while (true) {
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,1));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
      
    ESP_ERROR_CHECK(gpio_set_level(GPIO_NUM_4,0));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
