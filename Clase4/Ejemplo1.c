// ejemplo 1 input
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>



void app_main() {
  printf("Clase GPIO INPUT!\n");

  gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT);

  while (true) {
    int button_state = gpio_get_level(GPIO_NUM_2);
    if(button_state!=1){
      printf("Boton Pulsado!\n");
    }
    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}
