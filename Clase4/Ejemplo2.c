
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>



void app_main() {
  printf("Clase GPIO INPUT!\n");

  gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT);
  gpio_pullup_en(GPIO_NUM_2);

  gpio_set_direction(GPIO_NUM_17,GPIO_MODE_INPUT);
  gpio_pulldown_en(GPIO_NUM_17);

  gpio_set_direction(GPIO_NUM_4,GPIO_MODE_OUTPUT);
  gpio_set_direction(GPIO_NUM_18,GPIO_MODE_OUTPUT);


  while (true) {
    int button_state1 = gpio_get_level(GPIO_NUM_2);
    int button_state2 = gpio_get_level(GPIO_NUM_17);

    if(button_state1 != 1){
      printf("Boton1 Pulsado!\n");
      gpio_set_level(GPIO_NUM_4,1);
    }else{
      gpio_set_level(GPIO_NUM_4,0);
    }

    if(button_state2 == 1){
      printf("Boton2 Pulsado!\n");
      gpio_set_level(GPIO_NUM_18,1);
    }else{
      gpio_set_level(GPIO_NUM_18,0);
    }


    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}