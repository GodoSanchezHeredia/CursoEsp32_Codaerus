//ejemplo3 input

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>



void app_main() {
  printf("Clase GPIO INPUT!\n");

 // gpio_set_direction(GPIO_NUM_2,GPIO_MODE_INPUT);
 // gpio_pullup_en(GPIO_NUM_2);

 // gpio_set_direction(GPIO_NUM_17,GPIO_MODE_INPUT);
  //gpio_pulldown_en(GPIO_NUM_17);

 // gpio_set_direction(GPIO_NUM_4,GPIO_MODE_OUTPUT);
  //gpio_set_direction(GPIO_NUM_18,GPIO_MODE_OUTPUT);


//ENTRADAS
  gpio_config_t io_input = {
    .pin_bit_mask = ((1ULL<<GPIO_NUM_2) |(1ULL<<GPIO_NUM_17)) ,
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .intr_type =GPIO_INTR_DISABLE
  };

  ESP_ERROR_CHECK(gpio_config(&io_input));
  
  //SALIDAS
  gpio_config_t io_output = {
    .pin_bit_mask = ((1ULL<<GPIO_NUM_18) |(1ULL<<GPIO_NUM_4)) ,
    .mode=GPIO_MODE_OUTPUT
  };

  ESP_ERROR_CHECK(gpio_config(&io_output));

  while (true) {
    int button_state1 = gpio_get_level(GPIO_NUM_2);
    int button_state2 = gpio_get_level(GPIO_NUM_17);

    if(button_state1 != 1){
      printf("Boton1 Pulsado!\n");
      gpio_set_level(GPIO_NUM_4,1);
    }else{
      gpio_set_level(GPIO_NUM_4,0);
    }

    if(button_state2  != 1){
      printf("Boton2 Pulsado!\n");
      gpio_set_level(GPIO_NUM_18,1);
    }else{
      gpio_set_level(GPIO_NUM_18,0);
    }


    vTaskDelay(100 / portTICK_PERIOD_MS);

  }
}
