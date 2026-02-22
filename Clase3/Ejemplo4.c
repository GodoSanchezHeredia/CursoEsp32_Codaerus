#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_err.h"
#include <stdint.h>

//maquino estado , contador binario

//gpio_num_t leds[] = {GPIO_NUM_18,GPIO_NUM_4,GPIO_NUM_5,GPIO_NUM_16};
gpio_num_t leds[] = {GPIO_NUM_16,GPIO_NUM_5,GPIO_NUM_4,GPIO_NUM_18};


void CounterBinary(int value){

  for(int i=0;i<4;i++){
    gpio_set_level(leds[i],(value>>i)&1);
  }
}

void app_main() {
  printf("Clase GPIO OUTPUT!\n");


  ESP_ERROR_CHECK(gpio_config(&(gpio_config_t ){
    .pin_bit_mask = ((1ULL<<GPIO_NUM_18) |(1ULL<<GPIO_NUM_4)|(1ULL<<GPIO_NUM_5)|(1ULL<<GPIO_NUM_16)) ,
    .mode=GPIO_MODE_OUTPUT
  }));

  uint8_t counter = 0;

  while (true) {
    CounterBinary(counter);
    counter++;
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    

  }
}
